#pragma once

#include <basis/seadTypes.h>

namespace agl {

class IndexStream
{
public:
    IndexStream();
    virtual ~IndexStream();

private:
    u32 mFormat; // agl::IndexStreamFormat
    u32 mPrimitiveType; // Idk the actual type
    void* mpBuffer;
    u32 mCount;
    u32 mStride;
};
static_assert(sizeof(IndexStream) == 0x18, "agl::IndexStream size mismatch");

}
