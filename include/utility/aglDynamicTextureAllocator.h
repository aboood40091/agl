#pragma once

#include <common/aglTextureData.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>
#include <utility/aglTextureMemoryAllocator.h>

namespace agl { namespace utl {

class TextureDataEx;

class DynamicTextureAllocator
{
    SEAD_SINGLETON_DISPOSER(DynamicTextureAllocator)

private:
    struct Context
    {
        u32 _0[0x908 / sizeof(u32)];
    };
    static_assert(sizeof(Context) == 0x908, "agl::utl::DynamicTextureAllocator::Context size mismatch");

    friend class TextureDataEx;

public:
    enum AllocateType
    {
        cAllocateType_Num = 3
    };

public:
    DynamicTextureAllocator();
    virtual ~DynamicTextureAllocator();

    TextureData* alloc(
        const sead::SafeString& name,
        TextureFormat format, u32 width, u32 height, u32 mip_level_num,
        void** pp_buffer = nullptr,
        AllocateType allocate_type = AllocateType(0),
        bool invalidate_gpu_cache = true
    );
    void free(const TextureData* ptr);

private:
    bool free_(Context* p_ctx, const TextureData* ptr);

private:
    sead::BitFlag32 _10;
    sead::UnsafeArray<Context, 4> mContext;
    sead::CriticalSection mCriticalSection;
    u32 _2470;
    u32 _2474;
};
static_assert(sizeof(DynamicTextureAllocator) == 0x247C, "agl::utl::DynamicTextureAllocator size mismatch");

class TextureDataEx : public TextureData
{
public:
    TextureDataEx();

private:
    TextureMemoryAllocator*                 mpMemoryAllocator;
    TextureMemoryAllocator::MemoryBlock*    mpMemoryBlock;
    sead::SafeString                        mName;
    u32                                     _ac;
    u8                                      mAllocType;
    u8                                      b1;
    u8                                      mMipLevelNum;
    sead::BitFlag8                          mFlag;
    u8                                      mSurfaceSwizzle;
    u8                                      _b5;
    u8                                      _pad[2];
    DynamicTextureAllocator::Context*       mpContext;

    friend class DynamicTextureAllocator;
};
static_assert(sizeof(TextureDataEx) == 0xBC, "agl::utl::TextureDataEx size mismatch");

} }
