#pragma once

#include <common/aglVertexStream.h>
#include <container/seadSafeArray.h>

namespace agl {

class VertexBuffer
{
public:
    static const u32 cVertexStreamMax = 16;

public:
    VertexBuffer();
    virtual ~VertexBuffer();

    void setUpBuffer(const void* buffer, u32 stride, u32 buffer_byte_size);
    void setUpStream(s32 stream_index, VertexStreamFormat format, u32 offset);

private:
    void cleanUp_();

private:
    sead::SafeArray<VertexStream, cVertexStreamMax> mVertexStream;
    const void* mpBuffer;
    u32 mStride;
    u32 mVertexNum;
    u32 mBufferByteSize;
};
static_assert(sizeof(VertexBuffer) == 0x1D4, "agl::VertexBuffer size mismatch");

}
