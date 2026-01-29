#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    set_short("Standard stairs");
    set_long("Standard items for stairs in this room.\n");

    add_item(({"stairs", "stairway", "spiral stairs", "spiral stairway"}),
        "The stairs are made of polished black marble. Even though many " +
        "feet must have walked up and down these stairs, not a scratch " +
        "can be noticed on the black surface of the stone steps.\n");

    add_cmd_item(({"stairs", "stairway", "spiral stairs", "spiral stairway"}),
        ({"touch", "feel"}), "The stairs are very smooth to the touch and " +
        "they feel almost soft yet they are ice cold.\n");
}
