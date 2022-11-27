#pragma once

#include <common/aglIndexStream.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <common/aglShaderEnum.h>
#include <common/aglTextureSampler.h>
#include <common/aglVertexAttribute.h>
#include <common/aglVertexBuffer.h>
#include <container/seadBuffer.h>
#include <gfx/seadGraphicsContextMRT.h>
#include <hostio/seadHostIODummy.h>
#include <utility/aglDebugTexturePage.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterIO.h>
#include <utility/aglParameterObj.h>

namespace agl {

class RenderBuffer;
class TextureData;

namespace pfx {

class DepthOfField : public utl::IParameterIO, public sead::hostio::Node
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

    struct DrawArg
    {
        DrawArg(Context& ctx, const RenderBuffer& render_buffer, const TextureData& depth, bool view_depth, f32 near, f32 far);

        s32 mPass;
        Context& mCtx;
        const RenderBuffer& mRenderBuffer;
        f32 mNear;
        f32 mFar;
        u32 mWidth;
        u32 mHeight;
        bool mViewDepth;
    };
    static_assert(sizeof(DrawArg) == 0x20, "agl::pfx::DepthOfField::DrawArg size mismatch");

    struct TempVignetting : utl::IParameterObj
    {
        TempVignetting(DepthOfField* p_dof, const sead::SafeString& param_name);

        utl::Parameter<s32> mType;
        utl::Parameter<sead::Vector2f> mRange;
        utl::Parameter<sead::Vector2f> mScale;
        utl::Parameter<sead::Vector2f> mTrans;
    };
    static_assert(sizeof(TempVignetting) == 0xCC, "agl::pfx::DepthOfField::TempVignetting size mismatch");

    struct Vertex
    {
        sead::Vector4f data;
    };

    struct VignettingShape
    {
        sead::Buffer<Vertex> mVertexBuffer;
        sead::Buffer<u16> mIndexBuffer;
        VertexBuffer mVertex;
        VertexAttribute mAttrib; // 0xF4
        IndexStream mIndex; // 0x18
    };
    static_assert(sizeof(VignettingShape) == 0x2F0, "agl::pfx::DepthOfField::VignettingShape size mismatch");

public:
    DepthOfField();
    virtual ~DepthOfField();

    void initialize (s32 ctx_num = 1, sead::Heap* heap = NULL);

    bool isEnable() const
    {
        return mEnable.getValue();
    }

    void setEnable(bool enable)
    {
        mEnable.setValue(enable);
    }

    ShaderMode draw(s32 ctx_index, const RenderBuffer& render_buffer, f32 near, f32 far, ShaderMode mode = cShaderMode_Invalid) const;
    ShaderMode draw(s32 ctx_index, const RenderBuffer& render_buffer, const TextureData& depth, bool view_depth, f32 near, f32 far, ShaderMode mode = cShaderMode_Invalid) const;

    void allocBuffer(s32 ctx_index, const RenderBuffer& render_buffer) const;
    void allocBuffer(s32 ctx_index, TextureFormat format, s32 width, s32 height) const;
    void freeBuffer(s32 ctx_index) const;

private:
    bool enableDepthOfField_() const;
    bool enableBlurMipMapPass_() const;
    bool enableDepthBlur_() const;
    bool enableSeparateVignettingPass_() const;

    ShaderMode drawColorMipMap_(const DrawArg& arg, ShaderMode mode) const;
    ShaderMode drawDepthMipMap_(const DrawArg& arg, ShaderMode mode) const;
    ShaderMode drawCompose_(const DrawArg& arg, ShaderMode mode) const;
    ShaderMode drawVignetting_(const DrawArg& arg, ShaderMode mode) const;

public:
    void setIndirectTextureData(const TextureData* p_texture_data);
    void setIndirectEnable(bool enable);

    void setIndirectTextureTrans(const sead::Vector2f& trans);

private:
    mutable sead::Buffer<Context> mContext;
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
    utl::DebugTexturePage mDebugTexturePage;
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
