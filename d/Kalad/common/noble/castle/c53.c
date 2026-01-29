// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

object ob;

void reset_room();

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    set_long("You now find yourself in the tower-room area of "+
        "the castle. There is a spiral staircase here leading up "+
        "while to the south and north, the hall continues.\n");

    INSIDE;

    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c48", "north", 0, 0);
    add_exit(NOBLE + "castle/c58", "south", 0, 0);
    add_exit(NOBLE + "castle/ctower3", "up", 0);
    add_exit(NOBLE + "castle/c18", "down", 0);

    reset_room();
}

void
reset_room()
{
    ob = clone_npcs(ob, NOBLE + "npc/castle_guard");
}


