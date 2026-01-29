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

#define EAST    "f22"
#define SE        "m22"
#define NE        "m17"


object guard;

void
create_dunlending()
{
    set_short("In a forest near a meadow in Anorien");
    set_long("You stand in a narrow strip of forest between two meadows. The "
        + "trees here tower above you, so large that even two trolls "
        + "couldn't link their arms around the treetrunks. Ferns grow around "
        + "the trees, a darker shade of green than the grass in the meadows.\n");
        
    add_item( ({"fern", "ferns"}), "The ferns have leaves the size of an ogre's "
        + "hand. They are a dark, rich green and grow near the trees.\n");
    set_no_exit_msg( ({"south", "north", "west", "northwest", "southwest"}), 
        "You have trouble getting any traction moving that direction.\n");
    add_pinecone();
    add_forest_meadow("north and south");
    add_room_tell("A rabbit hops in, and then out, of view.");
    add_room_tell("Clouds sail across the sky, like captainless ships.");
    add_room_tell("You hear men and women talking in hushed tones, just out "
        + "of sight.");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
        forest_climb("f21_up");
    }
    add_guard_down();
}

void
reset_room()
{
        set_searched(0);}
