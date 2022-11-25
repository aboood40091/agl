#pragma once

//#include <container/seadOffsetList.h>
#include <prim/seadSafeString.h>
#include <utility/aglResParameter.h>

namespace agl { namespace utl {

class IParameterObj;
class ParameterBase;

class IParameterList
{
public:
    IParameterList();

    void addObj(IParameterObj*, const sead::SafeString&);

protected:
    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const { }
    virtual bool preRead_() { return true; }
    virtual void postRead_() { }
    virtual bool isApply_(ResParameterList list) const { return list.getParameterListNameHash() == mNameHash; }
    virtual void callbackNotAppliable_(IParameterObj*, ParameterBase*, ResParameterObj) { }

protected:
    u32 _0[4];  // sead::OffsetList<idk>
    u32 _10[4]; // sead::OffsetList<idk>
    sead::FixedSafeString<64> _20;
    u32 mNameHash;
    u32 _70;
    u32 _74;
    u32 _78;
};
static_assert(sizeof(IParameterList) == 0x80, "agl::utl::IParameterList size mismatch");

} }
