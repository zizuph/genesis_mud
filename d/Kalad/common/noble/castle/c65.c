// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are nearing the south end of this large hallway. "+
        "Here, a beautiful statue adorns the east wall. You can smell "+
        "a faint, bad odor coming from the west. The carpet under your "+
        "feet muffles your footsteps.\n");
    add_item("statue","The statue depicts a man and woman entertwined "+
        "together in an embrace, with a golden halo over them.\n");
    add_item("carpet","The carpet is soft and warm.\n");

    add_exit(NOBLE + "castle/c60", "north", 0, 0);
    add_exit(NOBLE + "castle/c64", "west", 0, 0);
    add_exit(NOBLE + "castle/c70", "south", 0, 0);
}
