#pragma once

//#include <container/seadOffsetList.h>
#include <prim/seadSafeString.h>
#include <utility/aglResParameter.h>

namespace agl { namespace utl {

class IParameterObj
{
public:
    IParameterObj();

protected:
    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const { }
    virtual bool preRead_() { return true; }
    virtual void postRead_() { }
    virtual bool isApply_(ResParameterObj obj) const { return obj.getParameterObjNameHash() == mNameHash; }

protected:
    u32 _0[4];  // sead::OffsetList<idk>
    sead::FixedSafeString<64> _10;
    u32 mNameHash;
    u32 _60;
    u32 _64;
    u32 _68;
};
static_assert(sizeof(IParameterObj) == 0x70, "agl::utl::IParameterObj size mismatch");

} }
