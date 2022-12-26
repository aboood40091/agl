#include <utility/aglTextureMemoryAllocator.h>

namespace agl { namespace utl {

TextureMemoryAllocator::MemoryBlock* TextureMemoryAllocator::alloc(const TextureData& tex, void** pp_buffer, bool allocate_from_head)
{
    if (!mpBufferStart)
        return nullptr;

    AllocArg arg;
    arg.mImageSize = tex.getImageSize();
    arg.mMipSize = tex.getMipLevelNum() > 1 ? tex.getMipSize() : 0;
    arg.mAlignment = tex.getAlignment();
    arg.mppTargetBuffer = nullptr;
    arg.mTargetBufferSize = 0;
    arg.mTargetBufferAlignment = sizeof(void*);

    if (tex.getTextureFormat() >= cTextureFormat_Depth_16 && tex.getTextureFormat() <= cTextureFormat_Depth_24_uNorm_Stencil_8)
    {
        if (pp_buffer != nullptr)
        {
            mDepthTarget.applyTextureData(tex);

            arg.mppTargetBuffer = pp_buffer;
            arg.mTargetBufferAlignment = mDepthTarget.getHiZBufferAlign();
            arg.mTargetBufferSize = mDepthTarget.getHiZBufferSize();
        }
    }
    else
    {
        if (tex.getMultiSampleType() != cMultiSampleType_1x)
        {
            mColorTarget.applyTextureData(tex);

            arg.mppTargetBuffer = pp_buffer;
            arg.mTargetBufferAlignment = mColorTarget.getAuxBufferAlign();
            arg.mTargetBufferSize = mColorTarget.getAuxBufferSize();
        }
    }

    const u32 alignment = sead::Mathu::max(arg.mAlignment, arg.mTargetBufferAlignment);

    arg.mSize  = sead::Mathu::roundUpPow2(arg.mImageSize, arg.mAlignment);
    arg.mSize += sead::Mathu::roundUpPow2(arg.mMipSize, arg.mTargetBufferAlignment);
    arg.mSize += arg.mTargetBufferSize;
    arg.mSize += alignment;

    if (allocate_from_head)
    {
        MemoryBlock* p_memory = mMemoryBlockFree.front();
        while (p_memory != nullptr)
        {
            if (alloc_(p_memory, arg, true))
                return p_memory;

            p_memory = mMemoryBlockFree.next(p_memory);
        }
    }
    else
    {
        MemoryBlock* p_memory = mMemoryBlockFree.back();
        while (p_memory != nullptr)
        {
            if (alloc_(p_memory, arg, false))
                return p_memory;

            p_memory = mMemoryBlockFree.prev(p_memory);
        }
    }

    return nullptr;
}

void TextureMemoryAllocator::free(MemoryBlock* p_memory)
{
    // SEAD_ASSERT(p_memory != nullptr);

    mUsedSize -= p_memory->mSize;

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

        if (p_memory->mpBuffer + p_memory->mSize <= p_temp_memory->mpBuffer)
        {
            mMemoryBlockFree.insertBefore(p_temp_memory, p_memory);

            if (p_memory->mpBuffer + p_memory->mSize == p_temp_memory->mpBuffer)
            {
                p_memory->mSize += p_temp_memory->mSize;
                mMemoryBlockFree.erase(p_temp_memory);
                mMemoryBlockEmpty.pushBack(p_temp_memory);
            }

            MemoryBlock* p_prev = mMemoryBlockFree.prev(p_memory);
            if (p_prev && p_prev->mpBuffer + p_prev->mSize == p_memory->mpBuffer)
            {
                p_memory->mpBuffer = p_prev->mpBuffer;
                p_memory->mSize += p_prev->mSize;
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
        if (p_prev && p_prev->mpBuffer + p_prev->mSize == p_memory->mpBuffer)
        {
            p_memory->mpBuffer = p_prev->mpBuffer;
            p_memory->mSize += p_prev->mSize;
            mMemoryBlockFree.erase(p_prev);
            mMemoryBlockEmpty.pushBack(p_prev);
        }
    }

    for (sead::OffsetList<MemoryBlock>::iterator itr = mMemoryBlockFree.begin(), itr_end = mMemoryBlockFree.end(); itr != itr_end; ++itr)
    {
        // Ok...
    }
}

bool TextureMemoryAllocator::isOverwrapperd(const TextureMemoryAllocator& allocator) const
{
    // SEAD_ASSERT(&allocator != this);

    const void* buffer1 = nullptr;
    const void* buffer2 = nullptr;

    // Mismatches if ternary operator not used

    buffer2 = mMemoryBlockFree.back()
        ? mMemoryBlockFree.back()->mpBuffer
        : nullptr;

    buffer1 = allocator.mMemoryBlockFree.front()
        ? allocator.mMemoryBlockFree.front()->mpBuffer + allocator.mMemoryBlockFree.back()->mSize
        : nullptr;

    return buffer1 < buffer2;
}

} }
