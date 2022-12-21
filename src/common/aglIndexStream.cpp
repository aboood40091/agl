#include <common/aglIndexStream.h>

namespace agl {

IndexStream::IndexStream()
    : mFormat(cIndexStreamFormat_u16)
    , mPrimitiveType(GX2_PRIMITIVE_TRIANGLES)
    , mpBuffer(NULL)
    , mCount(0)
    , mStride(0)
{
}

IndexStream::~IndexStream()
{
    cleanUp_();
}

void IndexStream::cleanUp_()
{
    mpBuffer = NULL;
    mCount = 0;
    mStride = 0;
}

}
