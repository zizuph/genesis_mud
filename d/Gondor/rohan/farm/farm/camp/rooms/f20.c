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

#define WEST    "f19"
#define SE        "f29"
#define SW        "f28"
#define NW        "f18"

object guard;

void
create_dunlending()
{
    set_short("In a forest in Anorien");
    set_long("Thick patches of poison oak grow between many of the trees "
        + "here, making it impossible to walk in those directions. "
        + "Where there is no poison oak, "
        + "the trees are spaced wide apart and the forest is still and "
        + "calm. The smell of pine lingers heavily in the air, and pine "
        + "needles and pinecones are scattered about the forest floor.\n");

    add_item( ({"undergrowth", "oak", "poison oak", "poisonoak"}),
        "You do NOT want to walk into this stuff! The poison oak has small "
        + "glossy leaves. They look almost waxy, or oily, and if you touch "
        + "them they make you itch and itch and itch. No. You're NOT going "
        + "through that stuff.\n");
    set_no_exit_msg( ({"east", "north", "northeast", "south"}),
        "The undergrowth is too thick that direction!\n");
    add_pinecone();

    add_room_tell("A rabbit hops in, and then out, of view.");
    add_room_tell("Clouds sail across the sky, like captainless ships.");
    add_room_tell("You hear men and women talking in hushed tones, just out "
        + "of sight.");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast");


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f20_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
