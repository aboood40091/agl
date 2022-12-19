#include <common/aglRenderTarget.h>
#include <prim/seadMemUtil.h>

namespace agl {

RenderTargetColor::RenderTargetColor()
    : RenderTargetBase()
    , mIsMSAA2D(false)
    , mAuxBufferSize(0)
    , mAuxBufferAlign(0x800)
    , mpAuxBuffer(NULL)
{
    sead::MemUtil::fillZero(&mInnerBuffer, sizeof(GX2ColorBuffer));
    GX2InitColorBufferAuxPtr(&mInnerBuffer, NULL);
}

void RenderTargetColor::invalidateGPUCache() const
{
    if (mTextureData.getImagePtr())
        GX2Invalidate(GX2_INVALIDATE_COLOR_BUFFER, mTextureData.getImagePtr(), mTextureData.getImageSize());

    if (mTextureData.getMipPtr())
        GX2Invalidate(GX2_INVALIDATE_COLOR_BUFFER, mTextureData.getMipPtr(), mTextureData.getMipSize());
}

void RenderTargetColor::initRegs_() const
{
    mInnerBuffer.viewMip = mMipLevel;
    mInnerBuffer.viewFirstSlice = mSlice;
    mInnerBuffer.viewNumSlices = 1;
    GX2InitColorBufferRegs(&mInnerBuffer);
    mUpdateRegs = false;
}

RenderTargetDepth::RenderTargetDepth()
    : RenderTargetBase()
    , mHiZBufferSize(0)
    , mHiZBufferAlign(0x800)
    , mpHiZBuffer(NULL)
{
    sead::MemUtil::fillZero(&mInnerBuffer, sizeof(GX2DepthBuffer));
    GX2InitDepthBufferHiZPtr(&mInnerBuffer, NULL);
    GX2InitDepthBufferHiZEnable(&mInnerBuffer, GX2_DISABLE);
}

void RenderTargetDepth::initRegs_() const
{
    mInnerBuffer.viewMip = mMipLevel;
    mInnerBuffer.viewFirstSlice = mSlice;
    mInnerBuffer.viewNumSlices = 1;
    mInnerBuffer.clearDepth = 1.0f;
    mInnerBuffer.clearStencil = 0;
    GX2InitDepthBufferRegs(&mInnerBuffer);
    mUpdateRegs = false;
}

}
