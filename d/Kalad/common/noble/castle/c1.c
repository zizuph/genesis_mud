// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are at a bend in the north hall of the "+
    "castle of the High-Lord. The walls are decorated with "+
    "murals and tapestries, and the ground is covered with "+ 
    "a red carpet. The hall bends to the southwest, while "+
    "directly south, you see a room.\n");
    add_item("murals","They are pictures of dragons, goblins, "+
    "griffins and other mystical creatures.\n");
    add_item("tapestries","They are finely woven with many "+
    "ancient symbols on them.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c4", "southwest", 0, 0);
    add_exit(NOBLE + "castle/c2", "east", 0, 0);
    add_exit(NOBLE + "castle/c5", "south", 0, 0);
}


