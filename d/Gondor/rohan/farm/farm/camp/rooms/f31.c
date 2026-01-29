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

#define NORTH    "f27"
#define WEST    "f30"
#define SW        "m25"
#define NW        "f26"
#define NE        "f28"


object guard;

void
create_dunlending()
{
    set_short("In the foothills of the White Mountains");
    set_long("A small meadow opens up to the southeast, sheltered in the "
        + "shadow of the White Mountains. The wind blows strongly here, "
        + "knocking the occasional pinecone loose from the trees. The pine "
        + "forest continues for many hours walk northward.\n");
    
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    
    set_no_exit_msg( ({"south", "east", "southeast"}), 
        "Thick undergrowth prevents you from moving in that direction.\n");
    add_item("undergrowth", "The undergrowth is thick here. You notice "
        + "poison oak as well as some bushes with thorns on them. You would "
        + "not be able to walk through the undergrowth.\n");
    add_forest_meadow("southeast");
    
    add_room_tell("The wind blows cold off the White Mountains.");
    add_room_tell("@@do_wind");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    
    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
        forest_climb("f31_up");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}

void
do_wind()
{
    if(!random(2))
    {
        object pinecone;
        pinecone = clone_object(CAMP_OBJ_DIR + "pinecone");
        pinecone->move(TO);
        tell_room(TO, "The wind blows hard, shaking loose a pinecone from a "
            + "tree. The pinecone lands on the ground with a THUD.\n");
            return;
    }
    else
    {
        tell_room(TO, "The wind blows hard, shaking the trees back and forth.\n");
        return;
    }
}

