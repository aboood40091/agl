#pragma once

#include <util/aglParameterList.h>
#include <util/aglResParameter.h>

namespace agl { namespace utl {

class IParameterIO : public IParameterList
{
public:
    IParameterIO();
    IParameterIO(const sead::SafeString&, u32 = 0);

protected:
    virtual void callbackNotInterpolatable_(IParameterObj*, ParameterBase*, ResParameterObj, ResParameterObj, ResParameter, ResParameter, f32) { }

public:
    virtual bool save(const sead::SafeString&, u32) const;
    virtual void applyResParameterArchive(ResParameterArchive arc);
    virtual void applyResParameterArchiveLerp(ResParameterArchive arc_a, ResParameterArchive arc_b, f32);

protected:
    virtual void callbackInvalidVersion_(ResParameterArchive arc) { }

protected:
    sead::FixedSafeString<64> _80;
    u32 _cc;
    void* mpDelegate; // sead delegate
    sead::FixedSafeString<256> _d4;
};
static_assert(sizeof(IParameterIO) == 0x1E0, "agl::utl::IParameterIO size mismatch");

} }
