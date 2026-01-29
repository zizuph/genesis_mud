#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("inside a wide, circular chamber");
    set_long("You are inside a wide, circular chamber " +
        "of some sort. Above your head, the ceiling " +
        "has a large number of holes in it, and light " +
        "streams through into the room unimpeded. " +
        "On the rubble-strewn floor, two stone " +
        "benches stand on the east and west sides " +
        "of the room, against the curving walls. Above " +
        "each bench, a narrow window is cut into the " +
        "walls. A narrow stone staircase spirals " +
        "down into darkness against the south wall, " +
        "and a wide archway leads through the north " +
        "wall.\n\n");

    add_item(({"roof", "ceiling"}),
        "It looks to have been made with stone tiles placed " +
        "atop wooden rafters, but now most of the rafters are " +
        "gone, bringing down a large number of the stone tiles " +
        "with them.\n");
    add_item(({"rafters"}),
        "The rafters in the ceiling are made from wood, and " +
        "like everything else made from wood here, they've either " +
        "fallen apart or are in the process of doing it.\n");
    add_item(({"tiles"}),
        "The ceiling is made from a number of overlapping " +
        "stone tiles, but many of them have fallen down without " +
        "the support of the rafters, leaving huge holes in " +
        "the ceiling.\n");
    add_item(({"walls"}),
        "The circular walls of the chamber are relatively " +
        "barren, except for a single slit in the east " +
        "and west walls which serve as windows.\n");
    add_item(({"floor", "ground"}),
        "The floor of the room is made from flagstones " +
        "closely fitted together, though many are cracked " +
        "or smashed from the weight of falling tiles from " +
        "the roof.\n");
    add_item(({"benches"}),
        "Simple stone benches stand beneath the two windows " +
        "on the east and west sides of the room.\n");
    add_item(({"stairs", "staircase"}),
        "The stone staircase descends through the floor at " +
        "the south end of the room.\n");

    INSIDE;

    add_exit(RUIN + "kings_chamber", "north");
    add_exit(RUIN + "main_hall_5", "down");
}
