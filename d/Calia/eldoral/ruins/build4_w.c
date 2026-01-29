#pragma strict_types

#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("the ruins of a long hall in " + CASTLE_NAME);
    set_long("You are in a long hall-like room. It " +
        "continues off to the east, however much of " +
        "the ceiling at that end of the hall has " +
        "long since collapsed, burying whatever might " +
        "have been in that end beneath tons of broken " +
        "stone. This end of the room is fairly clear, " +
        "however. The plain walls of the room bearing " +
        "a few signs of age, but largely intact. The " +
        "only exits from the hall at this ends appear " +
        "to be a narrow passage that leads through " +
        "the wall to the west, and a slightly larger passage " +
        "to the north.\n\n");

    add_item(({"ceiling", "roof"}),
        "The ceiling above your head is fairly simply in " +
        "construction, appearing to be large slabs of stone " +
        "simply laid across the walls. The slabs are badly " +
        "cracked, and further to the east they've collapsed " +
        "entirely.\n");
    add_item(({"walls"}),
        "The walls are common enough, grey stone blocks cut " +
        "and fit into place. They're holding up fairly well " +
        "to the passage of time, but are covered in a fine " +
        "spiderweb of small cracks.\n");
    add_item(({"floor", "ground"}),
        "The floor is comprised of flagstones carefully set " +
        "into place, though several have started lifting and " +
        "cracking.\n");

    add_exit(RUIN + "hall-build4", "north");
    add_exit(RUIN + "build4_e", "east");
    add_exit(RUIN + "build2-build4", "west");
}
