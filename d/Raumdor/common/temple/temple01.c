/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

int blocked;

void
set_blocked(int i)
{
    blocked = i;
}

int
query_blocked()
{
    return blocked;
}

void
create_room()
{
    ::create_room();
    set_short("Entrance of an underground temple");
    set_long(
      "You at the foot of a dark stairway. There are torches burning on the " +
      "walls beside you. This short hallway leads north into what looks like " +
      "a circular chamber with a rather large statue in the center.\n");
    add_item(({"statue"}), "It looks like a robed figure.\n");
    add_item(({"stairs"}), "They are made of black stone.\n");
    add_item(({"torches"}), "They give light to the area.\n");
    add_exit(TEMPLE_DIR + "stairs2", "up", "@@block@@");
    add_exit(TEMPLE_DIR + "temple03", "north", 0);
}

int
block()
{
    if (blocked)
    {
        write("That way has been seald off by a shimmering purple field.\n");
        say(QCTNAME(TP) +
            " tries to go up but is stopped by a shimmering purple field.\n");
        return 1;
    }
    return 0;
}
