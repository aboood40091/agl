#pragma once

#include <container/seadBuffer.h>

#include <cafe/gx2.h>

namespace agl {

class VertexBuffer;

class VertexAttribute
{
    struct Attribute_
    {
        VertexBuffer* mpVertexBuffer;
        u32 mStreamIndex;
        u32 mBufferIndex;
    };
    static_assert(sizeof(Attribute_) == 0xC, "agl::VertexAttribute::Attribute_ size mismatch");

public:
    static const u32 cVertexAttributeMax = 16;

public:
    VertexAttribute();
    virtual ~VertexAttribute();

private:
    Attribute_ mAttribute[cVertexAttributeMax]; // sead::SafeArray<Attribute_, cVertexAttributeMax>
    sead::Buffer<VertexBuffer*> mVertexBuffer;
    bool mSetupFinish;
    bool mCreateFinish;
    GX2FetchShader mFetchShader;
    u8* mpFetchShaderBuf;
};
static_assert(sizeof(VertexAttribute) == 0xF4, "agl::VertexAttribute size mismatch");

}
