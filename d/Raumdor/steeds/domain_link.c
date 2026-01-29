/*
 * - /d/Raumdor/domain_link.c
 *
 * The master preloader for the Raumdor domain.
 */
#pragma no_inherit
#pragma no_clone
#pragma save_binary
#pragma strict_types

#include "defs.h"
inherit "/std/domain_link";

#include <const.h>

public void
remove_object()	{ destruct(); }

public void
preload_link()
{
    preload("/d/Raumdor/lib/clock");
    
    // spy quest npc spawn.
    preload("/d/Raumdor/common/forest/wforest73");
}

public void
armageddon(int level)
{
    // Make sure the RTS manager shuts down nicely.
    if (level == ARMAGEDDON_SHUTDOWN)
    {
        CLOCK->stop_clock();
    }
}

