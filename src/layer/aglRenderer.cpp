#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>

namespace agl { namespace lyr {

Renderer* Renderer::sInstance = NULL;

void Renderer::removeDrawMethod(const DrawMethod* p_draw_method)
{
    // SEAD_ASSERT(p_draw_method != nullptr);
    for (sead::Buffer<Layer*>::iterator itr = mpLayer.begin(), itr_end = mpLayer.end(); itr != itr_end; ++itr)
    {
        Layer* p_layer = *itr;
        if (p_layer)
            p_layer->removeDrawMethod(p_draw_method);
    }
}

} }
