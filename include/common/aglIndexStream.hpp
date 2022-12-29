#pragma once

namespace agl {

inline void
IndexStream::draw(u32 count, u32 start) const
{
    // SEAD_ASSERT(( start + count ) <= getCount());
    GX2DrawIndexedEx(mPrimitiveType, getCount(), GX2IndexFormat(mFormat), mpBuffer, start, count);
}

}
