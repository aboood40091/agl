#pragma once

#include <common/aglRenderTarget.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <heap/seadHeap.h>

namespace agl { namespace utl {

class TextureMemoryAllocator
{
public:
    class MemoryBlock
    {
    public:
        MemoryBlock(); // TODO

    private:
        u8* mpBuffer;
        u32 mBufferSize;
        u8* mpBufferFromDebugHeap;
        void* mpImagePtr;
        void* mpMipPtr;
        sead::ListNode mListNode;

        friend class TextureMemoryAllocator;
    };

public:
    TextureMemoryAllocator();
    virtual ~TextureMemoryAllocator();

    void free(MemoryBlock* p_memory);

private:
    void* mpBufferStart;
    void* mpBufferEnd;
    u32 mUsedSize; // I think
    sead::Buffer<MemoryBlock> mMemoryBlock;
    sead::OffsetList<MemoryBlock> mMemoryBlockUsed;
    sead::OffsetList<MemoryBlock> mMemoryBlockFree;
    sead::OffsetList<MemoryBlock> mMemoryBlockEmpty;
    RenderTarget<RenderTargetColor> mColorTarget;
    RenderTarget<RenderTargetDepth> mDepthTarget;
    sead::Heap* mpDebugHeap;
};
static_assert(sizeof(TextureMemoryAllocator) == 0x300, "agl::utl::TextureMemoryAllocator size mismatch");

} }
