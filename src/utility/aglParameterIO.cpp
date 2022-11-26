#include <utility/aglParameterIO.h>

namespace agl { namespace utl {

IParameterIO::IParameterIO(const sead::SafeString& param_1, u32 param_2)
    : IParameterList()
    , mpDelegate(NULL)
    , _d4(sead::SafeString::cEmptyString)
{
    _80 = param_1;
    _cc = param_2;
    setParameterListName_("param_root");
}

} }
