#pragma once

#include <gfx/seadColor.h>
#include <math/seadVector.h>

namespace agl { namespace utl {

template <>
inline Parameter<sead::Vector2f>::Parameter(const sead::SafeString& name_1, const sead::SafeString& name_2, IParameterObj* p_obj, const sead::Vector2f& value)
    : ParameterBase()
{
    initializeListNode(name_1, name_2, "", p_obj);
    mValue.set(value);
}

template <>
inline Parameter<sead::Vector3f>::Parameter(const sead::SafeString& name_1, const sead::SafeString& name_2, IParameterObj* p_obj, const sead::Vector3f& value)
    : ParameterBase()
{
    initializeListNode(name_1, name_2, "", p_obj);
    mValue.set(value);
}

template <>
inline Parameter<sead::Vector4f>::Parameter(const sead::SafeString& name_1, const sead::SafeString& name_2, IParameterObj* p_obj, const sead::Vector4f& value)
    : ParameterBase()
{
    initializeListNode(name_1, name_2, "", p_obj);
    mValue.set(value);
}

static_assert(sizeof(Parameter<bool>) == 0x14);
static_assert(sizeof(Parameter<s32>) == 0x14);
static_assert(sizeof(Parameter<f32>) == 0x14);
static_assert(sizeof(Parameter<sead::Vector2f>) == 0x18);
static_assert(sizeof(Parameter<sead::Vector3f>) == 0x1C);
static_assert(sizeof(Parameter<sead::Vector4f>) == 0x20);
static_assert(sizeof(Parameter<sead::Color4f>) == 0x20);
static_assert(sizeof(Parameter< sead::FixedSafeString<32> >) == 0x3C);

template <>
inline ParameterBase::ParameterType
Parameter<bool>::getParameterType() const
{
    return cType_bool;
}

template <>
inline ParameterBase::ParameterType
Parameter<s32>::getParameterType() const
{
    return cType_int;
}

template <>
inline ParameterBase::ParameterType
Parameter<f32>::getParameterType() const
{
    return cType_float;
}

template <>
inline ParameterBase::ParameterType
Parameter<sead::Vector2f>::getParameterType() const
{
    return cType_vec2;
}

template <>
inline ParameterBase::ParameterType
Parameter<sead::Vector3f>::getParameterType() const
{
    return cType_vec3;
}

template <>
inline ParameterBase::ParameterType
Parameter<sead::Vector4f>::getParameterType() const
{
    return cType_vec4;
}

template <>
inline ParameterBase::ParameterType
Parameter<sead::Color4f>::getParameterType() const
{
    return cType_color;
}

template <>
inline ParameterBase::ParameterType
Parameter< sead::FixedSafeString<32> >::getParameterType() const
{
    return cType_str;
}

} }
