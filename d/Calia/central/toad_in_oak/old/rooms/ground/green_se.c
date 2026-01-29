/*
 * /d/Calia/central/toad_in_oak/rooms/ground/green_se.c
 *
 * This is the southeast corner of the Toad-in-Oak village green. 
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
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

    set_long("You are standing near the southeast corner of a large open " +
        "area among the ancient trees of the forest. At the very center " + 
        "of the clearing sits an odd looking gazebo. Scattered beams of " + 
        "sunlight reach the ground here through holes in the leafy canopy " +
        "above. Along the edge of the clearing sits a long wooden bench.\n");

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
    Bench->set_long("This bench is a marvelous construction, assuming " + 
        "it is a construction at all. Its various parts of the bench, the " + 
        "seat, the back, and the legs, seem to flow together without " + 
        "any visible seam, as if it was all one piece.\n@@bench_contents@@"); 
    Bench->add_item(({"back", "seat", "legs"}), Bench->query_long()); 
    Bench->set_adjectives(({"long", "wooden"})); 

    /*  Exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne" , "north", Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_05" , "southeast", Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw", "west", Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo", "northwest", Bench->exit); 

    /* items */ 

    add_item(({"trees", "oaks", "oak", "tree", "forest", "branches", 
        "leaves", "trunks"}), 
        "The trees that surround this clearing are as big around as a " + 
        "small building, and stretch far into the sky above you. Their " + 
        "upper branches and leaves mesh together and block out some of " + 
        "the sun's light before it reaches here.\n"); 

    add_item(({"grass", "ground"}), "The green grass grows all around you. In the " + 
        "clearing, and between the trees, the grass takes up every inch of " +
        "ground that isn't otherwise occupied.\n"); 

    add_item(({"gazebo", "tree", "platfrom", "stairs", "stump", 
        "trunks", "trunk"}), Gazebo->describe); 

    set_tell_time(150); 

    add_tell("A young looking elf passes you as she walks through the clearing.\n"); 
    add_tell("You can hear a stream babbling in the distance.\n"); 
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("A squirrel bounds across the clearing.\n"); 
    add_tell("The song of a songbird sounds from somewhere in the " + 
        "distance.\n");
    
}

