/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define EAST    "f29"
#define WEST    "f27"
#define SW        "f31"
#define NW        "f19"
#define NE        "f20"

object guard;

void
create_dunlending()
{
    set_short("Low in the foothills of the White Mountains");
    set_long("The foothills of the White Mountains rise steeply to the west "
        + "and southwest, leading to way toward the White Mountains themselves. "
        + "In every direction, ancient pine trees form an old-growth forest. "
        + "The trees are large, but there is more than enough room to walk "
        + "between them.\n");

    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    set_no_exit_msg( ({"north", "south", "southeast"}),
        "You have trouble getting any traction moving that direction.\n");
    add_item( ({"rock", "rocks", "granite", "granite rock", "granite rocks"}),
        "The rocks vary in size from very large to very very large, to quite "
        + "massive. They are a white-grey in color and make the foothills "
        + "look even more rugged than they are.\n");
    add_pinecone();

    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");


    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
        forest_climb("f28_up");
    }

add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
