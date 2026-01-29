/*
 * /d/Calia/central/toad_in_oak/rooms/ground/green_sw.c
 *
 * This is the southwest corner of the Toad-in-Oak village green. 
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
  
    set_long("You stand in the southwestern corner of a large clearing in " + 
        "the great forest. At the center of the clearing is an " +
        "odd-looking gazebo. Small patches of sunlight reach the ground " +
        "here through holes in the green canopy far above. A long curved " +
        "bench sits at the very corner of the clearing.\n"); 

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
    Bench->set_long("The bench runs along both the the western and " + 
        "southern edges of the clearing, and has a gentle curve at the " +
        "corner. The entire thing appears to be a single piece of wood, " + 
        "including the high back and the legs that hold it up.\n" + 
        "@@contents@@"); 
    Bench->add_item(({"back", "seat", "legs"}), Bench->query_long()); 
    Bench->set_adjectives(({"long", "wooden"})); 

    /*  Properties  */ 

    add_prop(OBJ_I_LIGHT, 2); 
        
    /*  Exits  */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "north", Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo", "northeast", Bench->exit); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "east", Bench->exit  ); 

    /* items */ 

    add_item(({"trees", "oaks", "oak", "tree", "forest", "branches", 
        "leaves", "trunks"}), 
        "The ancient oaks that dominate this part of the forest have grown " +
        "to incredible proportions. Their trunks are several feet around, " + 
        "and they stretch far above you. Their uppermost brances and " + 
        "leaves block a a good deal of the sun's light before it can reach " +
        "this clearing.\n");
    
    add_item(({"grass", "ground"}), "Although the forest floor is covered with " + 
        "perpetual shadows, the grass here is remarkably green and " + 
        "healthy. It has taken over every bit of ground between the stream " + 
        "and the thicket that doesn't have a tree growing in it.\n"); 

    add_item(({"vegetation", "thicket", "shrubs", "thorns", "vines", "wall"}),
        "Dense shrubs, thorny vines, and other vegetation have grown " + 
        "together to form an impassible thicket in the forest to the " + 
        "west.\n");

    add_item(({"gazebo", "tree", "platfrom", "stairs", "stump", 
        "trunks", "trunk"}), Gazebo->describe); 

    set_tell_time(150); 

    add_tell("You can hear a stream babbling in the distance.\n"); 
    add_tell("You hear a tree frog chirping somewhere in the forest.\n"); 
    add_tell("A squirrel bounds across the clearing.\n"); 
    add_tell("The song of a songbird sounds from somewhere in the " + 
        "distance.\n");

}
