#include <common/aglTextureData.h>
#include <prim/seadMemUtil.h>

namespace agl {

TextureData::TextureData()
    : mWidth(1)
    , mHeight(1)
    , mDepth(1)
    , mImageByteSize(1)
    , mCompR(4)
    , mCompG(4)
    , mCompB(4)
    , mCompA(4)
{
    sead::MemUtil::fillZero(&mSurface, sizeof(GX2Surface));
}

}
