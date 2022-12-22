#include <container/seadBuffer.h>
#include <mc/seadCoreInfo.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace agl { namespace utl {

DynamicTextureAllocator* DynamicTextureAllocator::sInstance = nullptr;

void DynamicTextureAllocator::free(const TextureData* ptr)
{
    // SEAD_ASSERT(ptr != nullptr);

    if (!free_(&mContext[s32(sead::CoreInfo::getCurrentCoreId())], ptr))
    {
        // TODO: scoped lock
        mCriticalSection.lock();
        {
            for (sead::UnsafeArray<Context, 4>::iterator itr_ctx = mContext.begin(), itr_ctx_end = --mContext.end(); itr_ctx != itr_ctx_end; ++itr_ctx)
                if (itr_ctx.getIndex() != s32(sead::CoreInfo::getCurrentCoreId()))
                    if (free_(&(*itr_ctx), ptr))
                        break;
        }
        mCriticalSection.unlock();
    }
}

bool DynamicTextureAllocator::free_(Context* p_ctx, const TextureData* ptr)
{
    // SEAD_ASSERT(ptr != nullptr);
    TextureDataEx* p_tex = static_cast<TextureDataEx*>(const_cast<TextureData*>(ptr));

    if (p_tex->mpContext != p_ctx)
        return false;

    // SEAD_ASSERT(p_tex->mpMemoryBlock != nullptr);
    p_tex->mpMemoryAllocator->free(p_tex->mpMemoryBlock);
    p_tex->mpMemoryBlock = nullptr;

    return true;
}

} }
