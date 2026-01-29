/*
 * File:    lawn_ne.c
 * Creator: Cirion, 1998.11.26
 * Purpose: Area outside the monastery
 */
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("peaceful lawn outside the Monestary");
    set_long("The thin blades of verdant grass growing upon this "
        + "high plateau shiver in the strong, cold wind that "
        + "blows across the lawn. To the south, the ancient stones "
        + "of a great monastery loom. A large wooden doorway "
        + "opens into the dark halls, and to the north a steep, rocky "
        + "path curves west and descends out of sight below the "
        + "edge of the plateau."
        + living_view("lawn_nw", " Standing on the lawn to the "
        + "west, you see ", ".", "") + "\n");
    add_item(({"door","doorway"}),
        "It is a massive, curved wooden arch that leads "
        + "into the ancient monastery to the south. Its "
        + "frame appears to have once held strong doors, "
        + "long since removed.\n");
    add_item(({"grass","lawn","blades"}),
        "The grass is well manicured here, and quivers as "
        + "the wind blows across it.\n");
    add_item(({"monastery","building"}),
        "Its ancient stones rise high overhead, and the "
        + "open doorway to the south leads into it.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_nw", "west");
    add_exit("lawn_east1", "southeast");
    add_exit("hall_lower_north", "south");
    add_exit("path7", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "You pass through the doorway and "
        + "out onto the windy front lawn.\n");
}

