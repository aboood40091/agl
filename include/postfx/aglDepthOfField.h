#pragma once

#include <common/aglShaderEnum.h>

namespace agl {

class RenderBuffer;
class TextureData;

namespace pfx {

class DepthOfField
{
public:
    DepthOfField();
    ~DepthOfField();

    ShaderMode draw(s32, const RenderBuffer&, f32, f32, ShaderMode = cShaderMode_Invalid) const;
    ShaderMode draw(s32, const RenderBuffer&, const TextureData&, bool, f32, f32, ShaderMode = cShaderMode_Invalid) const;

private:
    u32 _0[0x10ec / sizeof(u32)];
};
static_assert(sizeof(DepthOfField) == 0x10ec, "agl::pfx::DepthOfField size mismatch");

} }
