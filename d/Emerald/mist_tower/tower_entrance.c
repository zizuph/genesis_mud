#include "defs.h"

inherit MIST_TOWER_BASE;

void
create_tower_room()
{
    set_em_long("A cramped hallway extends approximately five meters " +
        "in from the arched exit from the tower and opens up into a " +
        "larger area beyond.  A break in the stone wall just before " +
        "the end of the hall hides a narrow, tightly spiraled stairway " +
        "leading upwards.\n");

    add_exit("tower_storage", "north");
    add_exit("prominence01", "south");
    add_exit("tower_library", "up");

    add_item( ({ "stair", "stairway", "stairs", "staircase",
                 "spiral stair", "spiral stairway",
                 "spiral staircase", "spiraled staircase",
                 "spiraled stair", "spiraled stairway",
                 "tightly spiraled stairway" }),
        "At one end of this hall, a tightly spiraling staircase winds"
      + " its way up into the recesses of the stone ceiling.\n");
}
