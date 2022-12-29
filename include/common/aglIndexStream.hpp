#pragma once

namespace agl {

inline void
IndexStream::draw(u32 instance_num, u32 base_vertex) const
{
    draw(0, getCount(), instance_num, base_vertex);
}

inline void
IndexStream::draw(u32 start, u32 count, u32 instance_num, u32 base_vertex) const
{
    if (count > 0)
    {
        // SEAD_ASSERT(( start + count ) <= getCount());
        GX2DrawIndexedEx(mPrimitiveType, count, GX2IndexFormat(mFormat), getBufferPtr(start), base_vertex, instance_num);
    }
}

}
