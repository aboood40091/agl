#pragma once

#include <common/aglVertexEnum.h>
#include <container/seadSafeArray.h>

#include <cafe/gx2.h>

namespace agl {

class VertexBuffer
{
    struct Stream_
    {
        Stream_()
            : mFormat(cVertexStreamFormat_8_uNorm)
            , mOffset(0)
            , mEnable(false)
        {
        }

        VertexStreamFormat mFormat;
        u32 mOffset;

        bool mEnable;

        GX2CompSel mCompSel;
        u32 mDivisor;
        GX2EndianSwapMode mEndianSwap;
        GX2AttribIndexType mIndexType;
    };
    static_assert(sizeof(Stream_) == 0x1C);

public:
    static const u32 cVertexStreamMax = 16;

public:
    VertexBuffer();
    virtual ~VertexBuffer();

    bool isEnable(s32 index) const { return mStream[index].mEnable; }

    void setUpBuffer(const void* buffer, u32 stride, u32 buffer_byte_size);
    void setUpStream(s32 index, VertexStreamFormat format, u32 offset);

private:
    void cleanUp_();

private:
    sead::SafeArray<Stream_, cVertexStreamMax> mStream;
    const void* mpBuffer;
    u32 mStride;
    u32 mVertexNum;
    u32 mBufferByteSize;
};
static_assert(sizeof(VertexBuffer) == 0x1D4, "agl::VertexBuffer size mismatch");

}
