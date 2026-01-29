// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You now find yourself in a slight bend of the "+
    "hall. Here, a large staircase leads up to the upper "+
    "levels of the castle. The hall here is not decorated.\n");
    add_item("staircase","They are grand white marble stairs "+
    "with oak railings.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c14", "northwest", 0, 0);
    add_exit(NOBLE + "castle/c20", "east", 0, 0);
    add_exit(NOBLE + "castle/c54", "up", 0);
}
