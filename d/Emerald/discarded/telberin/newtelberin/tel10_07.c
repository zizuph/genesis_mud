#include "defs.h";

inherit TELBERIN_ROOM;

void
create_telberin_room()
{
    set_short("Royal Circle of Telberin");
    set_em_long("The wide south avenue of Telberin comes to an end here " +
        "at the scenic Royal Circle.  Beautiful, tranquil gardens " +
        "border the circle, and inside are the grand edifices of the " +
        "royal government and the Temple of Telan-Ri.  Immediately to " +
        "your north lies the guildhall of the Keepers of Telberin.\n");

    add_exit("tel11_07", "east");
    add_exit("tel09_07", "west");
    add_exit("tel10_06", "south");
    add_exit("kot/entrance", "north");
}
