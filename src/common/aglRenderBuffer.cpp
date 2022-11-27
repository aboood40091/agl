#include <common/aglRenderBuffer.h>
#include <gfx/cafe/seadFrameBufferCafe.h>

namespace agl {

sead::Buffer<RenderBuffer*> RenderBuffer::sBoundRenderBuffer;

RenderBuffer::~RenderBuffer()
{
    for (s32 i = 0; i < sBoundRenderBuffer.size(); i++)
        if (sBoundRenderBuffer[i] == this)
            sBoundRenderBuffer[i] = NULL;
}

}
