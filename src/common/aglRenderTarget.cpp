#include <common/aglRenderTarget.h>

namespace agl {

void RenderTargetColor::initRegs_() const
{
    mInnerBuffer.viewMip = mMipLevel;
    mInnerBuffer.viewFirstSlice = mSlice;
    mInnerBuffer.viewNumSlices = 1;
    GX2InitColorBufferRegs(&mInnerBuffer);
    mUpdateRegs = false;
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
