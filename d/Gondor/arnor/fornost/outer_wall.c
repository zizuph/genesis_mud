/*
 *      /d/Gondor/arnor/fornost/outer_wall.c
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
    add_ground();
    add_ivy();
    add_outer_wall();
    add_rubble();
    add_ruins();
    add_stones();

    add_item("slope",
    "The green steep slope leads up to the top of the hill.\n");
    add_item("plaza", "No details can be seen from here.\n");
    add_item("foundation", "The foundation looks, despite its age, to be "+
    "in a very good condition.\n");

    add_exit(FORNOST_DIR + "plaza", "west", 0, 3);
    add_exit(FORNOST_DIR + "on_hill", "up", 0, 5);
}

string
set_arnor_long()
{
    string desc;

    desc = "At the outer wall of the ruins of Fornost. "+
    "The sturdy foundation of the outer wall is intact. The wall itself is "+
    "largely collapsed though. The parts that still remain seem remarkably "+
    "untouched by the ravages of time. Ivy grows on the wall. "+
    "An open plaza is to the west. To the southeast a steep slope leads up. ";
    desc += query_arnor_time();

    return BSN(desc);
}
