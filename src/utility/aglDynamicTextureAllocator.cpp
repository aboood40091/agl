#include <container/seadBuffer.h>
#include <mc/seadCoreInfo.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace agl { namespace utl {

DynamicTextureAllocator* DynamicTextureAllocator::sInstance = NULL;

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

} }
