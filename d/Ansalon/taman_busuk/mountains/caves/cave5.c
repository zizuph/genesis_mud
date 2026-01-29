#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>

inherit CAVE_BASE;

int has_jewel = 0;

void
create_cave_room()
{
    set_short("a cave under the Taman Busuk mountains");
    set_long("You are standing in a narrow cave under the Taman " +
    "Busuk mountains. A rough stone basin is carved out of the rock " +
    "of the east wall. There is a small stream of water pouring into " +
    "the basin and spilling onto the ground.\n");

    add_cave_items();

    add_item(({"basin","rough stone basin","stone basin"}),
    "The basin has been carved out of the wall, and is set not " +
    "far off the ground. A small stream of water pours out of " +
    "a hole above the basin. A statuette of a woman, also carved " +
    "out of the wall, stands above the hole, hands clasped as if " +
    "in prayer.\n");

    add_item(({"stream","stream of water"}),
    "The stream of water flows from a hole in the wall down into the " +
    "basin.\n");

    add_item(({"hole","hole in the wall"}),
    "The hole from which the stream issues is small and round, not " +
    "much bigger than your finger.\n");

    add_item(({"water","water in basin"}),
    "The water in the basin is crystal clear.\n");

    add_item(({"statuette","woman"}),
    "The statuette is not more than a couple of hands high. It " +
    "depicts a woman clad in long, flowing robes. She stands " +
    "erect, her hands clasped beneath her head, as if in prayer.\n");

    add_item(({"hands","hands on statuette","woman's hands",
        "the woman's hands"}),
    "@@exa_hands@@");

    add_item("jewel", "@@exa_jewel@@");

    remove_prop(ROOM_I_LIGHT);

    add_exit(CAVE_DIR + "cave4", "west");
}

string
exa_hands()
{
    if (has_jewel)
    {
        return "Looking closer, you notice that the statuette's " +
        "hands are not clasped in prayer, but rather that she is " +
        "holding a small jewel, which shines brightly!\n";
    }
    else
    {
        return "Looking closer, you notice that the statuette's " +
        "hands are not clasped in prayer, but rather that they " +
        "are cupped around nothing. Perhaps a piece of the " +
        "statuette is missing.\n";
    }
}

string
exa_jewel()
{
    if (has_jewel)
    {
        return "The small jewel is shining brightly. It looks quite " +
        "valuable.\n";
    }
    else
    {
        return "You find no jewel.\n";
    }
}
