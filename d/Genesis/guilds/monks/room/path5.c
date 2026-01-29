/*
 * File:    path5.c
 * Creator: Cirion, 1998.12.04
 * Purpose: Mountain path leading up to the monastery
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
    set_short("rocky mountain path");
    set_long("Rising up to the northeast, the trail bends sharply here around "
        + "an outcropping in the cliff wall, which rises sheer straight above "
        + "until it seems to hit a plateau high above. The trail winds its "
        + "way down to the south, and is especially narrow here, the space "
        + "of a foot separating it from the drop to the dark-green forest "
        + "below.\n");
    add_item(({"rock","rocks","pebble","pebbles","ground"}),
        "The rocks and pebbles underfoot make walking here "
        + "precarious.\n");
    add_item(({"forest","trees"}),
        "The forest below is a dark canopy the spreads out "
        + "as far as the eye can see.\n");
    add_item(({"trail","path"}),
        " It rises to the north and goes south into the "
        + "forest.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("path4", "south");
    add_exit("path6", "northeast");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "The winds starts to turn cold as you "
        + "climb the steep, rocky path.\n");
    ENTRANCE_MSG("northeast", "You descend the steep, rocky mountain path.\n");
}

