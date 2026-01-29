/* Lair of the Khiraa, Sarr */
#pragma strict_types

#include "defs.h"
inherit STD_ROOM;

int open = 0;

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Within the stairs Hallway");
    set_long(
      "You are on a stairwell leading down into darkness. The air here is " +
      "cold, damp and smelling of death and decay. The stairs themselves are " +
      "made of black stone, and look well-used. On one wall you see a small " +
      "niche.\n");

    add_item(({"niche"}), "There is a tiny green gem embedded there.\n");
    add_item(({"stairs"}), "They are made of worn black stone.\n");
    add_exit(TEMPLE_DIR + "stairs2", "down", 0);
}

void
init()
{
    ::init();
    add_action("gem", "press");
    add_action("gem", "push");
}

int
gem(string str)
{
    if (str != "gem")
    {
        NF("Press what? The gem?\n");
        return 0;
    }
    if (open == 1)
    {
        NF("The way is already open.\n");
        return 0;
    }
    write("You press the gem.\n");
    say(QCTNAME(TP) + " presses the gem in the niche.\n");
    TO->open_passage();
    return 1;
}

void
open_passage()
{
    if (!open)
    {
        open = 1;
        tell_room(TO, "The ceiling moves, and opens a way up!\n");
        TO->add_exit(FOREST_DIR + "wforest69", "up", 0);
        call_other(FOREST_DIR + "wforest69", "open_passage");
        set_alarm(30.0, 0.0, "close_passage");
    }
}

void
close_passage()
{
    if (open)
    {
        tell_room(TO, "The ceiling moves, closing the way back up!\n");
        open = 0;
        TO->remove_exit("up");
        call_other(FOREST_DIR + "wforest69", "close_passage");
    }
}

int *
query_coordinates()
{
    return ({11, 2, -1});
}
