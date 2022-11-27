#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <thread/seadCriticalSection.h>

namespace agl {

class TextureData;

namespace utl {

class DynamicTextureAllocator
{
    SEAD_SINGLETON_DISPOSER(DynamicTextureAllocator)

private:
    struct Context
    {
        u32 _0[0x908 / sizeof(u32)];
    };
    static_assert(sizeof(Context) == 0x908, "agl::utl::DynamicTextureAllocator::Context size mismatch");

public:
    DynamicTextureAllocator();
    virtual ~DynamicTextureAllocator();

    void free(const TextureData* ptr);

private:
    bool free_(Context* p_ctx, const TextureData* ptr);

private:
    sead::BitFlag32 _10;
    Context mContext[4]; // sead::UnsafeArray<Context, 4>
    sead::CriticalSection mCriticalSection;
    u32 _2470;
    u32 _2474;
};
static_assert(sizeof(DynamicTextureAllocator) == 0x247C, "agl::utl::DynamicTextureAllocator size mismatch");

} }
