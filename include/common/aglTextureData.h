#pragma once

#include <common/aglTextureEnum.h>
#include <math/seadMathCalcCommon.h>

#include <cafe/gx2.h>

namespace agl {

class TextureSampler;

class TextureData
{
public:
    TextureData();
    virtual ~TextureData() { }

    TextureType getTextureType() const { return TextureType(mSurface.dim); }

    s32 getWidth() const { return sead::Mathi::max(mSurface.width, mWidth); }
    s32 getHeight() const { return sead::Mathi::max(mSurface.height, mHeight); }

    void* getImagePtr() const { return mSurface.imagePtr; }
    u32 getImageSize() const { return mSurface.imageSize; }

    void* getMipPtr() const { return mSurface.mipPtr; }
    u32 getMipSize() const { return mSurface.mipSize; }

    TextureCompSel getComponentR() const { return mCompR; }
    TextureCompSel getComponentG() const { return mCompG; }
    TextureCompSel getComponentB() const { return mCompB; }
    TextureCompSel getComponentA() const { return mCompA; }

    void invalidateGPUCache() const;

private:
    TextureFormat mFormat;
    GX2Surface mSurface;
    s32 mWidth;
    s32 mHeight;
    u32 mDepth;
    u32 mImageByteSize;
    TextureCompSel mCompR;
    TextureCompSel mCompG;
    TextureCompSel mCompB;
    TextureCompSel mCompA;

    friend class TextureSampler;
};
static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
