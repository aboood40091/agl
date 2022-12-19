#pragma once

#include <container/seadBuffer.h>
#include <gfx/seadFrameBuffer.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>

namespace agl {

class RenderTargetColor;
class RenderTargetDepth;

template <typename T>
class RenderTarget;

class RenderBuffer : public sead::IDisposer, public sead::FrameBuffer
{
    SEAD_RTTI_OVERRIDE(RenderBuffer, sead::FrameBuffer)

public:
    RenderBuffer();
    RenderBuffer(const sead::Vector2f& virtual_size, const sead::BoundBox2f& physical_area);
    RenderBuffer(const sead::Vector2f& virtual_size, f32 physical_x, f32 physical_y, f32 physical_w, f32 physical_h);
    virtual ~RenderBuffer();

private:
    void initialize_();

public:
    virtual void copyToDisplayBuffer(const sead::DisplayBuffer* display_buffer) const;
    virtual void clear(u32 clr_flag, const sead::Color4f& color, f32 depth, u32 stencil) const;
    virtual void bindImpl_() const;

    RenderTarget<RenderTargetColor>* getRenderTargetColor(u32 target_index = 0) const
    {
        // TODO: sead::SafeArray
        if (target_index < 8)
            return mColorTarget[target_index];
        else
            return mColorTarget[0];
    }

    RenderTarget<RenderTargetDepth>* getRenderTargetDepth() const
    {
        return mDepthTarget;
    }

    void setRenderTargetColorNullAll();
    void setRenderTargetDepthNull() { mDepthTarget = NULL; }

    void clear(u32 target_index, u32 clr_flag, const sead::Color4f& color, f32 depth, u32 stencil) const;

private:
    RenderTarget<RenderTargetColor>* mColorTarget[8]; // sead::SafeArray
    RenderTarget<RenderTargetDepth>* mDepthTarget;

    static sead::Buffer<const RenderBuffer*> sBoundRenderBuffer;
};
static_assert(sizeof(RenderBuffer) == 0x50, "agl::RenderBuffer size mistmatch");

}
