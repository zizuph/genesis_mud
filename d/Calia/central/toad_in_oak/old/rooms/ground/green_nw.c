/*
 * /d/Calia/central/toad_in_oak/rooms/ground/green_nw.c
 *
 * This is the northwest corner of the Toad-in-Oak village green. 
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"

#define BENCH TOAD_IN_OAK_OBJECTS + "bench.c"

// GLOBAL VARIABLES 

object Bench;
object Gazebo; 

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

/*  Name        leave_inv
    Purpose     Called when an object leaves the room
    Arguments   see sman
    Returns     Nothing */ 
void 
leave_inv(object ob, object to) 
{   
    
    Bench->leave(ob); 

    ::leave_inv(ob, to); 
}

/*  Function    exits_description
    Purpose     redefinition of base function to include the contents of the
                bench
    Arguments   None
    returns     Description of the exits from the room, plus whatevers sitting
                on the bench. 
*/
string
exits_description()
{
    return ::exits_description() + Bench->contents(this_player()); 
}

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("A large clearing among the giant trees."); 

    set_long("You find yourself in the northwest corner of a large open " + 
        "square among the the oaks of the forest. In the very center of the " +
        "otherwise clear area is an odd-looking looking gazebo. Scattered " + 
        "sunbeams reach the ground here through gaps in the leafy canopy, " + 
        "making this clearing brighter than most the forest floor. A long " + 
        "wooden bench sits at the western edge of the clearing.\n"); 

    /*  Properties  */ 

    add_prop(OBJ_I_LIGHT, 2); 

    /*  Objects  */ 

    if(!find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"))
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 
    }
    
    Gazebo = find_object(TOAD_IN_OAK_ROOMS_GROUND + "gazebo"); 

    Bench = clone_object(BENCH); 
    Bench->move(this_object(), 1); 
    Bench->set_limit(10); 
    Bench->set_parse_string("[down] [on] [the] [long] [wooden] 'bench'");
    Bench->set_short("long wooden bench"); 
    Bench->set_long("The wooden bench sits at the very edge of the " + 
        "clearing and is long enough to seat a number of people. It has " + 
        "two legs at each end and a high back, yet the entire thing " + 
        "appears to be made out of a single piece of wood, the different " +
        "parts almost flowing into each other.\n@@contents@@"); 
    Bench->add_item(({"back", "seat", "legs"}), Bench->query_long()); 
    Bench->set_adjectives(({"long", "wooden"})); 

    /*  Exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04" , 
        "north", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne" , 
        "east", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo" , 
        "southeast", 
        Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw" , 
        "south", 
        Bench->exit); 

    /* items */ 

    add_item(({"grass", "ground"}), "The grass here is thick, green and " + 
        "healthy, despite the low light. It covers the entire clearing " + 
        "like a carpet, without any bare spots or brown patches.\n"); 

    add_item(({"trees", "oaks", "forest", "trunks", "branches", 
        "leaves", "canopy"}), 
        "The oaks in this part of the forest are massive, their thick " + 
        "trunks stretching high above you. Their uppermost branches and " +
        "leaves mesh together to form a nearly opaque canopy. However, " + 
        "this clearing recieves a little more light than does most of the " + 
        "forest floor.\n"); 
    
    add_item(({"vegetation", "thicket", "shrubs", "thorns", "vines", "wall"}),
        "A dense thicket of shrubs, thorny vines, and other vegetation " + 
        "winds its way through the trees west of the clearing, forming a " + 
        "natural wall seperating this area from the rest of the forest.\n"); 
            
    add_item(({"gazebo", "tree", "platfrom", "stairs", "stump", 
        "trunks", "trunk"}), Gazebo->describe); 

    set_tell_time(150); 

    add_tell("You can hear a stream babbling in the distance.\n"); 
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("A squirrel bounds across the clearing.\n"); 
    add_tell("The song of a songbird sounds from somewhere in the " + 
        "distance.\n");

}

