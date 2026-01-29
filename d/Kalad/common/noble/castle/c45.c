// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are now in a large hallway that stretches far "+
    "to the south as far as you can see. The carpet beneath you "+
    "softens your footsteps, and the walls around you are bare.\n");
    add_item("carpet","The red carpet is soft and warm. To "+
    "the east, you see a fancy looking room.\n");

    add_exit(NOBLE + "castle/c40", "north", 0, 0);
    add_exit(NOBLE + "castle/c46", "east", 0, 0);
    add_exit(NOBLE + "castle/c50", "south", 0, 0);
}


