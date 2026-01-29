/*
 *      /d/Gondor/arnor/fornost/on_hill.c
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
    set_short("on top of a hill just outside the ruins of Fornost");

    add_grass();
    add_hills();
    add_ivy();
    add_ruins();

    add_item("ridge", BSN(
    "The ridge is connecting this hill with the other hills "+
    "spreading out northeast."));
    add_item("tower", BSN(
    "The tower seems to be of two storeys. On top of the tower is a "+
    "battlement."));
    add_item("entrance", "The entrance leads into the tower.\n");
    add_item(({ "battlement", "merlons"}), 
    "Between the merlons the dark clefts look down at you.\n");
    add_item(({ "clefts", "embrasures"}), 
    "You cannot see anything in the clefts.\n");

    add_exit(FORNOST_DIR + "south_ridge", "north", 0, 2);
    add_exit(FORNOST_DIR + "outer_wall", "down", 0, 3);
    add_exit(FORNOST_DIR + "ins_g_tow", "in", 0, 1);
}

string
set_arnor_long()
{
    string desc;

    desc = "On top of a green hill just outside the ruins of Fornost. "+
    "A grey tower is overlooking the countryside here. There is a ridge "+
    "that extends north to another hilltop. Ivy covers the south side of "+
    "the grey tower. There is an entrance leading into the tower. ";
    desc += query_arnor_time();

    return BSN(desc);
}
