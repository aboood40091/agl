#include <layer/aglLayer.h>
#include <layer/aglRenderStep.h>

namespace agl { namespace lyr {

s32 Layer::removeDrawMethod(const DrawMethod* p_draw_method)
{
    // SEAD_ASSERT(p_draw_method != nullptr);
    s32 ret = 0;
    for (sead::Buffer<RenderStep>::iterator itr = mRenderStep.begin(), itr_end = mRenderStep.end(); itr != itr_end; ++itr)
        ret += (*itr).remove(p_draw_method);
    return ret;
}

} }
