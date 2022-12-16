#pragma once

#include <detail/aglGX2.h>

namespace agl {

inline void
RenderTargetColor::copyToDisplayBuffer(const sead::DisplayBufferCafe* display_buffer) const
{
    copyToDisplayBuffer(
        display_buffer->getScanOutTarget() == sead::DisplayBufferCafe::cTarget_TV
            ? GX2_SCAN_TARGET_TV
            : GX2_SCAN_TARGET_DRC_FIRST
    );
}

inline void
RenderTargetColor::copyToDisplayBuffer(GX2ScanTarget scan_target) const
{
    GX2ColorBuffer color_buffer;
    color_buffer.surface.width = mInnerBuffer.surface.width;
    color_buffer.surface.height = mInnerBuffer.surface.height;

    GX2SetViewport(
        0.0f, 0.0f,
        f32(s32(color_buffer.surface.width)), f32(s32(color_buffer.surface.height)),
        0.0f, 1.0f
    );

    GX2SetScissor(
        0, 0,
        color_buffer.surface.width, color_buffer.surface.height
    );

    if (scan_target == GX2_SCAN_TARGET_TV)
    {
        GX2InitColorBufferFTV(
            &color_buffer,
            color_buffer.surface.width, color_buffer.surface.height,
            mInnerBuffer.surface.format,
            mInnerBuffer.surface.aa
        );
        GX2InitColorBufferPtr(&color_buffer, mInnerBuffer.surface.imagePtr);
        GX2InitColorBufferAuxPtr(&color_buffer, mInnerBuffer.auxPtr);

        GX2CopyColorBufferToScanBuffer(&color_buffer, scan_target);
        agl::driver::GX2Resource::instance()->restoreContextState();
    }
    else
    {
        GX2CopyColorBufferToScanBuffer(&mInnerBuffer, scan_target);
        agl::driver::GX2Resource::instance()->restoreContextState();
    }
}

inline void
RenderTargetColor::expandAuxBuffer() const
{
    if (!mpAuxBuffer)
        return;

    if (mUpdateRegs)
    {
        initRegs_();
        mUpdateRegs = false;
    }

    GX2ExpandAAColorBuffer(&mInnerBuffer);
    driver::GX2Resource::instance()->restoreContextState();
}

inline void
RenderTargetDepth::expandHiZBuffer() const
{
    if (!mpHiZBuffer)
        return;

    if (mUpdateRegs)
    {
        initRegs_();
        mUpdateRegs = false;
    }

    GX2ExpandDepthBuffer(&mInnerBuffer);
    driver::GX2Resource::instance()->restoreContextState();
}

}
