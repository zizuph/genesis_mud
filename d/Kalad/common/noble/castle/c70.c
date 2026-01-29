// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself in the southern corridor of "+
        "the castle of the High-Lord. Windows adorn the south wall, "+
        "letting the warm sun rays in. The carpet beneath you "+
        "softens your steps. There is a crystal ball on one of "+
        "the ledges of the windows.\n");
    add_item("ball","The crystal ball seems to be some sort of "+
        "prism, and you see a rainbow of light spilling out against "+
        "the opposite wall.\n");
    add_item("windows","The windows are arch-shaped, and give "+
        "you a good view of the outside noble district streets.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c69", "west", 0, 0);
    add_exit(NOBLE + "castle/c71", "east", 0, 0);
    add_exit(NOBLE + "castle/c65", "north", 0, 0);
}


