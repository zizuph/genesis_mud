// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You now find yourself in the tower-room area of "+
    "the castle. There is a spiral staircase here leading up "+
    "while to the south, the hall continues. The walls are "+
    "decorated with tapestries.\n");
    add_item("murals","They are pictures of dragons, goblins, "+
    "griffins and other mystical creatures.\n");
    add_item("tapestries","They are finely woven with many "+
    "ancient symbols on them.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_exit(NOBLE + "castle/c3", "northwest", 0, 0);
    add_exit(NOBLE + "castle/c13", "south", 0, 0);
    add_exit(NOBLE + "castle/c42", "up", 0);
}


