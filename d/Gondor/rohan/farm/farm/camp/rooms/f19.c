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

#define SOUTH    "f27"
#define EAST    "f20"
#define WEST    "m21"
#define SE        "f28"
#define SW        "f26"
#define NW        "m16"
#define NE        "f18"


object guard;

void
create_dunlending()
{
    set_short("Next to a meadow in Anorien");
    set_long("The pine needles that normally cover the forest floor "
        + "have been pushed aside, showing signs of a camp. You see "
        + "a fire ring, some bones and even a recently disturbed mound "
        + "of dirt.\n");
    add_item( ({"needles", "needle", "pine needles", "pineneedles"}),
        "The pine needles are all pushed to the sides of the area exposing "
        + "dirt from the forest floor.\n");
    add_item( ({"floor", "forest floor"}), "The forest floor is dirt, "
        + "mainly, very fine dirt that seems to get everywhere: in your "
        + "eyes, in your boots, even in your mouth. It rises like dust "
        + "when you walk.\n");
    add_item( ({"bone", "bones"}), "These bones look like rabbit bones. "
        + "You notice tooth marks on them, so definitely this was someone's "
        + "meal.\n");
    add_item( ({"fire ring"}), "Mostly the fire ring is a circle of rocks. "
        + "You notice black soot all along the rocks, so there was a fire "
        + "in it. Whoever made the fire was not a skilled woodsman, "
        + "because it's located right under a tree. This could have burned "
        + "down the whole forest.\n");
    add_item( ({"rock", "rocks", "soot", "black soot"}), "The soot is "
        + "evidence of a fire in the fire ring.\n");
    add_item( ({"dirt", "mound", "mound of dirt", "dirt mound"}), "You look "
        + "at the mound of dirt and the first thing you notice is that there are "
        + "two boot prints, just in front of it, about a shoulder's width "
        + "apart. As you breathe in through your nose, it suddenly hits you. "
        + "This was the latrine! Right in the middle of camp! They didn't even "
        + "walk away to relieve themselves.\n");
    add_item("latrine", "What a crappy place for a latrine.\n");
    add_item( ({"prints", "print", "boot print", "boot prints"}),
        "The boot prints tell you where people squatted in order to use the "
        + "latrine.\n");
    add_cmd_item( ({"latrine", "the latrine"}), "use", "Gross! Not here in camp!\n");
    
    set_no_exit_msg( ({"north"}), 
        "Try as you might, you cannot find a trail leading that direction.\n");
    
    
    add_forest_meadow("west");
    add_room_tell("A rabbit hops in, and then out, of view.");
    add_room_tell("Clouds sail across the sky, like captainless ships.");
    add_room_tell("You hear men and women talking in hushed tones, just out "
        + "of sight.");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
        forest_climb("f19_up");
    }
    add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



