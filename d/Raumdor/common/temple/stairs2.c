/* Lair of the Khiraa, Sarr */
#pragma strict_types

#include "defs.h"
inherit STD_ROOM;

int blocked = 0;

void
set_blocked(int i)
{
    blocked = i;
}

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Within a stairwell");
    set_long(
      "You are in a stairwell leading down into darkness. The air here is " +
      "cold, damp and smelling of death and decay. The stairs themselves are " +
      "made of black stone, and look well-used.\n");

    add_item(({"stairs"}), "They are made of black stone.\n");
    add_exit(TEMPLE_DIR + "temple01", "down", "@@block@@");
    add_exit(TEMPLE_DIR + "stairs1", "up", 0);
}

int
block()
{
    if (blocked)
    {
        write("The way is blocked by a shimmering purple field.\n");
        say(QCTNAME(TP) +
            " tries to go down, but is blocked by a purple shimmering " +
            "field.\n");
        return 1;
    }
    return 0;
}

int *
query_coordinates()
{
    return ({11, 2, -2});
}
