#include <common/aglTextureData.h>
#include <common/aglTextureFormatInfo.h>
#include <detail/aglTextureDataUtil.h>
#include <prim/seadMemUtil.h>

namespace agl {

TextureData::TextureData()
    : mWidth(1)
    , mHeight(1)
    , mDepth(1)
    , mImageByteSize(1)
    , mCompR(cTextureCompSel_0)
    , mCompG(cTextureCompSel_0)
    , mCompB(cTextureCompSel_0)
    , mCompA(cTextureCompSel_0)
{
    sead::MemUtil::fillZero(&mSurface, sizeof(GX2Surface));
}

void TextureData::invalidateGPUCache() const
{
    if (getImagePtr())
        GX2Invalidate(GX2_INVALIDATE_TEXTURE, getImagePtr(), getImageSize());

    if (getMipPtr())
        GX2Invalidate(GX2_INVALIDATE_TEXTURE, getMipPtr(), getMipSize());
}

void TextureData::initialize_(TextureType type, TextureFormat format, u32 width, u32 height, u32 depth, u32 mip_level_num, MultiSampleType multi_sample_type)
{
    mSurface.dim = GX2SurfaceDim(type);
    mFormat = format;
    mSurface.format = detail::TextureDataUtil::convFormatAGLToGX2(format);
    mSurface.aa = GX2AAMode(multi_sample_type);

    if (format >= cTextureFormat_Depth_16 && format <= cTextureFormat_Depth_24_uNorm_Stencil_8)
        mSurface.use = GX2_SURFACE_USE_DEPTH_BUFFER_TEXTURE;
    else
        mSurface.use = GX2_SURFACE_USE_TEXTURE;

    mSurface.tileMode = GX2_TILE_MODE_DEFAULT;
    mSurface.swizzle = 0;

    initializeSize_(width, height, depth);
    setMipLevelNum(mip_level_num);

    mCompR = TextureFormatInfo::getDefaultCompSel(format, 0);
    mCompG = TextureFormatInfo::getDefaultCompSel(format, 1);
    mCompB = TextureFormatInfo::getDefaultCompSel(format, 2);
    mCompA = TextureFormatInfo::getDefaultCompSel(format, 3);

    detail::TextureDataUtil::calcSizeAndAlignment(&mSurface);

    mSurface.imagePtr = nullptr;
    mSurface.mipPtr = nullptr;
}

void TextureData::initializeFromSurface(const GX2Surface& surface)
{
    mSurface = surface;
    mFormat = detail::TextureDataUtil::convFormatGX2ToAGL(mSurface.format);

    initializeSize_(mSurface.width, mSurface.height, mSurface.depth);
    setMipLevelNum(surface.numMips);

    mCompR = TextureFormatInfo::getDefaultCompSel(mFormat, 0);
    mCompG = TextureFormatInfo::getDefaultCompSel(mFormat, 1);
    mCompB = TextureFormatInfo::getDefaultCompSel(mFormat, 2);
    mCompA = TextureFormatInfo::getDefaultCompSel(mFormat, 3);
}

}
