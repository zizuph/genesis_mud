/*
 *      /d/Gondor/arnor/fornost/wall_tower.c
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
    set_short("at a wall tower in the ruins of Fornost");

    add_buildings();
    add_cracks();
    add_grass();
    add_ground();
    add_outer_wall();
    add_rubble();
    add_ruins();
    add_stones();

    add_item(({ "tower", "wall tower" }), BSN(
    "Even though the lower parts of the tower still stand, they show signs "+
    "of being battered. Here and there you can see cracked stones."));
    add_item(({ "rock", "black rock" }), BSN(
    "A black rock, made of lava-stone, cracked as if it was thrown here "+
    "by great force."));

    add_exit(FORNOST_DIR + "guard_quarter", "west", 0, 2);
    add_exit(FORNOST_DIR + "c_wall", "southwest", 0, 3);
    add_exit(FORNOST_DIR + "hill_top", "up", 0, 5);
}

string
set_arnor_long()
{
    string desc;

    desc = "At a wall tower in the outer wall in the ruins of Fornost. "+
    "The top of the wall has been knocked down, a few feet of the wall "+
    "still stands. The walls of the tower has also been breached, they are "+
    "only as high as a tall man at the highest point. "+
    "Inside the tower is a black rock. To the southwest the wall "+
    "continues, and to the east a slope leads up. ";
    desc += query_arnor_time();

    return BSN(desc);
}
