#include <codec/seadHashCRC32.h>
#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>

namespace agl { namespace utl {

ParameterBase::ParameterBase()
{
    initializeListNode("default", "parameter", "", NULL);
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
