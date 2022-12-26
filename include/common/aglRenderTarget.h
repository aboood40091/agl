#pragma once

#include <common/aglTextureData.h>
#include <gfx/cafe/seadFrameBufferCafe.h>

namespace agl {

class RenderTargetBase
{
public:
    RenderTargetBase(u32 mip_level = 0, u32 slice = 0)
        : mTextureData()
        , mUpdateRegs(true)
        , mMipLevel(mip_level)
        , mSlice(slice)
    {
    }

    TextureData& getTextureData() { return mTextureData; }
    const TextureData& getTextureData() const { return mTextureData; }

    u32 getMipLevel() const { return mMipLevel; }
    u32 getSlice() const { return mSlice; }

protected:
    TextureData mTextureData;
    mutable bool mUpdateRegs;
    u32 mMipLevel;
    u32 mSlice;
};
static_assert(sizeof(RenderTargetBase) == 0xA8);

class RenderTargetColor : public RenderTargetBase
{
public:
    RenderTargetColor();
    RenderTargetColor(const TextureData& texture_data, u32 mip_level, u32 slice);

    u32 getAuxBufferSize()  const { return mAuxBufferSize;  }
    u32 getAuxBufferAlign() const { return mAuxBufferAlign; }

    GX2ColorBuffer& getInnerBuffer() const { return mInnerBuffer; }

    void copyToDisplayBuffer(const sead::DisplayBufferCafe* display_buffer) const;
    void copyToDisplayBuffer(GX2ScanTarget scan_target) const;
    void initRegs() const;
    void expandAuxBuffer() const;

    void invalidateGPUCache() const;

private:
    void initRegs_() const;

protected:
    bool mIsMSAA2D;
    u32 mAuxBufferSize;
    u32 mAuxBufferAlign;
    void* mpAuxBuffer;
    mutable GX2ColorBuffer mInnerBuffer;
};
static_assert(sizeof(RenderTargetColor) == 0x154, "agl::RenderTargetColor size mismatch");

class RenderTargetDepth : public RenderTargetBase
{
public:
    RenderTargetDepth();
    RenderTargetDepth(const TextureData& texture_data, u32 mip_level, u32 slice);

    u32 getHiZBufferSize()  const { return mHiZBufferSize;  }
    u32 getHiZBufferAlign() const { return mHiZBufferAlign; }

    GX2DepthBuffer& getInnerBuffer() const { return mInnerBuffer; }

    void initRegs() const;
    void expandHiZBuffer() const;

    void invalidateGPUCache() const;

private:
    void initRegs_() const;

protected:
    u32 mHiZBufferSize;
    u32 mHiZBufferAlign;
    void* mpHiZBuffer;
    mutable GX2DepthBuffer mInnerBuffer;
};
static_assert(sizeof(RenderTargetDepth) == 0x160, "agl::RenderTargetDepth size mismatch");

template <typename T>
class RenderTarget : public T
{
public:
    RenderTarget()
        : T()
    {
    }

    RenderTarget(const TextureData& texture_data, u32 mip_level, u32 slice)
        : T(texture_data, mip_level, slice)
    {
    }

    void invalidateGPUCache() const
    {
        T::invalidateGPUCache();
        mTextureData.invalidateGPUCache();
    }

    void applyTextureData(const TextureData& texture_data);
    void applyTextureData(const TextureData& texture_data, u32 mip_level, u32 slice);

private:
    void applyTextureData_(const TextureData& texture_data, u32 mip_level, u32 slice);
};

}

#ifdef __cplusplus

#include <common/aglRenderTarget.hpp>

#endif // __cplusplus
