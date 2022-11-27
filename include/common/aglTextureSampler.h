#pragma once

#include <common/aglShaderLocation.h>
#include <common/aglTextureData.h>
#include <gfx/seadColor.h>
#include <gfx/seadGraphics.h>
#include <prim/seadBitFlag.h>

namespace agl {

class TextureSampler
{
public:
    TextureSampler();
    virtual ~TextureSampler();

    bool activate(const SamplerLocation& location, s32 = -1) const;

private:
    void initRegs_() const;

    void initTexture_() const;
    void initWrap_() const;
    void initFilter_() const;
    void initMipParam_() const;
    void initDepthComp_() const;
    void initBorderColor_() const;

private:
    TextureData mTextureData;
    TextureFilterType mFilterMag;
    TextureFilterType mFilterMin;
    TextureMipFilterType mMipFilter;
    TextureWrapType mWrapX;
    TextureWrapType mWrapY;
    TextureWrapType mWrapZ;
    sead::Color4f mBorderColor;
    f32 mLODMin;
    f32 mLODMax;
    f32 mLODBias;
    TextureAnisoRatio mMaxAniso;
    bool mReplaceCompSel;
    TextureCompSel mCompR;
    TextureCompSel mCompG;
    TextureCompSel mCompB;
    TextureCompSel mCompA;
    bool mIsTextureSet;
    u8 _e9;
    u8 _ea;
    sead::Graphics::DepthFunc mDepthComp;
    mutable GX2Sampler mGX2Sampler;
    mutable GX2Texture mGX2Texture;
    mutable bool mHasBorder;
    mutable sead::BitFlag8 mFlag;
};
static_assert(sizeof(TextureSampler) == 0x1A0, "agl::TextureSampler size mismatch");

}
