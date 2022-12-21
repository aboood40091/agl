#pragma once

#include <common/aglVertexEnum.h>

namespace agl {

class VertexStream
{
public:
    VertexStream()
        : mFormat(cVertexStreamFormat_8_uNorm)
        , mOffset(0)
        , mInitialized(false)
    {
    }

    void reset()
    {
        mInitialized = false;
    }

private:
    VertexStreamFormat mFormat;
    u32 mOffset;
    bool mInitialized;
    u32 mCompSel;
    u32 mDivisor;
    VertexStreamEndianSwap mEndianSwap;
    VertexStreamIndexType mIndexType;
};
static_assert(sizeof(VertexStream) == 0x1C);

}
