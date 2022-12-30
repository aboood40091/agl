#pragma once

#include <common/aglShaderEnum.h>

namespace agl {

class TextureSampler;

namespace utl {

class ImageFilter2D
{
public:
    static ShaderMode drawTextureQuadTriangle(const TextureSampler& sampler, ShaderMode mode);
};

} }
