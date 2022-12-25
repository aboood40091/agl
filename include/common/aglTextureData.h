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

    TextureFormat getTextureFormat() const { return mFormat; }
    TextureType getTextureType() const { return TextureType(mSurface.dim); }

    s32 getWidth() const { return sead::Mathi::max(mSurface.width, mWidth); }
    s32 getHeight() const { return sead::Mathi::max(mSurface.height, mHeight); }

    MultiSampleType getMultiSampleType() const { return MultiSampleType(mSurface.aa); }

    s32 getDepth() const { return sead::Mathi::max(mSurface.depth, mDepth); }

    void* getImagePtr() const { return mSurface.imagePtr; }
    void setImagePtr(void* ptr) { mSurface.imagePtr = ptr; }

    u32 getImageSize() const { return mSurface.imageSize; }

    void* getMipPtr() const { return mSurface.mipPtr; }
    void setMipPtr(void* ptr) { mSurface.mipPtr = ptr; }

    u32 getMipSize() const { return mSurface.mipSize; }

    u32 getSurfaceSwizzle() { return GX2GetSurfaceSwizzle(&mSurface); }
    void setSurfaceSwizzle(u32 swizzle) { GX2SetSurfaceSwizzle(&mSurface, swizzle); }

    TextureCompSel getComponentR() const { return mCompR; }
    TextureCompSel getComponentG() const { return mCompG; }
    TextureCompSel getComponentB() const { return mCompB; }
    TextureCompSel getComponentA() const { return mCompA; }

    void initialize(TextureFormat format, u32 width, u32 height, u32 mip_level_num)
    {
        initialize_(cTextureType_2D, format, width, height, 1, mip_level_num, cMultiSampleType_1x);
    }

    void initialize3D(TextureFormat format, u32 width, u32 height, u32 depth, u32 mip_level_num)
    {
        initialize_(cTextureType_3D, format, width, height, depth, mip_level_num, cMultiSampleType_1x);
    }

    void initializeCubeMap(TextureFormat format, u32 width, u32 height, u32 mip_level_num)
    {
        initialize_(cTextureType_CubeMap, format, width, height, 6, mip_level_num, cMultiSampleType_1x);
    }

    void initializeCubeMapArray(TextureFormat format, u32 width, u32 height, u32 array_num, u32 mip_level_num)
    {
        initialize_(cTextureType_CubeMap, format, width, height, array_num * 6, mip_level_num, cMultiSampleType_1x);
    }

    void initializeArray(TextureFormat format, u32 width, u32 height, u32 array_num, u32 mip_level_num)
    {
        initialize_(cTextureType_2D_Array, format, width, height, array_num, mip_level_num, cMultiSampleType_1x);
    }

    void initializeMultiSample(TextureFormat format, u32 width, u32 height, MultiSampleType multi_sample_type)
    {
        initialize_(cTextureType_2D_MSAA, format, width, height, 1, 1, multi_sample_type);
    }

    void setMipLevelNum(u32 mip_level_num);

    void invalidateGPUCache() const;

    void initializeFromSurface(const GX2Surface& surface);

private:
    void initialize_(TextureType type, TextureFormat format, u32 width, u32 height, u32 depth, u32 mip_level_num, MultiSampleType multi_sample_type);
    void initializeSize_(u32 width, u32 height, u32 depth);

private:
    TextureFormat mFormat;
    GX2Surface mSurface;
    s32 mWidth;
    s32 mHeight;
    s32 mDepth;
    u32 mImageByteSize;
    TextureCompSel mCompR;
    TextureCompSel mCompG;
    TextureCompSel mCompB;
    TextureCompSel mCompA;

    friend class TextureSampler;
};
static_assert(sizeof(TextureData) == 0x9C, "agl::TextureData size mismatch");

}
