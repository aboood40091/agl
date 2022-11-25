#pragma once

#include <common/aglTextureEnum.h>

#include <cafe/gx2.h>

namespace agl {

class TextureData
{
public:
    TextureData();
    virtual ~TextureData() { }

    TextureType getTextureType() const { return TextureType(mSurface.dim); }

    TextureCompSel getComponentR() const { return mCompR; }
    TextureCompSel getComponentG() const { return mCompG; }
    TextureCompSel getComponentB() const { return mCompB; }
    TextureCompSel getComponentA() const { return mCompA; }

private:
    TextureFormat mFormat;
    GX2Surface mSurface;
    u32 mWidth;
    u32 mHeight;
    u32 mDepth;
    u32 mImageByteSize;
    TextureCompSel mCompR;
    TextureCompSel mCompG;
    TextureCompSel mCompB;
    TextureCompSel mCompA;
};
static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
