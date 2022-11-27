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
        mCriticalSection.lock();
        {
            typedef sead::Buffer<Context>::iterator _Iterator;
            for (_Iterator itr_ctx = _Iterator(mContext), itr_ctx_end = _Iterator(mContext, 3); itr_ctx != itr_ctx_end; ++itr_ctx)
                if (itr_ctx.getIndex() != s32(sead::CoreInfo::getCurrentCoreId()) && free_(&(*itr_ctx), ptr))
                    break;
        }
        mCriticalSection.unlock();
    }
}

} }
