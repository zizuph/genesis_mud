// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("Your footsteps are muffled as you walk down this "+
    "red carpeted hallway. The walls around you are dark and "+
    "grey.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c57", "north", 0, 0);
    add_exit(NOBLE + "castle/c67", "south", 0, 0);
}


