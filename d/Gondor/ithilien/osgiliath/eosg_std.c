/*
 *	/d/Gondor/ithilien/osgiliath/eosg_std.c
 *
 *	Coded by Elessar
 *
 *	Modification log:
 *	 1-Feb-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

public int
check_allow()
{
    object stopper;

    if (query_friend_or_foe(TP) < 0  &&
        (rq_stage() >= RQ_OSGILIATH_BROKEN ||
        rq_stage() < RQ_OSGILIATH_FIXED))
        return 0;
    else if ((rq_stage() < RQ_OSGILIATH_BROKEN  ||
      rq_stage() >= RQ_OSGILIATH_FIXED) &&
      (query_friend_or_foe(TP) > 0  ||
        present("_ithilien_badge",TP)))
        return 0;
    if (stopper = present("_stopping_npc",TO)) 
    {
        if (CAN_SEE(stopper,TP) &&
            (stopper->query_skill(SS_AWARENESS) > TP->query_skill(SS_SNEAK)/2)) 
        {
            write(CAP(LANG_ADDART(stopper->query_race_name()))
              + " stops you from going that way.\n");
            return 1;
        }
        write("You sneak past the " + stopper->query_race_name() + "!\n");
    }
    return 0;
}
