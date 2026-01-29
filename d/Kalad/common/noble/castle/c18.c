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
    "while to the south, the hall continues. On one wall, "+
    "you notice a large, gold-framed painting.\n");
    add_item(({"large painting","painting","gold-framed painting"}),
    "You see a painting of a vast area of rolling, grass-lands. "+
    "They stretch off to the horizen of blue sky. There is a "+
    "single flower in the center, of blue color.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c14", "north", 0, 0);
    add_exit(NOBLE + "castle/c23", "south", 0, 0);
    add_exit(NOBLE + "castle/c53", "up", 0);
}


