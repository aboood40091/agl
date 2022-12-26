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

        void* getImagePtr() const { return mpImagePtr; }
        void* getMipPtr() const { return mpMipPtr; }

    private:
        u8* mpBuffer;
        u32 mSize;
        u8* mpBufferFromDebugHeap;
        void* mpImagePtr;
        void* mpMipPtr;
        sead::ListNode mListNode;

        friend class TextureMemoryAllocator;
    };

public:
    TextureMemoryAllocator();
    virtual ~TextureMemoryAllocator();

    u32 getUsedSize() const { return mUsedSize; }

    MemoryBlock* alloc(const TextureData& tex, void** pp_buffer = nullptr, bool allocate_from_head = true);
    void free(MemoryBlock* p_memory);

    bool isOverwrapperd(const TextureMemoryAllocator& allocator) const;

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
