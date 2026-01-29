// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself in a long north-south hallway. "+
    "The carpet you walk upon is red and soft. The walls are "+
    "adorned with various tapestries. You see what looks like "+
    "a bedroom to the west.\n");
    add_item("tapestries","They depict various battle scenes.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c47", "north", 0, 0);
    add_exit(NOBLE + "castle/c51", "west", 0, 0);
    add_exit(NOBLE + "castle/c57", "south", 0, 0);
}
