// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself in a hallway that goes north and "+
    "south through the upper part of the Castle of the High-Lord. "+
    "There are two doorways to the east and west. To the east, "+
    "you can hear armour clinking and snoring. West, you hear "+
    "nothing but some quiet humming.\n");

    add_exit(NOBLE + "castle/c55", "north", 0, 0);
    add_exit(NOBLE + "castle/c59", "west", 0, 0);
    add_exit(NOBLE + "castle/c61", "east", 0, 0);
    add_exit(NOBLE + "castle/c65", "south", 0, 0);
}


