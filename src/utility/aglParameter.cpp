#include <codec/seadHashCRC32.h>
#include <utility/aglParameter.h>

namespace agl { namespace utl {

u32 ParameterBase::calcHash(const sead::SafeString& s)
{
    return sead::HashCRC32::calcHash(s.cstr(), s.calcLength());
}

} }
