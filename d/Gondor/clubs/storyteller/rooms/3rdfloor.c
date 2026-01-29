/*
 * /d/Gondor/clubs/storytellers/rooms/3rdfloor.c
 */
inherit "/d/Gondor/std/room";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

void
create_gondor()
{
    set_short("the top of the stairwell on the third floor");
    set_long("You are at the top of the stairwell, on the third " +
        "floor of the clubhouse. A ladder is attached to the wall " +
        "in front of you, and in the south wall is a doorway " +
        "leading to the Grand Hall of the Tellers.\n");
    add_item(({"stairwell", "stair", "stairs",}),
        "They are made of polished white stone, skillfully " +
        "crafted so that not even the thinnest knife blade could " +
        "be slipped into the crack between two stones.  The stairs " +
        "lead down from this floor.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(STORYT_DIR + "rooms/sittingroom3", "south", 0, 0);
    add_exit(STORYT_DIR + "rooms/roof", "up", 0, 1);
    add_exit(STORYT_DIR + "rooms/2ndfloor", "down", 0, 1);
}

