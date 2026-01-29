// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a foul smelling chamber");
    INSIDE;
    set_long("The ground here is not carpeted, and the ground "+
    "is splattered with refuse. The room turns here to the "+
    "north, where it smells even worse. There are no windows, "+
    "no decorations or candles. Just stinking, wretched "+
    "stone walls.\n");
    add_item("refuse","There are little piles of junk, half-rotten "+
    "food, and feces. Small rats scurry about the floor.\n");
    add_item("rats","Tiny black and brown furred rodents with "+
    "beady red eyes dart across the room.\n");

    add_exit(NOBLE + "castle/c26", "north", 0, 0);
    add_exit(NOBLE + "castle/c30", "west", 0, 0);
}
