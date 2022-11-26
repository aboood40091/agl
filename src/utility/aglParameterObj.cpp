#include <utility/aglParameter.h>
#include <utility/aglParameterObj.h>

namespace agl { namespace utl {

IParameterObj::IParameterObj()
    : mChildHash(0xFFFFFFFF)
{
    mChildParameter.initOffset(offsetof(ParameterBase, mListNode));

    mName = sead::SafeString::cEmptyString;
}

} }
