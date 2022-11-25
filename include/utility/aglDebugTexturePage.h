#pragma once

#include <heap/seadDisposer.h>

namespace agl { namespace utl {

class DebugTexturePage : public sead::IDisposer
{
public:
    DebugTexturePage();

    virtual ~DebugTexturePage()
    {
        cleanUp();
    }

    void cleanUp();

private:
    u32 _10[0x1CC / sizeof(u32)];
};
static_assert(sizeof(DebugTexturePage) == 0x1DC, "agl::utl::DebugTexturePage size mismatch");

} }
