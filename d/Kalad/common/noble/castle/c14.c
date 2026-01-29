// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You now stand on the soft, red carpet that covers "+
    "this long hall leading south. The walls have torches on "+
    "them to give light when needed. The walls surrounding you "+
    "are covered with fine crystal drapes. There is a window "+
    "to the west of you, and to the southeast, you see a large "+
    "staircase.\n");
    add_item("staircase","It looks like it is made of marble.\n");
    add_item("drapes","They are strings of tiny, spherical crystals "+
    "that reflect the light around the room.\n");
    add_item("window","Through the window, you see the meadow around "+
    "the castle.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c9", "north", 0, 0);
    add_exit(NOBLE + "castle/c19", "southeast", 0, 0);
    add_exit(NOBLE + "castle/c18", "south", 0, 0);
}
