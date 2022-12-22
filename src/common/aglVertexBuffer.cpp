#include <common/aglVertexBuffer.h>

namespace agl {

VertexBuffer::VertexBuffer()
    : mVertexStream()
    , mpBuffer(nullptr)
    , mStride(0)
    , mVertexNum(0)
    , mBufferSize(0)
{
}

VertexBuffer::~VertexBuffer()
{
    cleanUp_();
}

void VertexBuffer::cleanUp_()
{
    for (u32 i = 0; i < cVertexStreamMax; i++)
        mVertexStream[i].reset();

    mpBuffer = nullptr;
    mBufferSize = 0;
    mStride = 0;
    mVertexNum = 0;
}

}
