#include <detail/aglRootNode.h>
#include <detail/aglShaderHolder.h>
#include <postfx/aglDepthOfField.h>
#include <utility/aglDynamicTextureAllocator.h>

namespace agl { namespace pfx {

DepthOfField::DepthOfField()
    : utl::IParameterIO("agldof")
    , mContext()
    , _1e8(0)
    , _1ec(1.0f)
    , mEnableColorBlur(true)
    , _1f4(1.0f)
    , mGraphicsContext()
    , mParameterObj()
    , mEnable                   (true,                                               "enable",                    "�L��",              &mParameterObj)
    , mNearEnable               (false,                                              "near_enable",               "�ߌi�ڂ��L��",       &mParameterObj)
    , mFarEnable                (true,                                               "far_enable",                "���i�ڂ��L��",       &mParameterObj)
    , mDepthBlur                (false,                                              "depth_blur",                "�ߌi�ڂ��̐[�x�ڂ���", &mParameterObj)
    , mEnableVignettingColor    (false,                                              "enable_vignetting_color",   "���ӌ����L��",      &mParameterObj)
    , mEnableVignettingBlur     (false,                                              "enable_vignetting_blur",    "���ӂڂ��L��",       &mParameterObj)
    , mEnableVignetting2Shape   (false,                                              "enable_vignetting_2_shape", "�`��ݒ���킯��",    &mParameterObj)
    , mEnableColorControl       (false,                                              "enable_color_control",      "�[�x�ɂ��F����",    &mParameterObj)
    , mIndirectEnable           (false,                                              "indirect_enable",           "�C���_�C���N�g�����L��", &mParameterObj)
    , mStart                    (100.0f,                                             "start",                     "�ڂ��J�n�[�x",       &mParameterObj)
    , mEnd                      (200.0f,                                             "end",                       "�ڂ��I���[�x",       &mParameterObj)
    , mFarStart                 (120.0f,                                             "far_start",                 "�ߌi�ڂ��J�n�[�x",   &mParameterObj)
    , mFarEnd                   (0.0f,                                               "far_end",                   "�ߌi�ڂ��I���[�x",   &mParameterObj)
    , mLevel                    (2.0f,                                               "level",                     "�ڂ������x��",         &mParameterObj)
    , mDepthBlurAdd             (0.0f,                                               "depth_blur_add",            "�[�x�ڂ������Z",      &mParameterObj)
    , mSaturateMin              (1.0f,                                               "saturate_min",              "�ʓx",              &mParameterObj)
    , mColorCtrlDepth           (sead::Vector4f(1000.0f, 2000.0f, 3000.0f, 4000.0f), "color_ctrl_depth",          "�F��������",        &mParameterObj)
    , mIndirectTexTrans         (sead::Vector2f::zero,                               "indirect_tex_trans",        "�e�N�X�`���s��Trans",  &mParameterObj)
    , mIndirectTexScale         (sead::Vector2f::ones,                               "indirect_tex_scale",        "�e�N�X�`���s��Scale",  &mParameterObj)
    , mIndirectTexRotate        (0.0f,                                               "indirect_tex_rotate",       "�e�N�X�`���s��Rotate", &mParameterObj)
    , mIndirectScale            (0.2f,                                               "indirect_scale",            "�䂪�ݕ�",           &mParameterObj)
    , mVignettingBlur           (1.0f,                                               "vignetting_blur",           "���ӂڂ�����",        &mParameterObj)
    , mVignettingBlend          (0,                                                  "vignetting_blend",          "�u�����h",            &mParameterObj)
    , mVignettingColor          (sead::Color4f(0.0f, 0.0f, 0.0f, 0.75f),             "vignetting_color",          "���ӌ����F",        &mParameterObj)
    , mTempVignetting0(this, "vignetting_shape_0")
    , mTempVignetting1(this, "vignetting_shape_1")
    , mFarMulColor              (sead::Color4f(1.0f, 1.0f, 1.0f, 1.0f),              "far_mul_color",             "��Z�F",            &mParameterObj)
    , mDebugTexturePage()
    , mpIndirectTextureData(nullptr)
    , mIndirectTextureSampler()
    , _ae0(sead::Vector4f::zero)
    , mIndirectMatrixRow0(1.0f, 0.0f, 0.0f)
    , mIndirectMatrixRow1(0.0f, 1.0f, 0.0f)
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

void DepthOfField::initialize(s32 ctx_num, sead::Heap* heap)
{
    mContext.allocBuffer(ctx_num, heap);

    assignShaderProgram_();
    initVertex_(heap);
    initIndex_(heap);

    mIndirectTextureSampler.setWrap(
        cTextureWrapType_Repeat,
        cTextureWrapType_Repeat,
        cTextureWrapType_Repeat
    );

    for (sead::Buffer<Context>::iterator itr_ctx = mContext.begin(), itr_ctx_end = mContext.end(); itr_ctx != itr_ctx_end; ++itr_ctx)
    {
        itr_ctx->mIsInitialized = true;
        itr_ctx->mIndex = itr_ctx.getIndex();

        itr_ctx->mColorTargetTextureSampler.setFilter(
            cTextureFilterType_Linear,
            cTextureFilterType_Linear,
            cTextureMipFilterType_None
        );
        itr_ctx->mColorTargetTextureSampler.setUnk1(1);

        itr_ctx->mDepthTargetTextureSampler.setFilter(
            cTextureFilterType_Linear,
            cTextureFilterType_Linear,
            cTextureMipFilterType_None
        );
        itr_ctx->mDepthTargetTextureSampler.setUnk1(1);

        itr_ctx->mpColorTextureData = nullptr;

        itr_ctx->mColorTextureSampler.setFilter(
            cTextureFilterType_Linear,
            cTextureFilterType_Linear,
            cTextureMipFilterType_Point
        );

        itr_ctx->mpDepthTextureData = nullptr;

        itr_ctx->mDepthTextureSampler.setFilter(
            cTextureFilterType_Linear,
            cTextureFilterType_Linear,
            cTextureMipFilterType_Point
        );
    }

    mDebugTexturePage.setUp(ctx_num, "DepthOfField", heap);
}

#define MACRO_DOF_MIPMAP_COLOR_MIP 0
#define MACRO_DOF_MIPMAP_DEPTH_MIP 1

#define MACRO_DOF_DEPTH_MASK_DOF_FAR    0
#define MACRO_DOF_DEPTH_MASK_DOF_NEAR   1
#define MACRO_DOF_DEPTH_MASK_VIGNETTING 2
#define MACRO_DOF_DEPTH_MASK_VIEW_DEPTH 3

#define MACRO_DOF_FINAL_DOF_FAR     0
#define MACRO_DOF_FINAL_DOF_NEAR    1
#define MACRO_DOF_FINAL_VIGNETTING  2
#define MACRO_DOF_FINAL_VIEW_DEPTH  3

#define MACRO_DOF_VIGNETTING_VIGNETTING         0
#define MACRO_DOF_VIGNETTING_VIGNETTING_BLEND   1

static inline ShaderProgram* GetVariation(ShaderProgram& program, s32 macro_index, s32 value_index)
{
    /*  Getter of variation where macro at macro_index is set to value at value_index,
        and all other macros are set to values at index 0 respectively.                 */

    return program.getVariation(program.getVariationMacroValueVariationNum(macro_index) * value_index);
}

void DepthOfField::assignShaderProgram_()
{
    // MipMap
    {
        ShaderProgram& program_mipmap = detail::ShaderHolder::instance()->getShader(detail::ShaderHolder::cShader_DOFMipmap);

        mpCurrentProgramMipMap[0] = GetVariation(program_mipmap, MACRO_DOF_MIPMAP_COLOR_MIP, mEnableColorBlur ? 2 : 1);
        mpCurrentProgramMipMap[1] = GetVariation(program_mipmap, MACRO_DOF_MIPMAP_DEPTH_MIP, 1);
    }
    // DepthMask + Final
    {
        bool enable_depth_blur = enableDepthBlur_();
        s32 dof_near_idx =
            *mNearEnable
                ? (enable_depth_blur ? 2 : 1)
                : 0;

        s32 vignetting_idx = 0;
        if (*mEnableVignettingBlur)
        {
            vignetting_idx = 1;
            if (*mEnableVignettingColor && !enableSeparateVignettingPass_())
            {
                bool color_is_black = mVignettingColor->r == 0.0f &&
                                      mVignettingColor->g == 0.0f &&
                                      mVignettingColor->b == 0.0f;

                s32 idx = 2;
                if  (color_is_black)
                    idx = 1;

                vignetting_idx = idx;
                vignetting_idx++;
            }
        }

        s32 dof_far_idx = 0;
        if (*mFarEnable)
        {
            dof_far_idx = 1;
            if (*mEnableColorControl)
            {
                if (*mSaturateMin != 1.0f)
                    dof_far_idx = 2;

                if (    mFarMulColor->r != 1.0f ||
                        mFarMulColor->g != 1.0f ||
                        mFarMulColor->b != 1.0f     )
                    dof_far_idx += 2;
            }

            if (mpIndirectTextureData && *mIndirectEnable)
                dof_far_idx += 4;
        }

        const ShaderProgram& program_depth_mask = detail::ShaderHolder::instance()->getShader(detail::ShaderHolder::cShader_DOFDepthMask);

        s32 depth_mask_variation_idx = program_depth_mask.getVariationMacroValueVariationNum(MACRO_DOF_DEPTH_MASK_DOF_FAR)      * (dof_far_idx != 0) +
                                       program_depth_mask.getVariationMacroValueVariationNum(MACRO_DOF_DEPTH_MASK_DOF_NEAR)     * dof_near_idx +
                                       program_depth_mask.getVariationMacroValueVariationNum(MACRO_DOF_DEPTH_MASK_VIGNETTING)   * *mEnableVignettingBlur;

        mpCurrentProgramDepthMask[0] = program_depth_mask.getVariation(depth_mask_variation_idx);
        mpCurrentProgramDepthMask[1] = program_depth_mask.getVariation(depth_mask_variation_idx | 1);

        ShaderProgram& program_final = detail::ShaderHolder::instance()->getShader(detail::ShaderHolder::cShader_DOFFinal);

        s32 final_variation_idx = program_final.getVariationMacroValueVariationNum(MACRO_DOF_FINAL_DOF_FAR)     * dof_far_idx +
                                  program_final.getVariationMacroValueVariationNum(MACRO_DOF_FINAL_DOF_NEAR)    * dof_near_idx +
                                  program_final.getVariationMacroValueVariationNum(MACRO_DOF_FINAL_VIGNETTING)  * vignetting_idx;

        mpCurrentProgramFinal[0] = program_final.getVariation(final_variation_idx);
        mpCurrentProgramFinal[1] = program_final.getVariation(final_variation_idx | 1);
    }
    // Vignetting
    {
        ShaderProgram& program_vignetting = detail::ShaderHolder::instance()->getShader(detail::ShaderHolder::cShader_DOFVignetting);

        bool vignetting_color_is_black = mVignettingColor->r == 0.0f &&
                                         mVignettingColor->g == 0.0f &&
                                         mVignettingColor->b == 0.0f;

        s32 vignetting_blend_idx;
        switch (VignettingBlendType(*mVignettingBlend))
        {
        default:                        vignetting_blend_idx = 0; break;
        case cVignettingBlend_White:    vignetting_blend_idx = 1; break;
        case cVignettingBlend_Black:    vignetting_blend_idx = 2; break;
        }

        s32 vignetting_variation_idx = program_vignetting.getVariationMacroValueVariationNum(MACRO_DOF_VIGNETTING_VIGNETTING)       * s32(!vignetting_color_is_black) +
                                       program_vignetting.getVariationMacroValueVariationNum(MACRO_DOF_VIGNETTING_VIGNETTING_BLEND) * vignetting_blend_idx;

        mpCurrentProgramVignetting = program_vignetting.getVariation(vignetting_variation_idx);
    }
}

ShaderMode DepthOfField::draw(s32 ctx_index, const RenderBuffer& render_buffer, f32 near, f32 far, ShaderMode mode) const
{
    // SEAD_ASSERT(render_buffer.getRenderTargetDepth() != nullptr);
    return draw(ctx_index, render_buffer, render_buffer.getRenderTargetDepth()->getTextureData(), false, near, far, mode);
}

ShaderMode DepthOfField::draw(s32 ctx_index, const RenderBuffer& render_buffer, const TextureData& depth, bool view_depth, f32 near, f32 far, ShaderMode mode) const
{
    if (isEnable())
    {
        // SEAD_ASSERT(render_buffer.getRenderTargetColor() != nullptr);
        if (mContext[ctx_index].mIsInitialized)
        {
            DrawArg arg(mContext[ctx_index], render_buffer, depth, view_depth, near, far);
            if (enableBlurMipMapPass_())
            {
                allocBuffer(ctx_index, render_buffer);
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
                freeBuffer(ctx_index);
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

void DepthOfField::allocBuffer(s32 ctx_index, const RenderBuffer& render_buffer) const
{
    const RenderTargetColor* color = render_buffer.getRenderTargetColor();
    // SEAD_ASSERT(color != nullptr);

    allocBuffer(ctx_index, color->getTextureData().getTextureFormat(), color->getTextureData().getWidth(), color->getTextureData().getHeight());
}

void DepthOfField::allocBuffer(s32 ctx_index, TextureFormat format, s32 width, s32 height) const
{
    Context* p_ctx = &(mContext[ctx_index]);
    utl::DynamicTextureAllocator* p_allocator = utl::DynamicTextureAllocator::instance();

    s32 color_blur_mipmap_num;
    s32 color_blur_width;
    s32 color_blur_height;

    if (*mIndirectEnable && roundDown_(*mLevel) == 0)
    {
        color_blur_mipmap_num = roundUp_(*mLevel) + 1;

        color_blur_width  = width;
        color_blur_height = height;
    }
    else
    {
        color_blur_mipmap_num = sead::Mathi::max(1, roundUp_(*mLevel));

        color_blur_width  = width  / 2;
        color_blur_height = height / 2;
    }

    p_ctx->mpColorTextureData = p_allocator->alloc(
        "dof_blur_mipmap",
        format,
        color_blur_width,
        color_blur_height,
        color_blur_mipmap_num
    );
    // SEAD_ASSERT(p_ctx->mpColorTextureData != nullptr);
    p_ctx->mColorTextureSampler.applyTextureData(*p_ctx->mpColorTextureData);

    if (enableDepthBlur_())
    {
        p_ctx->mpDepthTextureData = p_allocator->alloc(
            "dof_depth_mipmap",
            cTextureFormat_R8_uNorm,
            width  / 2,
            height / 2,
            roundUp_(*mDepthBlurAdd) + 1
        );
        // SEAD_ASSERT(p_ctx->mpDepthTextureData != nullptr);
        p_ctx->mDepthTextureSampler.applyTextureData(*p_ctx->mpDepthTextureData);
    }
}

void DepthOfField::freeBuffer(s32 ctx_index) const
{
    Context* p_ctx = &(mContext[ctx_index]);
    utl::DynamicTextureAllocator* p_allocator = utl::DynamicTextureAllocator::instance();

    if (p_ctx->mpColorTextureData)
    {
        p_allocator->free(p_ctx->mpColorTextureData);
        p_ctx->mpColorTextureData = nullptr;
    }
    if (p_ctx->mpDepthTextureData)
    {
        p_allocator->free(p_ctx->mpDepthTextureData);
        p_ctx->mpDepthTextureData = nullptr;
    }
}

bool DepthOfField::enableDepthOfField_() const
{
    return *mNearEnable || *mFarEnable;
}

bool DepthOfField::enableBlurMipMapPass_() const
{
    return enableDepthOfField_() || *mEnableVignettingBlur;
}

bool DepthOfField::enableDepthBlur_() const
{
    return *mNearEnable && *mDepthBlur;
}

bool DepthOfField::enableDifferntShape_() const
{
    return *mEnableVignettingColor && *mEnableVignettingBlur && *mEnableVignetting2Shape;
}

bool DepthOfField::enableSeparateVignettingPass_() const
{
    // Implementing this in a single line mismatches :^)

    if (*mEnableVignettingColor)
        if (enableDifferntShape_() || *mVignettingBlend != 0 || !*mEnableVignettingBlur)
            return true;

    return false;
}

DepthOfField::DrawArg::DrawArg(Context& ctx, const RenderBuffer& render_buffer, const TextureData& depth, bool view_depth, f32 near, f32 far)
    : mCtx(ctx)
    , mRenderBuffer(render_buffer)
    , mNear(near)
    , mFar(far)
    , mWidth(mRenderBuffer.getRenderTargetColor()->getTextureData().getWidth())
    , mHeight(mRenderBuffer.getRenderTargetColor()->getTextureData().getHeight())
    , mViewDepth(view_depth)
{
    mCtx.mColorTargetTextureSampler.applyTextureData(mRenderBuffer.getRenderTargetColor()->getTextureData());
    mCtx.mDepthTargetTextureSampler.applyTextureData(depth);
}

DepthOfField::TempVignetting::TempVignetting(DepthOfField* p_dof, const sead::SafeString& param_name)
    : utl::IParameterObj()
    , mType (0,                           "type",  "�`��",    this)
    , mRange(sead::Vector2f(0.25f, 1.0f), "range", "�ω���",  this)
    , mScale(sead::Vector2f(1.0f, 1.0f),  "scale", "�X�P�[��",  this)
    , mTrans(sead::Vector2f(0.0f, 0.0f),  "trans", "�I�t�Z�b�g", this)
{
    p_dof->addObj(this, param_name);
}

} }
