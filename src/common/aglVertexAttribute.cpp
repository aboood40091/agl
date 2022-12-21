#include <common/aglVertexAttribute.h>

namespace agl {

VertexAttribute::VertexAttribute()
    : mAttribute()
    , mVertexBuffer()
    , mSetupFinish(false)
    , mCreateFinish(false)
    , mpFetchShaderBuf(NULL)
{
}

VertexAttribute::~VertexAttribute()
{
    destroy();
}

void VertexAttribute::destroy()
{
    if (!mCreateFinish)
        return;

    mVertexBuffer.freeBuffer();

    if (mpFetchShaderBuf)
    {
        delete[] mpFetchShaderBuf;
        mpFetchShaderBuf = NULL;
    }

    mCreateFinish = false;
    mSetupFinish = false;
}

}
