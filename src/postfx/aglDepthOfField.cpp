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
    , mEnable                   ("enable",                      "�L��",               &mParameterObj, true)
    , mNearEnable               ("near_enable",                 "�ߌi�ڂ��L��",           &mParameterObj, false)
    , mFarEnable                ("far_enable",                  "���i�ڂ��L��",           &mParameterObj, true)
    , mDepthBlur                ("depth_blur",                  "�ߌi�ڂ��̐[�x�ڂ���",       &mParameterObj, false)
    , mEnableVignettingColor    ("enable_vignetting_color",     "���ӌ����L��",           &mParameterObj, false)
    , mEnableVignettingBlur     ("enable_vignetting_blur",      "���ӂڂ��L��",           &mParameterObj, false)
    , mEnableVignetting2Shape   ("enable_vignetting_2_shape",   "�`��ݒ���킯��",         &mParameterObj, false)
    , mEnableColorControl       ("enable_color_control",        "�[�x�ɂ��F����",         &mParameterObj, false)
    , mIndirectEnable           ("indirect_enable",             "�C���_�C���N�g�����L��",      &mParameterObj, false)
    , mStart                    ("start",                       "�ڂ��J�n�[�x",           &mParameterObj, 100.0f)
    , mEnd                      ("end",                         "�ڂ��I���[�x",           &mParameterObj, 200.0f)
    , mFarStart                 ("far_start",                   "�ߌi�ڂ��J�n�[�x",         &mParameterObj, 120.0f)
    , mFarEnd                   ("far_end",                     "�ߌi�ڂ��I���[�x",         &mParameterObj, 0.0f)
    , mLevel                    ("level",                       "�ڂ������x��",           &mParameterObj, 2.0f)
    , mDepthBlurAdd             ("depth_blur_add",              "�[�x�ڂ������Z",          &mParameterObj, 0.0f)
    , mSaturateMin              ("saturate_min",                "�ʓx",               &mParameterObj, 1.0f)
    , mColorCtrlDepth           ("color_ctrl_depth",            "�F��������",            &mParameterObj, sead::Vector4f(1000.0f, 2000.0f, 3000.0f, 4000.0f))
    , mIndirectTexTrans         ("indirect_tex_trans",          "�e�N�X�`���s��Trans",     &mParameterObj, sead::Vector2f::zero)
    , mIndirectTexScale         ("indirect_tex_scale",          "�e�N�X�`���s��Scale",     &mParameterObj, sead::Vector2f::ones)
    , mIndirectTexRotate        ("indirect_tex_rotate",         "�e�N�X�`���s��Rotate",    &mParameterObj, 0.0f)
    , mIndirectScale            ("indirect_scale",              "�䂪�ݕ�",             &mParameterObj, 0.2f)
    , mVignettingBlur           ("vignetting_blur",             "���ӂڂ�����",           &mParameterObj, 1.0f)
    , mVignettingBlend          ("vignetting_blend",            "�u�����h",             &mParameterObj, 0)
    , mVignettingColor          ("vignetting_color",            "���ӌ����F",            &mParameterObj, sead::Color4f(0.0f, 0.0f, 0.0f, 0.75f))
    , mTempVignetting0(this, "vignetting_shape_0")
    , mTempVignetting1(this, "vignetting_shape_1")
    , mFarMulColor              ("far_mul_color",               "��Z�F",              &mParameterObj, sead::Color4f(1.0f, 1.0f, 1.0f, 1.0f))
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
        sead::SafeString _unused("��ʊE�[�x");
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
