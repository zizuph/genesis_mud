#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public int
in_msg()
{
    write("You carefully duck inside the opening.\n");
    return 0;
}

public void
create_room()
{
    extra = "A low outcrop of stone juts up from beneath the " +
        "bushy forest floor, in the center of which you notice " +
        "an opening leading downwards into what might be a cave " +
        "of some sort. ";
    create_forest();

    add_item(({"outcrop", "stone"}),
        "The large stone is unremarkable, except for a dark " +
        "opening in one side that appears to lead downwards " +
        "beneath the ground.\n");
    add_item(({"opening", "dark opening"}),
        "An opening in the face of the rock leads down into " +
        "what might be a cave.\n");

    add_exit(CAVERNS + "pas1", "in", "@@in_msg");
    add_exit(FOREST + "s_forest_7", "north");
    add_exit(FOREST + "s_forest_16", "west");
    add_exit(FOREST + "s_forest_25", "south");
    add_exit(FOREST + "e_forest_1", "east");
}
