#pragma once

#include <common/aglVertexEnum.h>

#include <cafe/gx2.h>

namespace agl {

class IndexStream
{
public:
    typedef GX2PrimitiveType PrimitiveType; // Idk the actual type

public:
    IndexStream();
    virtual ~IndexStream();

    PrimitiveType getPrimitiveType() const { return mPrimitiveType; }
    void setPrimitiveType(PrimitiveType primitive_type) { mPrimitiveType = primitive_type; }

    void setUpStream(const void* addr, IndexStreamFormat format, u32 count, PrimitiveType primitive_type)
    {
        setUpStream_(addr, format, count);
        setPrimitiveType(primitive_type);
    }

    u32 getCount() const { return mCount; }

private:
    void setUpStream_(const void* addr, IndexStreamFormat format, u32 count);
    void cleanUp_();

private:
    IndexStreamFormat mFormat;
    PrimitiveType mPrimitiveType;
    void* mpBuffer;
    u32 mCount;
    u32 mStride;
};
static_assert(sizeof(IndexStream) == 0x18, "agl::IndexStream size mismatch");

}
