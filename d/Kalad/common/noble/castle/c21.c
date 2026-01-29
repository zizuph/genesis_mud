// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself in a short hall that bends "+
    "to the west sharply. The walls are adorned with ancient "+
    "tapestries. The ground is covered with a red carpet, and "+
    "to the north you smell food.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");
    add_item(({"tapestries","ancient tapestries"}),
    "They are covered with runes that seem to date back to "+
    "ancient times.\n");

    add_exit(NOBLE + "castle/c16", "north", 0, 0);
    add_exit(NOBLE + "castle/c20", "west", 0, 0);
}
