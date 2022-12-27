#include <common/aglVertexAttribute.h>

namespace agl {

VertexAttribute::VertexAttribute()
    : mSetupFinish(false)
    , mCreateFinish(false)
    , mpFetchShaderBuf(nullptr)
{
}

VertexAttribute::~VertexAttribute()
{
    destroy();
}

void VertexAttribute::create(u32 buffer_max, sead::Heap* heap)
{
    // SEAD_ASSERT(0 < buffer_max && buffer_max <= cVertexAttributeMax);
    mVertexBuffer.allocBuffer(buffer_max, heap);

    mpFetchShaderBuf = new (heap, GX2_SHADER_ALIGNMENT) u8[GX2CalcFetchShaderSize(cVertexAttributeMax)];

    mCreateFinish = true;

    cleanUp();
}

void VertexAttribute::destroy()
{
    if (!mCreateFinish)
        return;

    mVertexBuffer.freeBuffer();

    if (mpFetchShaderBuf)
    {
        delete[] mpFetchShaderBuf;
        mpFetchShaderBuf = nullptr;
    }

    mCreateFinish = false;
    mSetupFinish = false;
}

}
