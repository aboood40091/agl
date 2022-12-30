#include <detail/aglShaderHolder.h>
#include <utility/aglImageFilter2D.h>

namespace agl { namespace utl {

ShaderMode ImageFilter2D::drawTextureQuadTriangle(const TextureSampler& sampler, ShaderMode mode)
{
    const ShaderProgram* program =
        detail::ShaderHolder::instance()->getShader(detail::ShaderHolder::cShader_Texture)
            .getVariation(1);

    mode = program->activate(mode);
    drawQuadTriangle(*program, sampler);

    return mode;
}

} }
