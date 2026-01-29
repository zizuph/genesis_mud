// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are at an intersection. To the south, the "+
    "cold, stone corridor continues, but to the east and west, "+
    "you see rooms. A foul smell emenates from the east. "+
    "Torches line the walls.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c31", "east", 0, 0);
    add_exit(NOBLE + "castle/c25", "north", 0, 0);
    add_exit(NOBLE + "castle/c35", "south", 0, 0);
    add_exit(NOBLE + "castle/c29", "west", 0, 0);
}
