#pragma once

#include <common/aglShaderEnum.h>

namespace agl {

class ShaderProgram;
class TextureSampler;

namespace utl {

class ImageFilter2D
{
public:
    static void drawQuadTriangle(const ShaderProgram& program, const TextureSampler& sampler);
    static ShaderMode drawTextureQuadTriangle(const TextureSampler& sampler, ShaderMode mode);
};

} }
