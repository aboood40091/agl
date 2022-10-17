#pragma once

#include <detail/aglGX2.h>

namespace agl {

inline void
RenderTargetColor::expandAuxBuffer() const
{
    if (!mpAuxBuffer)
        return;

    if (mUpdateRegs)
    {
        initRegs_();
        mUpdateRegs = false;
    }

    GX2ExpandAAColorBuffer(&mInnerBuffer);
    driver::GX2Resource::instance()->restoreContextState();
}

inline void
RenderTargetDepth::expandHiZBuffer() const
{
    if (!mpHiZBuffer)
        return;

    if (mUpdateRegs)
    {
        initRegs_();
        mUpdateRegs = false;
    }

    GX2ExpandDepthBuffer(&mInnerBuffer);
    driver::GX2Resource::instance()->restoreContextState();
}

}
