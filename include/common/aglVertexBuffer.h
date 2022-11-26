#pragma once

#include <common/aglVertexStream.h>

namespace agl {

class VertexBuffer
{
public:
    VertexBuffer();
    virtual ~VertexBuffer();

private:
    VertexStream mVertexStream[16]; // sead::SafeArray<VertexStream, 16>
    const void* mpBuffer;
    u32 mStride;
    u32 mVertexNum;
    u32 mBufferSize;
};
static_assert(sizeof(VertexBuffer) == 0x1D4, "agl::VertexBuffer size mismatch");

}
