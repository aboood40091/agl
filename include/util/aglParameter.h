#pragma once

#include <prim/seadSafeString.h>

namespace sead {

class Heap;

}

namespace agl { namespace utl {

class IParameterObj;

class ParameterBase
{
public:
    enum ParameterType
    {
        cType_bool  = 0, // bool
        cType_float = 1, // f32
        cType_int   = 2, // s32
        cType_vec2  = 3, // sead::Vector2f
        cType_vec3  = 4, // sead::Vector3f
        cType_vec4  = 5, // sead::Vector4f
        cType_color = 6, // sead::Color4f
        cType_str   = 7  // sead::FixedSafeString<32>
    };

public:
    ParameterBase();
    virtual ~ParameterBase() { }

    virtual bool copy(const ParameterBase&);
    virtual void copyUnsafe(const ParameterBase&);
    virtual bool copyLerp(const ParameterBase&, const ParameterBase&, f32);

    virtual ParameterType getParameterType() const = 0;
    virtual const void* ptr() const = 0;
    virtual void* ptr() = 0;
    virtual const void* typePtr() const = 0;
    virtual void* typePtr() = 0;
    virtual size_t size() const = 0;
    virtual void clone(sead::Heap*, IParameterObj*) const = 0;

    virtual void postApplyResource_(const void*, size_t) { }

    void initializeListNode(const sead::SafeString&, const sead::SafeString&, const sead::SafeString&, IParameterObj*);

protected:
    u32 mHash;
    u32 _4;
    u32 _8;
};
static_assert(sizeof(ParameterBase) == 0x10, "agl::utl::ParameterBase size mismatch");

template <typename T>
class Parameter : public ParameterBase
{
public:
    Parameter(const sead::SafeString& name_1, const sead::SafeString& name_2, IParameterObj* p_obj, const T& value)
        : ParameterBase()
    {
        initializeListNode(name_1, name_2, "", p_obj);
        mValue = value;
    }

    ParameterType getParameterType() const;
    const void* ptr() const { return &mValue; }
    void* ptr() { return &mValue; }
    const void* typePtr() const { return &mValue; }
    void* typePtr() { return &mValue; }
    virtual size_t size() const { return sizeof(mValue); }
    void clone(sead::Heap*, IParameterObj*) const { /* Deleted in NSMBU */ }

    void setValue(const T& value) { mValue = value; }
    const T& getValue() const { return mValue; }

private:
    T mValue;
};

} }

#ifdef __cplusplus

#include <util/aglParameter.hpp>

#endif // __cplusplus
