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
    "this long hall leading south. The walls have tapestries on "+
    "them.\n");
    add_item("tapestries","They depict various battle scenes.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c42", "north", 0, 0);
    add_exit(NOBLE + "castle/c52", "south", 0, 0);
}

