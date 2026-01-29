// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are walking along the north corridor of the top "+
    "level of the castle. The red carpet beneath you muffles the "+
    "sound of your footsteps as you walk. The air here is hot, and "+
    "the sun streaming through the windows brightens the many "+
    "paintings that adorn the east wall.\n");
    add_item("carpet","The red carpet is soft and warm.\n");
    add_item("windows","Through the windows, you can see the streets of "+
    "the noble district.\n");
    add_item("paintings","They are masterpieces of some ancient painter, "+
    "long dead, but not forgotten. They look mostly like sploches of "+
    "paint splattered randomly.\n");

    add_exit(NOBLE + "castle/c40", "east", 0, 0);
    add_exit(NOBLE + "castle/c38", "west", 0, 0);
}


