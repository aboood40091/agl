#include <detail/aglRootNode.h>
#include <postfx/aglDepthOfField.h>

namespace agl { namespace pfx {

DepthOfField::DepthOfField()
    : utl::IParameterIO("agldof")
    , mContext()
    , _1e8(0)
    , _1ec(1.0f)
    , _1f0(1)
    , _1f4(1.0f)
    , mGraphicsContext()
    , mParameterObj()
    , mEnable                   (true,                                               "enable",                    "有効",              &mParameterObj)
    , mNearEnable               (false,                                              "near_enable",               "近景ぼけ有効",       &mParameterObj)
    , mFarEnable                (true,                                               "far_enable",                "遠景ぼけ有効",       &mParameterObj)
    , mDepthBlur                (false,                                              "depth_blur",                "近景ぼけの深度ぼかし", &mParameterObj)
    , mEnableVignettingColor    (false,                                              "enable_vignetting_color",   "周辺減光有効",      &mParameterObj)
    , mEnableVignettingBlur     (false,                                              "enable_vignetting_blur",    "周辺ぼけ有効",       &mParameterObj)
    , mEnableVignetting2Shape   (false,                                              "enable_vignetting_2_shape", "形状設定をわける",    &mParameterObj)
    , mEnableColorControl       (false,                                              "enable_color_control",      "深度による色調整",    &mParameterObj)
    , mIndirectEnable           (false,                                              "indirect_enable",           "インダイレクト処理有効", &mParameterObj)
    , mStart                    (100.0f,                                             "start",                     "ぼけ開始深度",       &mParameterObj)
    , mEnd                      (200.0f,                                             "end",                       "ぼけ終了深度",       &mParameterObj)
    , mFarStart                 (120.0f,                                             "far_start",                 "近景ぼけ開始深度",   &mParameterObj)
    , mFarEnd                   (0.0f,                                               "far_end",                   "近景ぼけ終了深度",   &mParameterObj)
    , mLevel                    (2.0f,                                               "level",                     "ぼかしレベル",         &mParameterObj)
    , mDepthBlurAdd             (0.0f,                                               "depth_blur_add",            "深度ぼかし加算",      &mParameterObj)
    , mSaturateMin              (1.0f,                                               "saturate_min",              "彩度",              &mParameterObj)
    , mColorCtrlDepth           (sead::Vector4f(1000.0f, 2000.0f, 3000.0f, 4000.0f), "color_ctrl_depth",          "色調整距離",        &mParameterObj)
    , mIndirectTexTrans         (sead::Vector2f::zero,                               "indirect_tex_trans",        "テクスチャ行列Trans",  &mParameterObj)
    , mIndirectTexScale         (sead::Vector2f::ones,                               "indirect_tex_scale",        "テクスチャ行列Scale",  &mParameterObj)
    , mIndirectTexRotate        (0.0f,                                               "indirect_tex_rotate",       "テクスチャ行列Rotate", &mParameterObj)
    , mIndirectScale            (0.2f,                                               "indirect_scale",            "ゆがみ幅",           &mParameterObj)
    , mVignettingBlur           (1.0f,                                               "vignetting_blur",           "周辺ぼけ強さ",        &mParameterObj)
    , mVignettingBlend          (0,                                                  "vignetting_blend",          "ブレンド",            &mParameterObj)
    , mVignettingColor          (sead::Color4f(0.0f, 0.0f, 0.0f, 0.75f),             "vignetting_color",          "周辺減光色",        &mParameterObj)
    , mTempVignetting0(this, "vignetting_shape_0")
    , mTempVignetting1(this, "vignetting_shape_1")
    , mFarMulColor              (sead::Color4f(1.0f, 1.0f, 1.0f, 1.0f),              "far_mul_color",             "乗算色",            &mParameterObj)
    , mDebugTexturePage()
  //, mpCurrentProgramNearMask() // TODO
  //, mpCurrentProgramMipMap() // TODO
  //, mpCurrentProgramDepthMask() // TODO
  //, mpCurrentProgramFinal() // TODO
  //, mpCurrentProgramVignetting(NULL)
    , mpIndirectTextureData(NULL)
    , mIndirectTextureSampler()
    , _ae0(sead::Vector4f::zero)
    , mIndirectMatrixRow0(1.0f, 0.0f, 0.0f)
    , mIndirectMatrixRow1(0.0f, 1.0f, 0.0f)
  //, mVignettingShape() // TODO
    , _10e8(1)
{
    addObj(&mParameterObj, "dof");

    {
        sead::SafeString _unused("被写界深度");
    }

    detail::RootNode::setNodeMeta(this, "Icon=SNAPSHOT");
}

DepthOfField::~DepthOfField()
{
    for (s32 i = 0; i < mContext.size(); i++)
        freeBuffer(i);

    mContext.freeBuffer();
}

ShaderMode DepthOfField::draw(s32 idx_ctx, const RenderBuffer& render_buffer, f32 near, f32 far, ShaderMode mode) const
{
    // SEAD_ASSERT(render_buffer.getRenderTargetDepth() != nullptr);
    return draw(idx_ctx, render_buffer, render_buffer.getRenderTargetDepth()->getTextureData(), false, near, far, mode);
}

ShaderMode DepthOfField::draw(s32 idx_ctx, const RenderBuffer& render_buffer, const TextureData& depth, bool view_depth, f32 near, f32 far, ShaderMode mode) const
{
    if (isEnable())
    {
        // SEAD_ASSERT(render_buffer.getRenderTargetColor() != nullptr);
        if (mContext[idx_ctx].mIsInitialized)
        {
            DrawArg arg(mContext[idx_ctx], render_buffer, depth, view_depth, near, far);
            if (enableBlurMipMapPass_())
            {
                allocBuffer(idx_ctx, render_buffer);
                {
                    // Pass 0
                    {
                        arg.mPass = 0;
                        mode = drawColorMipMap_(arg, mode);
                    }

                    if (enableDepthBlur_()) // Pass 1
                    {
                        arg.mPass = 1;
                        mode = drawDepthMipMap_(arg, mode);
                    }

                    // Pass 2
                    {
                        arg.mPass = 2;
                        mode = drawCompose_(arg, mode);
                    }
                }
                freeBuffer(idx_ctx);
            }

            if (enableSeparateVignettingPass_()) // Pass 3
            {
                arg.mPass = 3;
                mode = drawVignetting_(arg, mode);
            }
        }
    }

    return mode;
}

} }
