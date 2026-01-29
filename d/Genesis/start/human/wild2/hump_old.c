/* 	hump.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Humpbacked bridge");
    set_long("\n"+
             "An old humpbacked bridge.\n"+
             "");

    add_exit(THIS_DIR + "crossroad","west");
    add_exit(TOWN_DIR + "vill_gate","east");

    add_item(({"bridge" }),
             "This is a genuine, solid, old stone bridge.\n"+
             "It looks like as if it has been here for ages.\n"+
             "");
    add_item("carving", "On one of the stones there is a carving reading: " +
             "K + P = TRUE!\n");
    add_item("rail", "The rail is gnarled with age and is filled " +
             "scratchings like: A loves C\n");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}
