/*
 *      /d/Gondor/arnor/fornost/c_wall.c
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
    set_short("at the outer wall of the ruins of Fornost");

    add_buildings();
    add_grass();
    add_outer_wall();
    add_rubble();
    add_ruins();
    add_stones();

    add_item("ground", BSN(
    "You study the ground and guess that a tunnel was mined under "+
    "the wall and that caused the cave-in of the wall."));
    add_item(({ "spot", "bare spot" }),
    "The ground here must have been poisoned somehow, as "+
    "nothing grows here.\n");
    add_item(({ "green area", "area" }),
    "You only discern that the area looks overgrown.\n");

    add_exit(FORNOST_DIR + "wall_tower", "northeast", 0, 3);
    add_exit(FORNOST_DIR + "f_garden", "west", 0, 2);
}

string
set_arnor_long()
{
    string desc;

    desc = "At this point the outer wall is completely destroyed. "+
    "It looks as if the ground was swept away and then the outer wall "+
    "caved in. Outside the wall there is a bare spot on the ground "+
    "where no grass grows. To the west is a green area, and to the "+
    "northeast the wall continues. ";
    desc += query_arnor_time();

    return BSN(desc);
}
