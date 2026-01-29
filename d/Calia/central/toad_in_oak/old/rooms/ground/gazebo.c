/*
 * /d/Calia/central/toad_in_oak/rooms/ground/Gazebo.c
 *
 * The gazebo in the middle of the village green. This was shaped magically from a 
 * single living oak rather than built.  
 *
 * HISTORY: [99-11-05] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"
#include <composite.h>
#include <filter_funs.h>

// FUNCTIONS

// FUNCTIONS

/*  Function    describe
    Purpose     Describe the gazebo from outside, including anybody in it
    Arguments   None
    Returns     Description */ 
string 
describe()
{
    string description = "This gazebo looks as if it was grown rather than " +
        "built. Further, it appears to be a single tree, with several " + 
        "\"trunks\" growing from a stump-like base, and joining into a " + 
        "single massive trunk some distance above you. There are even a " +
        "couple of stairs leading up to the platform which is about a " + 
        "foot above the ground. "; 

    object gazebo, *livings; 
    
    livings = FILTER_LIVE(all_inventory(this_object())); 
    if (sizeof(livings)) 
    {

        description += "You can see " + COMPOSITE_ALL_LIVE(livings) + 
            " in the gazebo."; 
    }

    return description + "\n"; 
}

/*
 * Function name: hook_smelled
 * Description:   Adds smells to certain items in the room. 
 *                
 * Arguments:     str typed by the player 
 * Returns:       nothing
 */
void
hook_smelled(string smelled)
{

    switch (smelled)
    {
        case "ground": 
        case "gazebo":
        case "post": 
        case "trunk": 
        case "branches":
        case "ceiling":
        
            write("It smells very much like a perfectly healthy oak tree,\n"); 

            break;
    }
    return;
}

string
describe_green()
{

    string *clearing = ({   TOAD_IN_OAK_ROOMS_GROUND + "green_ne", 
                            TOAD_IN_OAK_ROOMS_GROUND + "green_se", 
                            TOAD_IN_OAK_ROOMS_GROUND + "green_sw", 
                            TOAD_IN_OAK_ROOMS_GROUND + "green_nw"}); 
    string return_value; 
    object *living_things = ({}); 
    object room; 
    int x = 0; 

    return_value = "The village green is a grass covered clearing between " + 
        "the trees of the surrounding forest. Several wooden benches sit " + 
        "at the very edges of the clearing, and a stream flows past the " + 
        "northeastern corner. "; 

    for (x = 0; x < sizeof(clearing); x++)
    {
        room = find_object(clearing[x]); 
    
        if (room != 0)
        {
            living_things += FILTER_LIVE(all_inventory(room)); 
        }
    }

    if (sizeof(living_things)) 
    {
        return_value += "You can see " + COMPOSITE_ALL_LIVE(living_things) +  
            " in the clearing."; 
    }
    
    return return_value + "\n"; 
}

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("An unusual gazebo"); 

    set_long("You appear to be standing in the very heart of a huge oak " + 
        "tree. The floor beneath you, the ceiling above, and the posts " + 
        "that run surround you all seem to have been formed from a single " +
        "tree into the shape of a gazebo. The tree seems to be perfectly " +
        "healthy despite it's odd shape. Every surface is covered with " + 
        "bark, and you can see a few small leafy branches nearby. From " + 
        "this raised platform you can see the entire village green.\n");

    /*  Properties  */ 

    add_prop(ROOM_I_TYPE, ROOM_NORMAL); 
    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "southeast" ); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw", "southwest" ); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "northwest" ); 

    /*  Items  */

    add_item(({"tree", "oak"}), "You find it rather difficult to get " + 
        "a good look at the tree as a whole while standing inside it. " + 
        "Perhaps you could look at something a bit smaller.\n");

    add_item(({"floor", "ground", "platform" }), "The floor of this gazebo " + 
        "looks much like an ordinary stump, except that it is covered by " + 
        "smooth brown bark rather than bare wood. The floor forms a " + 
        "platform about a foot above the ground outside.\n"); 

    add_item(({"posts", "trunks"}), "The four posts that run from the " + 
        "floor to the ceiling of the gazebo look like tyhe trunks of " + 
        "smaller oak trees. They are generally smooth and straight, " + 
        "although there are a few small twigs and leaves growing from " + 
        "then.\n"); 

    add_item(({"ceiling"}), "The ceiling is several feet above your head, " +
        "making it difficult to discern much detail. It appears to be " + 
        "very similar to the floor, only upside down.\n"); 

    add_item(({"green", "clearing", "grass", "bench", "benches", "stream"}), 
        "@@describe_green@@"); 

    add_item(({"branches", "leaves", "twigs"}), "You can see a number of " + 
        "twigs and small branches with a few small leaves growing low on " + 
        "tree, but any significant branches are far out of your reach.\n"); 

    add_item(({"bark"}), "The bark of the tree looks like that of any " + 
        "other tree except on the floor of the gazebo, where it is " + 
        "suprisingly smooth.\n"); 

    /*  Tells  */ 

    set_tell_time(150); 

    add_tell("You can hear a stream babbling in the distance.\n"); 
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("A squirrel bounds across the clearing.\n"); 
    add_tell("The song of a songbird sounds from somewhere in the " + 
        "distance.\n");
    add_tell("A young looking elf walks through the clearing.\n"); 

}



