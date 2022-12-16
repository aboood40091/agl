#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>

namespace agl {

sead::Buffer<RenderBuffer*> RenderBuffer::sBoundRenderBuffer;

RenderBuffer::~RenderBuffer()
{
    for (s32 i = 0; i < sBoundRenderBuffer.size(); i++)
        if (sBoundRenderBuffer[i] == this)
            sBoundRenderBuffer[i] = NULL;
}

void RenderBuffer::copyToDisplayBuffer(const sead::DisplayBuffer* display_buffer) const
{
    const sead::DisplayBufferCafe* p_display_buffer_cafe = sead::DynamicCast<const sead::DisplayBufferCafe>(display_buffer);

    // SEAD_ASSERT(mColorTarget[ 0 ] != nullptr);
    mColorTarget[0]->invalidateGPUCache();
    mColorTarget[0]->copyToDisplayBuffer(p_display_buffer_cafe);
}

}
