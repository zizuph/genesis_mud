/*
 *      /d/Gondor/arnor/fornost/ins_g_tow.c
 *
 *      Coded by Arren.
 *
 *      Modification log:
 *      28-Feb-1997, Olorin:    General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("inside a grey tower");

    set_long(BSN("Inside a round bare tower. The walls are rough and grey. "+
    "The stone floor is covered by dirt. Wind and weather have visited "+
    "this tower often. A staircase goes counter-clockwise up. "+
    "An open entrance leads out. "));

    add_item("floor",
    "Brushing away the dirt you see that the floor is rather smooth.\n");
    add_item("walls", "The stones have been set with great skill.\n");
    add_item(({ "stairs", "staircase"}), "A narrow staircase of stone.\n");
    add_item("entrance", "The entrance leads out of the tower.\n");
    add_item("dirt", "It's dirty.\n"); 
    add_item("tower", BSN(
    "This is the inside of an old tower. In the distant past it served as "+
    "a watch-tower. What it's used for now few know."));
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(FORNOST_DIR + "look_out", "up", 0, 1);
    add_exit(FORNOST_DIR + "on_hill", "out", 0, 1);
}

