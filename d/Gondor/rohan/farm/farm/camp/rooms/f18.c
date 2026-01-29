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

#define WEST    "m16"
#define SE        "f20"
#define SW        "f19"
#define NW        "f16"
#define NE        "f17"


object guard;

void
create_dunlending()
{
    set_short("South of a cliff in an Anorien Forest");
    set_long("To the north, the forest ends abruptly at "
        + "a steep cliff. Here, however, your footing is quite secure "
        + "and there's no way to just fall to your death--that you can "
        + "see, anyway. A thick patch of poison oak blocks passage to "
        + "the east, but to the west the forest opens up, becoming a "
        + "wide meadow.\n");

    add_item( ({"undergrowth", "oak", "poison oak", "poisonoak"}),
        "You do NOT want to walk into this stuff! The poison oak has small "
        + "glossy leaves. They look almost waxy, or oily, and if you touch "
        + "them they make you itch and itch and itch. No. You're NOT going "
        + "through that stuff.\n");
    set_no_exit_msg( ({"north", "south"}),
        "Try as you might, you cannot find a trail leading that direction.\n");
    set_no_exit_msg("east", "The undergrowth is too thick that direction!\n");
    add_cliff();
    add_forest_meadow("west");
    add_room_tell("A rabbit hops in, and then out, of view.");
    add_room_tell("Clouds sail across the sky, like captainless ships.");
    add_room_tell("You hear men and women talking in hushed tones, just out "
        + "of sight.");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f18_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



