#pragma once

#include <common/aglVertexStream.h>
#include <container/seadSafeArray.h>

namespace agl {

class VertexBuffer
{
public:
    VertexBuffer();
    virtual ~VertexBuffer();

private:
    sead::SafeArray<VertexStream, 16> mVertexStream;
    const void* mpBuffer;
    u32 mStride;
    u32 mVertexNum;
    u32 mBufferSize;
};
static_assert(sizeof(VertexBuffer) == 0x1D4, "agl::VertexBuffer size mismatch");

}
