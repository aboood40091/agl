#pragma once

#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace agl { namespace detail {

class RootNode
{
    SEAD_SINGLETON_DISPOSER(RootNode)

public:
    RootNode();
    virtual ~RootNode();

    static void setNodeMeta(/* sead::hostio::Node* */ void*, const sead::SafeString&);
};

} }
