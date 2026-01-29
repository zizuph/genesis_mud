/*
 *   /d/Gondor/ithilien/poros/obj/chest.c
 *
 *   This is a decoy chest in the corsair captains office.
 *
 *   Talisan,  February 1996
 */

#pragma strict_types
inherit "/std/receptacle";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_name("chest");
    set_pname("chests");
    set_pshort("old wooden chests");
    set_adj(({"old", "wooden"}));
    set_long(BSN("This is an old wooden chest that has seen its "
      + "share of use over the years. An old rusting lock is set "
      + "into the front of the chest."));
    set_pick(45);

    add_item(({"lock", "rusting lock"}), BSN("The lock is extremly "
      + "rusted, and no longer functionable."));

    add_prop(CONT_I_VOLUME,   4000);
    add_prop(CONT_I_WEIGHT,   2500);
    add_prop(CONT_I_MAX_VOLUME, 16000);
    add_prop(CONT_I_MAX_WEIGHT, 80000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    1);
    add_prop(CONT_I_REDUCE_VOLUME, 150);
    add_prop(CONT_I_REDUCE_WEIGHT, 150);
    add_prop(OBJ_I_VALUE,90);    /* Value ?? cc*/
    add_prop(OBJ_M_NO_GET, 1);

}

