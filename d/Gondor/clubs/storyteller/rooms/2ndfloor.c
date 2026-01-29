/*
 * /d/Gondor/clubs/storytellers/rooms/2ndfloor.c
 */
inherit "/d/Gondor/std/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

void
create_gondor()
{
    set_short("a quiet stairwell on the second floor");
    set_long("The quiet stairwell you are in leads down to the first " +
        "floor of this old building, while another staircase goes " +
        "up along the north wall. In the south wall is a doorway, " +
        "through which you can see a small hallway.\n");
    add_item(({"stairwell", "stair", "stairs",}),
        "They are made of polished white stone, skillfully " +
        "crafted so that not even the thinnest knife blade could " +
        "be slipped into the crack between two stones.  The stairs " +
        "lead up and down from this floor.\n");
    add_item(({"doorway", "arch", "archway", "hallway", "hall"}),
        "The doorway has a rounded arch, with funneled columns for " +
        "sideframes. Beyond it you see a hallway.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/shallway", "south", 0, 0);
    add_exit(STORYT_DIR + "rooms/foyer", "down", 0, 1);
    add_exit(STORYT_DIR + "rooms/3rdfloor", "up", 0, 1);
}

