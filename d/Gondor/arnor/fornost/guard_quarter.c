 /*
 *      /d/Gondor/arnor/fornost/guard_quarter.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/arnor/fornost/fornost.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_fornost()
{
    set_short("the remnants of a great building");

    add_buildings();
    add_grass();
    add_ground();
    add_roof();
    add_rubble();
    add_ruins();

    add_item(({ "pillars", "serie of pillars" }), BSN(
       "They have been toppled of at various heights. None is higher than "
     + "a few feet."));
    add_item(({ "floor", "dark floor" }), BSN(
    "The floor is broken in many places. It's mostly covered by ivy. "+
    "Close to one of the pillars, underneath the ivy, there seems to be "+
    "some sort of large crack in the floor."));
    add_item(({ "crack", "large crack" }),
    "The crack is deep and dark. There is a slab of stone covering a "+
    "part of it.\n");
    add_item(({ "stone", "slab of stone" }),
    "It could possibly be moved.\n");
    add_item(({ "", "" }), "");
    add_item("stones", "dark, has weathered many seasons");

    add_exit(FORNOST_DIR + "wall_tower", "east", 0, 2);
}

string
set_arnor_long()
{
    string desc;

    desc = "The remnants of a great building in the ruins of Fornost. "+
    "The large floor is flagged in dark stone. Around the floor rise a "+
    "serie of pillars, pocked and worn. These at one time had supported "+
    "a vast roof; now of roof there is none and the walls are but dreams "+
    "of the far past. ";
    desc += query_arnor_time();

    return BSN(desc);
}
