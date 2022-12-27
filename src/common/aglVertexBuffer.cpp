#include <common/aglVertexBuffer.h>

#include <cafe/os.h>

namespace agl {

VertexBuffer::VertexBuffer()
    : mVertexStream()
    , mpBuffer(nullptr)
    , mStride(0)
    , mVertexNum(0)
    , mBufferByteSize(0)
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
    mBufferByteSize = 0;
    mStride = 0;
    mVertexNum = 0;
}

void VertexBuffer::setUpBuffer(const void* buffer, u32 stride, u32 buffer_byte_size)
{
    cleanUp_();

    // SEAD_ASSERT(buffer != nullptr);
    // SEAD_ASSERT(buffer_byte_size != 0);

    mpBuffer = buffer;
    mStride = stride;

    if (stride == 0)
    {
        mVertexNum = 1;
        mBufferByteSize = buffer_byte_size;
    }
    else
    {
        mVertexNum = buffer_byte_size / stride;
        mBufferByteSize = stride * mVertexNum;
    }

    // SEAD_ASSERT(buffer_byte_size == mBufferByteSize);

    DCFlushRangeNoSync(mpBuffer, mBufferByteSize);
}

}
