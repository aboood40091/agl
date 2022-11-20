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
    , mEnable                   ("enable",                      "有効",               &mParameterObj, true)
    , mNearEnable               ("near_enable",                 "近景ぼけ有効",           &mParameterObj, false)
    , mFarEnable                ("far_enable",                  "遠景ぼけ有効",           &mParameterObj, true)
    , mDepthBlur                ("depth_blur",                  "近景ぼけの深度ぼかし",       &mParameterObj, false)
    , mEnableVignettingColor    ("enable_vignetting_color",     "周辺減光有効",           &mParameterObj, false)
    , mEnableVignettingBlur     ("enable_vignetting_blur",      "周辺ぼけ有効",           &mParameterObj, false)
    , mEnableVignetting2Shape   ("enable_vignetting_2_shape",   "形状設定をわける",         &mParameterObj, false)
    , mEnableColorControl       ("enable_color_control",        "深度による色調整",         &mParameterObj, false)
    , mIndirectEnable           ("indirect_enable",             "インダイレクト処理有効",      &mParameterObj, false)
    , mStart                    ("start",                       "ぼけ開始深度",           &mParameterObj, 100.0f)
    , mEnd                      ("end",                         "ぼけ終了深度",           &mParameterObj, 200.0f)
    , mFarStart                 ("far_start",                   "近景ぼけ開始深度",         &mParameterObj, 120.0f)
    , mFarEnd                   ("far_end",                     "近景ぼけ終了深度",         &mParameterObj, 0.0f)
    , mLevel                    ("level",                       "ぼかしレベル",           &mParameterObj, 2.0f)
    , mDepthBlurAdd             ("depth_blur_add",              "深度ぼかし加算",          &mParameterObj, 0.0f)
    , mSaturateMin              ("saturate_min",                "彩度",               &mParameterObj, 1.0f)
    , mColorCtrlDepth           ("color_ctrl_depth",            "色調整距離",            &mParameterObj, sead::Vector4f(1000.0f, 2000.0f, 3000.0f, 4000.0f))
    , mIndirectTexTrans         ("indirect_tex_trans",          "テクスチャ行列Trans",     &mParameterObj, sead::Vector2f::zero)
    , mIndirectTexScale         ("indirect_tex_scale",          "テクスチャ行列Scale",     &mParameterObj, sead::Vector2f::ones)
    , mIndirectTexRotate        ("indirect_tex_rotate",         "テクスチャ行列Rotate",    &mParameterObj, 0.0f)
    , mIndirectScale            ("indirect_scale",              "ゆがみ幅",             &mParameterObj, 0.2f)
    , mVignettingBlur           ("vignetting_blur",             "周辺ぼけ強さ",           &mParameterObj, 1.0f)
    , mVignettingBlend          ("vignetting_blend",            "ブレンド",             &mParameterObj, 0)
    , mVignettingColor          ("vignetting_color",            "周辺減光色",            &mParameterObj, sead::Color4f(0.0f, 0.0f, 0.0f, 0.75f))
    , mTempVignetting0(this, "vignetting_shape_0")
    , mTempVignetting1(this, "vignetting_shape_1")
    , mFarMulColor              ("far_mul_color",               "乗算色",              &mParameterObj, sead::Color4f(1.0f, 1.0f, 1.0f, 1.0f))
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

} }
