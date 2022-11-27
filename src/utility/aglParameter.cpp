#include <codec/seadHashCRC32.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>

namespace agl { namespace utl {

ParameterBase::ParameterBase()
{
    initializeListNode("default", "parameter", "", NULL);
}

bool ParameterBase::copy(const ParameterBase& parameter)
{
    if (getParameterType() != parameter.getParameterType() ||
        mHash != parameter.mHash)
    {
        return false;
    }

    copyUnsafe(parameter);
    return true;
}

void ParameterBase::copyUnsafe(const ParameterBase& parameter)
{
    u8* dst = static_cast<u8*>(ptr());
    const u8* src = static_cast<const u8*>(parameter.ptr());
    s32 len = size();

    for (s32 i = 0; i < len; i++)
        *dst++ = *src++;
}

bool ParameterBase::copyLerp(const ParameterBase& parameter_a, const ParameterBase& parameter_b, f32 t)
{
    if (getParameterType() != parameter_a.getParameterType() ||
        mHash != parameter_a.mHash ||
        getParameterType() != parameter_b.getParameterType() ||
        mHash != parameter_b.mHash)
    {
        return false;
    }

    switch (getParameterType())
    {
    case cType_bool:
    case cType_int:
    case cType_string32:
        copyUnsafe(parameter_a);
        break;
    case cType_f32:
        copyLerp_<f32>(parameter_a, parameter_b, t);
        break;
    case cType_vec2:
        copyLerp_<sead::Vector2f>(parameter_a, parameter_b, t);
        break;
    case cType_vec3:
        copyLerp_<sead::Vector3f>(parameter_a, parameter_b, t);
        break;
    case cType_vec4:
        copyLerp_<sead::Vector4f>(parameter_a, parameter_b, t);
        break;
    case cType_color:
        copyLerp_<sead::Color4f>(parameter_a, parameter_b, t);
        break;
    }
    return true;
}

void ParameterBase::initializeListNode(const sead::SafeString& name, const sead::SafeString& label, const sead::SafeString& meta, IParameterObj* p_obj)
{
    mHash = calcHash(name);

    if (p_obj)
        p_obj->pushBackListNode(this);
}

u32 ParameterBase::calcHash(const sead::SafeString& s)
{
    return sead::HashCRC32::calcHash(s.cstr(), s.calcLength());
}

} }
