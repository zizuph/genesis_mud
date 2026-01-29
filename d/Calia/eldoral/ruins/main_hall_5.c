#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("a narrow landing in the ruins of Castle " +
        "Chimera");
    set_long("You are in a narrow hallway that serves " +
        "as a landing on a long flight of stairs. The " +
        "hall itself opens into a much larger room to " +
        "the north, but the stone walls here are " +
        "fairly narrow, and the ceiling quite low. " +
        "In the south end of this hall, the room dead" +
        "-ends against a narrow, spiral stone " +
        "staircase, that leads upwards and down, " +
        "into darkness.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling is simple in construction, appearing " +
        "to be long stone slabs laid across the tops of the " +
        "walls. The staircase rises upwards through the " +
        "ceiling into darkness.\n");
    add_item(({"walls"}),
        "The walls rising on either side of you are simply " +
        "constructed from thick blocks of grey stone.\n");
    add_item(({"floor", "ground"}),
        "The floor is made of thick flagstones fitted " +
        "tightly together, and covered in a thick layer of " +
        "dust. The staircase descends beneath its surface, " +
        "leading downwards into darkness.\n");
    add_item(({"stairs", "staircase"}),
        "The stone staircase spirals tightly, leading up and " +
        "down from here into darkness.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "dining_hall", "north");
    add_exit(RUIN + "sitting_room", "up");
    add_exit(RUIN + "main_stairs_s", "down");
}
