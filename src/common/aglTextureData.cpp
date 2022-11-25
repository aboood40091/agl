#include <common/aglTextureData.h>
#include <prim/seadMemUtil.h>

namespace agl {

TextureData::TextureData()
    : mWidth(1)
    , mHeight(1)
    , mDepth(1)
    , mImageByteSize(1)
    , mCompR(cTextureCompSel_0)
    , mCompG(cTextureCompSel_0)
    , mCompB(cTextureCompSel_0)
    , mCompA(cTextureCompSel_0)
{
    sead::MemUtil::fillZero(&mSurface, sizeof(GX2Surface));
}

}
