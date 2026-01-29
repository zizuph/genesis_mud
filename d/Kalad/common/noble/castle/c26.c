// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a foul smelling chamber");
    INSIDE;
    set_long("This room is even worse than the last. There is a "+
    "large, dark hole in the center of the room, where the smell "+
    "of trash and refuse is overwhelming. All around it, on the walls, "+
    "even hanging from the ceiling are splatters and piles of garbage. "+
    "Just in front of you is a very large pile.\n");
    add_item("hole","The hole is large and dark, and you can barely "+
    "see the top of what looks like a huge pile of trash.\n");
    add_item("pile","A huge pile of refuse and junk.\n");
    add_item("refuse","There are little piles of junk, half-rotten "+
    "food, and feces. Small rats scurry about the floor.\n");
    add_item("rats","Tiny black and brown furred rodents with "+
    "beady red eyes dart across the room.\n");

    add_exit(NOBLE + "castle/c31", "south", 0, 0);
}
