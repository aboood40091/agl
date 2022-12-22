#include <utility/aglTextureMemoryAllocator.h>

namespace agl { namespace utl {

void TextureMemoryAllocator::free(MemoryBlock* p_memory)
{
    // SEAD_ASSERT(p_memory != nullptr);

    mUsedSize -= p_memory->mBufferSize;

    if (p_memory->mpBufferFromDebugHeap)
    {
        delete[] p_memory->mpBufferFromDebugHeap;
        p_memory->mpBufferFromDebugHeap = nullptr;
    }

    mMemoryBlockUsed.erase(p_memory);

    if (!mMemoryBlockFree.front())
    {
        mMemoryBlockFree.pushFront(p_memory);
        return;
    }

    for (sead::OffsetList<MemoryBlock>::iterator itr = mMemoryBlockFree.begin(), itr_end = mMemoryBlockFree.end(); itr != itr_end; ++itr)
    {
        MemoryBlock* p_temp_memory = &(*itr);

        if (p_memory->mpBuffer + p_memory->mBufferSize <= p_temp_memory->mpBuffer)
        {
            mMemoryBlockFree.insertBefore(p_temp_memory, p_memory);

            if (p_memory->mpBuffer + p_memory->mBufferSize == p_temp_memory->mpBuffer)
            {
                p_memory->mBufferSize += p_temp_memory->mBufferSize;
                mMemoryBlockFree.erase(p_temp_memory);
                mMemoryBlockEmpty.pushBack(p_temp_memory);
            }

            MemoryBlock* p_prev = mMemoryBlockFree.prev(p_memory);
            if (p_prev && p_prev->mpBuffer + p_prev->mBufferSize == p_memory->mpBuffer)
            {
                p_memory->mpBuffer = p_prev->mpBuffer;
                p_memory->mBufferSize += p_prev->mBufferSize;
                mMemoryBlockFree.erase(p_prev);
                mMemoryBlockEmpty.pushBack(p_prev);
            }

            break;
        }
    }

    if (!p_memory->mListNode.isLinked())
    {
        mMemoryBlockFree.pushBack(p_memory);

        MemoryBlock* p_prev = mMemoryBlockFree.prev(p_memory);
        if (p_prev && p_prev->mpBuffer + p_prev->mBufferSize == p_memory->mpBuffer)
        {
            p_memory->mpBuffer = p_prev->mpBuffer;
            p_memory->mBufferSize += p_prev->mBufferSize;
            mMemoryBlockFree.erase(p_prev);
            mMemoryBlockEmpty.pushBack(p_prev);
        }
    }

    for (sead::OffsetList<MemoryBlock>::iterator itr = mMemoryBlockFree.begin(), itr_end = mMemoryBlockFree.end(); itr != itr_end; ++itr)
    {
        // Ok...
    }
}

} }
