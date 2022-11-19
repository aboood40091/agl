#pragma once

#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglShaderEnum.h>
#include <common/aglTextureSampler.h>
#include <gfx/seadGraphicsContextMRT.h>
#include <util/aglParameter.h>
#include <util/aglParameterIO.h>
#include <util/aglParameterObj.h>

namespace agl {

class RenderBuffer;
class TextureData;

namespace pfx {

class DepthOfField : public utl::IParameterIO
{
    struct Context
    {
        bool mIsInitialized;
        s32 mIndex;
        TextureSampler mColorTargetTextureSampler;
        TextureSampler mDepthTargetTextureSampler;
        RenderBuffer mRenderBuffer;
        RenderTargetColor mColorTarget;
        TextureData* mpColorTextureData; // for "blur_mipmap"
        TextureSampler mColorTextureSampler;
        TextureData* mpDepthTextureData; // for "depth_mipmap"
        TextureSampler mDepthTextureSampler;
    };
    static_assert(sizeof(Context) == 0x834, "agl::pfx::DepthOfField::Context size mismatch");

    struct TempVignetting : public utl::IParameterObj // Not sure if superclass or member
    {
        utl::Parameter<s32> mType;
        utl::Parameter<sead::Vector2f> mRange;
        utl::Parameter<sead::Vector2f> mScale;
        utl::Parameter<sead::Vector2f> mTrans;
    };
    static_assert(sizeof(TempVignetting) == 0xCC, "agl::pfx::DepthOfField::TempVignetting size mismatch");

    struct VignettingShape
    {
        sead::Buffer<sead::Vector4f> mVertexBuffer;
        sead::Buffer<u16> mIndexBuffer;
        u32 mVertex[0x1D4 / sizeof(u32)]; // agl::VertexBuffer
        u32 mAttrib[0xF4 / sizeof(u32)]; // agl::VertexAttribute
        u32 mIndex[0x18 / sizeof(u32)]; // agl::IndexStream
    };
    static_assert(sizeof(VignettingShape) == 0x2F0, "agl::pfx::DepthOfField::VignettingShape size mismatch");

public:
    DepthOfField();
    ~DepthOfField();

    void initialize (s32 ctx_num = 1, sead::Heap* heap = NULL);

    void setEnable(bool enable)
    {
        mEnable.setValue(enable);
    }

    void setIndirectTextureData(const TextureData* p_texture_data);
    void setIndirectTextureTrans(const sead::Vector2f& trans);
    void setIndirectEnable(bool enable);

    ShaderMode draw(s32, const RenderBuffer&, f32, f32, ShaderMode = cShaderMode_Invalid) const;
    ShaderMode draw(s32, const RenderBuffer&, const TextureData&, bool, f32, f32, ShaderMode = cShaderMode_Invalid) const;

private:
    sead::Buffer<Context> mContext;
    u32 _1e8;
    f32 _1ec;
    u8 _1f0;
    f32 _1f4;
    sead::GraphicsContextMRT mGraphicsContext;
    utl::IParameterObj mParameterObj;
    utl::Parameter<bool> mEnable;
    utl::Parameter<bool> mNearEnable;
    utl::Parameter<bool> mFarEnable;
    utl::Parameter<bool> mDepthBlur;
    utl::Parameter<bool> mEnableVignettingColor;
    utl::Parameter<bool> mEnableVignettingBlur;
    utl::Parameter<bool> mEnableVignetting2Shape;
    utl::Parameter<bool> mEnableColorControl;
    utl::Parameter<bool> mIndirectEnable;
    utl::Parameter<f32> mStart;
    utl::Parameter<f32> mEnd;
    utl::Parameter<f32> mFarStart;
    utl::Parameter<f32> mFarEnd;
    utl::Parameter<f32> mLevel;
    utl::Parameter<f32> mDepthBlurAdd;
    utl::Parameter<f32> mSaturateMin;
    utl::Parameter<sead::Vector4f> mColorCtrlDepth;
    utl::Parameter<sead::Vector2f> mIndirectTexTrans;
    utl::Parameter<sead::Vector2f> mIndirectTexScale;
    utl::Parameter<f32> mIndirectTexRotate;
    utl::Parameter<f32> mIndirectScale;
    utl::Parameter<f32> mVignettingBlur;
    utl::Parameter<s32> mVignettingBlend; // -> enum VignettingBlendType
    utl::Parameter<sead::Color4f> mVignettingColor;
    TempVignetting mTempVignetting0;
    TempVignetting mTempVignetting1;
    utl::Parameter<sead::Color4f> mFarMulColor;
    u32 mDebugTexturePage[0x1DC / sizeof(u32)]; // agl::utl::DebugTexturePage
    ShaderProgram* mpCurrentProgramNearMask[2]; // sead::SafeArray
    ShaderProgram* mpCurrentProgramMipMap[2];
    const ShaderProgram* mpCurrentProgramDepthMask[2];
    ShaderProgram* mpCurrentProgramFinal[2];
    ShaderProgram* mpCurrentProgramVignetting;
    TextureData* mpIndirectTextureData;
    TextureSampler mIndirectTextureSampler;
    sead::Vector4f _ae0;
    sead::Vector3f mIndirectMatrixRow0;
    sead::Vector3f mIndirectMatrixRow1;
    VignettingShape mVignettingShape[2]; // sead::SafeArray
    u8 _10e8;
    // u32 _1e0[(0x10EC - 0x1E0) / sizeof(u32)];
};
static_assert(sizeof(DepthOfField) == 0x10EC, "agl::pfx::DepthOfField size mismatch");

} }
