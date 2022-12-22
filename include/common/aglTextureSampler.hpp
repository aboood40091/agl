#pragma once

namespace agl {

inline void
TextureSampler::applyTextureData(const TextureData& texture_data)
{
    if (!mIsTextureSet                                                   ||
        mTextureData.mSurface.dim      != texture_data.mSurface.dim      ||
        mTextureData.mSurface.width    != texture_data.mSurface.width    ||
        mTextureData.mSurface.height   != texture_data.mSurface.height   ||
        mTextureData.mSurface.depth    != texture_data.mSurface.depth    ||
        mTextureData.mSurface.numMips  != texture_data.mSurface.numMips  ||
        mTextureData.mSurface.format   != texture_data.mSurface.format   ||
        mTextureData.mSurface.swizzle  != texture_data.mSurface.swizzle  ||
        mTextureData.mSurface.tileMode != texture_data.mSurface.tileMode ||
        mTextureData.mSurface.aa       != texture_data.mSurface.aa)
    {
        applyTextureData_(texture_data);
    }
    else
    {
        void* image_ptr = texture_data.mSurface.imagePtr;
        void* mip_ptr = texture_data.mSurface.mipPtr;

        mTextureData.mSurface.imagePtr = image_ptr;
        mTextureData.mSurface.mipPtr   = mip_ptr;

        mGX2Texture.surface.imagePtr = image_ptr;
        mGX2Texture.surface.mipPtr   = mip_ptr;
    }
}

inline void
TextureSampler::setTextureCompSel(
    TextureCompSel r,
    TextureCompSel g,
    TextureCompSel b,
    TextureCompSel a
)
{
    mCompR = r;
    mCompG = g;
    mCompB = b;
    mCompA = a;

    mReplaceCompSel = true;
    mFlag.setBit(0);
}

inline void
TextureSampler::resetTextureCompSel()
{
    mReplaceCompSel = false;
    mFlag.setBit(0);
}

inline void
TextureSampler::setWrapX(TextureWrapType wrap_x)
{
    mWrapX = wrap_x;
    mFlag.setBit(1);
}

inline void
TextureSampler::setWrapY(TextureWrapType wrap_y)
{
    mWrapY = wrap_y;
    mFlag.setBit(1);
}

inline void
TextureSampler::setWrapZ(TextureWrapType wrap_z)
{
    mWrapZ = wrap_z;
    mFlag.setBit(1);
}

inline void
TextureSampler::setWrap(
    TextureWrapType wrap_x,
    TextureWrapType wrap_y,
    TextureWrapType wrap_z
)
{
    mWrapX = wrap_x;
    mWrapY = wrap_y;
    mWrapZ = wrap_z;
    mFlag.setBit(1);
}

inline void
TextureSampler::setFilterMag(TextureFilterType filter_mag)
{
    mFilterMag = filter_mag;
    mFlag.setBit(2);
}

inline void
TextureSampler::setFilterMin(TextureFilterType filter_min)
{
    mFilterMin = filter_min;
    mFlag.setBit(2);
}

inline void
TextureSampler::setFilterMip(TextureMipFilterType filter_mip)
{
    mFilterMip = filter_mip;
    mFlag.setBit(2);
}

inline void
TextureSampler::setFilter(
    TextureFilterType    filter_mag,
    TextureFilterType    filter_min,
    TextureMipFilterType filter_mip
)
{
    mFilterMag = filter_mag;
    mFilterMin = filter_min;
    mFilterMip = filter_mip;
    mFlag.setBit(2);
}

inline void
TextureSampler::setMaxAnisoRatio(TextureAnisoRatio max_aniso)
{
    mMaxAniso = max_aniso;
    mFlag.setBit(2);
}

inline void
TextureSampler::setMipParam(f32 lod_min, f32 lod_max, f32 lod_bias)
{
    mLODMin = lod_min;
    mLODMax = lod_max;
    mLODBias = lod_bias;
    mFlag.setBit(3);
}

inline void
TextureSampler::setDepthComp(sead::Graphics::DepthFunc func)
{
    mDepthComp = func;
    mFlag.setBit(4);
}

inline void
TextureSampler::setBorderColor(f32 r, f32 g, f32 b, f32 a)
{
    mBorderColor.setf(r, g, b, a);
    mFlag.setBit(5);
}

inline void
TextureSampler::setBorderColor(const sead::Color4f& color)
{
    mBorderColor = color;
    mFlag.setBit(5);
}

}
