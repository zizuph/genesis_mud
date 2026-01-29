#include "defs.h"

inherit M1_OUT_BASE;

nomask void
create_m1_room()
{
    add_walkway();

    set_long(query_long() + "A short set of stone stairs leads down " +
        "into a dark cellar beneath the monastery building.\n");

    add_item(({ "cellar", "dark cellar" }),
        "It is too dark to see much down there from outside.\n");

    add_item(({ "stairs", "stone stairs" }),
        "A set of stone stairs that leads down through a small " +
        "doorway into the cellar.\n");

    add_item(({ "door", "doorway", "small doorway", "frame", "door frame" }),
        "The doorway is quite small; all but the shortest of humans " +
        "or elves would have to duck to pass through it.  It looks as if " +
        "a door was once attached to the frame, but it is nowhere to be " +
        "found now.\n");

    add_exit("m0_22", "down");
    add_exit("m1_12", "west");
    add_exit("m1_23", "north");
    add_exit("m1_21", "south");
    add_exit("m1_13", "northwest");
    add_exit("m1_11", "southwest");
}
