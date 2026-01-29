/*
 * The graveyard of Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

inherit "/std/room";
inherit GRAVEYARD_BASE;


void
create_graveyard_room()
{
    set_long(grave_above4);
    add_my_desc("A cold fog hangs close to the ground and muffles most " +
        "sounds here.\n");

    set_aboveground();
    headstone_moved = 2; // no headstone here

    add_exit(GRAVE1_DIR + "gr1_07",  "north");
    add_exit(GRAVE1_DIR + "gr1_16",  "southwest");

    reset_room();
}

void
reset_room()
{
    object hammer;

    add_npcs(0);

    if (!present("hammer",TO))
    {
        hammer = clone_object(OBJ_DIR + "hammer");
        hammer->add_prop(OBJ_I_HIDE, 1 + random(4));
        hammer->move(TO);
    }
}
