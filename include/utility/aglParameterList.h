#pragma once

#include <container/seadOffsetList.h>
#include <prim/seadSafeString.h>
#include <utility/aglResParameter.h>

namespace agl { namespace utl {

class IParameterObj;
class ParameterBase;

class IParameterList
{
public:
    IParameterList();

    void addObj(IParameterObj* child, const sead::SafeString& name);

protected:
    virtual bool preWrite_() const { return true; }
    virtual void postWrite_() const { }
    virtual bool preRead_() { return true; }
    virtual void postRead_() { }
    virtual bool isApply_(ResParameterList list) const { return list.getParameterListNameHash() == mNameHash; }
    virtual void callbackNotAppliable_(IParameterObj*, ParameterBase*, ResParameterObj) { }

    void setParameterListName_(const sead::SafeString& name);

protected:
    sead::OffsetList<IParameterList> mChildList;
    sead::OffsetList<IParameterObj> mChildObj;
    sead::FixedSafeString<64> mName;
    u32 mNameHash;
    u32 _70;
    sead::ListNode mListNode;
};
static_assert(sizeof(IParameterList) == 0x80, "agl::utl::IParameterList size mismatch");

} }
