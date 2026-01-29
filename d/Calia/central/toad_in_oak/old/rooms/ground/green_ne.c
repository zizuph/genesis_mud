/*
 * /d/Calia/central/toad_in_oak/rooms/ground/green_ne.c
 *
 * This is the northeast corner of the Toad-in-Oak village green. 
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"

#define STREAM TOAD_IN_OAK_OBJECTS + "stream.c"

// GLOBAL VARIABLES

object Gazebo; 
object Stream; 

// FUNCTIONS

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
        case "grass": 
        case "ground": 

            write("The ground smells rather grassy.\n"); 
        
            break; 

        case "bench":
        case "gazebo":
        
            write("It smells very much like a perfectly healthy oak tree.\n"); 

            break;
    }
    return;
}

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("A large clearing among the giant trees."); 

    set_long("You are standing in the northeast corner of an open field " + 
        "in the middle of the forest. A small stream flows by, cutting off " +
        "the corner of the otherwise square clearing. Small patches of " + 
        "sunlight reach the ground through the leaves of the trees far " + 
        "above you. An unusual looking gazebo sits at the very center of " +
        "the clearing.\n");

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_BEACH); 
    add_prop(OBJ_I_CONTAIN_WATER, -1); 
    add_prop(OBJ_I_LIGHT, 2); 

    /* Obejects */ 

    if (!find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo")) 
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 
    }
    
    Gazebo = find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo");
   
    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("The stream of clear blue water babbles as it " + 
        "flows through the forest. It cuts off the corner of the clearing, " +
        "making it easy to reach down for a drink from here.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /*  Exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se" , "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo" , "southwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw" , "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04" , "northwest"); 

    /* items */ 

    add_item(({"ground", "grass"}), "The green grass grows all around. " + 
        "Between the trees and throughout the clearing, it starts right " +
        "at the edge of the stream and continues as far as you can see.\n"); 

    add_item(({"trees", "tree", "oaks", "forest", "trunks", "branches", 
        "leaves"}),             
        "The oaks in this part of the forest are massive, their thick " + 
        "trunks stretching high above you. Their uppermost branches and " +
        "leaves mesh together to form a nearly opaque canopy. However " + 
        "this clearing recieves a little more light than does most of the " + 
        "forest floor.\n"); 

    add_item(({"gazebo", "tree", "platform", "stairs", "stump", 
        "trunks", "trunk"}), Gazebo->describe); 
    
    set_tell_time(150); 

    add_tell("The stream babbles merrily as it flows past you.\n"); 
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("A squirrel bounds across the clearing.\n"); 
    add_tell("The song of a songbird sounds from somewhere in the " + 
        "distance.\n");

}
