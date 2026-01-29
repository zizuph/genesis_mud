#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    set_long(query_long() + "An open doorway leads east into " +
        "the main building of the monastery.\n");

    add_item(({ "doorway", "open doorway", "frame" }),
        "The doorway leads into what looks like a storage area of some " +
        "sort, but it is too dark to tell exactly what is indside.  " +
        "It looks as if a door was once attached to the frame, but it " +
        "is nowhere to be found now.\n");
        
    add_item("storage area",
        "It is too dark inside to make out much of anything.\n");

    add_exit("m1_31", "east");
    add_exit("m1_11", "west");
    add_exit("m1_22", "north");
    add_exit("m1_20", "south");
    add_exit("m1_12", "northwest");
    add_exit("m1_10", "southwest");
}
