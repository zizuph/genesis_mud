/*
 * /d/Calia/central/toad_in_oak/rooms/ground/pond_shore.c
 *
 * This is the shore of the duck pond in Toad-in-Oak
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define STREAM TOAD_IN_OAK_OBJECTS + "stream.c"
// GLOBAL VARIABLES

object Pond; 
object Pond_Room;

// FUNCTIONS

/*  Name:       enter_inv
    Purpose:    called whenever an object enters the room, it registers any 
                livings that enter with the Control_Room as being in the pond
                area.
    Arguments:  The object entering, the object it came from. 
    Returns:    nothing
 */ 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (ob->toad_in_oak_duck())
    {
        Control_Room->register("duck", ob); 
    }
}

/*
 * Function name: gs_hook_start_meditate
 * Description:   Prints messages when somebody starts to meditate           
 * Arguments:     none
 * Returns:       nothing
 */
void
gs_hook_start_meditate()
{
    write("You slowly sit down in the center of the clearing on the " + 
        "carpet like grass. A feeling of peace settles over your thoughts " +
        "and you begin to reflect on your recent " + 
        "experiences. You find yourself able to <set> your different " + 
        "preferences at you own desire. Just <rise> when you are done " +
        "meditating. You estimate your stats and the progress you make " + 
        "at them.\n\n");
    say(QCTNAME(this_player()) + " sits down in the center of the clearing " + 
        "and starts to meditate.\n");        
}

/*
 * Function name: gs_hook_rise
 * Description:   Prints messages when somebody stops meditating
 * Arguments:     none
 * Returns:       nothing
 */
void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface of\n" +
          "your consciousness. You exhale and feel very relaxed as you get\n" +
          "up from the soft grass.\n");
    say(QCTNAME(this_player()) + " rises from the grass.\n");          
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
        case "grass":
        case "ground":

        write("The grass has a fresh, clean smell, with just a hint of " + 
            "the earth below it.\n"); 

        break;

        case "flowers":
        case "wildflowers":

        write("The flowers here have a variety of sweet smells.\n"); 
    
        break; 

        case "tree":
        case "trees":
        case "oak":
        case "oaks":
        case "forest":
        case "trunks":

        write("The stately oaks have a distinctly wooden scent.\n"); 

        break; 

        case "branches":
        case "leaves":

        write("Unfortunately the leaf covered branches of the oaks are " + 
            "far out of the reach of even a nose as long as yours.\n"); 

        break; 

        case "pond": 
        case "water": 

        write("The water of the pond smells clear and fresh.\n"); 

        break; 
    
        case "beach": 
        case "sand":
        case "pebbles":

        write("The sand and pebbles that make up the beach smell like " + 
            "any other mud you've sniffed.\n"); 

        break;

    }
    return; 
}

/*  Name:       Leave_inv
    Purpose:    Unregisters a living from the Pond area when it leaves the
                room
    Arguments:  Object leaving, object it's going to
    Returns:    nothing
 */ 
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 

    if (ob->toad_in_oak_duck())
    {
        Control_Room->unregister("duck", ob); 
    }
}

/*
 * Function name:   pick flowers
 * Description:     Tells the player not to pick the flowers. 
 *                
 * Arguments:       str typed by the player 
 * Returns:         0/1
 */                 
int
pick_flowers(string command)
{
    int success = 0; 

    if (command && parse_command(command, this_object(), 
        "[the] 'flower' / 'flowers' / 'wildflower' / 'wildflowers'"))
    {
        write("Picking any of the flowers here would destroy the beauty " + 
            "of this spot. You'd best pick your flowers elsewhere.\n"); 
        
        success = 1; 
    }

    return success; 
}

/*  
    Name:       query_pond_exits
    Purpose:    Returns a list of which exits lead to other pondside rooms.
    Arguments:  None
    Returns:    List of directions
*/
string*
query_pond_exits()
{
    return ({"northwest"}); 
}

/*
    Name:       toad_in_oak_pond_room
    Purpose:    Identifies this as one of the rooms near the pond
    Arguments:  None
    Returns:    1
*/ 
int
toad_in_oak_pond_room()
{
    return 1; 
}

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("Next to a small pond in the forest"); 

    set_long("You are standing in a tiny clearing next to a small pond. " +
        "All around you are the giant oaks that dominate this part of " + 
        "the forest. A few wildflowers growing nearby and waves from the " + 
        "pond gently hitting the narrow beach add to the beauty of the " + 
        "area. This spot is very peaceful - even the normal background " + 
        "noises of the forest are absent. It might be a good place to " + 
        "meditate.@@pond_contents@@\n"); 

    /*  Properties  */

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /*  Objects  */ 

    if (! find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface")) 
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    }

    Pond_Room = find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 

    Pond = clone_object(STREAM); 
    Pond->set_name("pond"); 
    Pond->remove_name("stream"); 
    Pond->move(this_object(), 1); 
    Pond->set_object("pond"); 
    Pond->set_long(Pond_Room->describe); 
    Pond->add_item(({"water"}), Pond_Room->describe); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_11", "northwest"); 

    /* items */ 

    add_item(({"grass", "ground"}), 
        "The grass in this area is thick, green, and healthy. It covers " + 
        "the ground between the trees and the pond like a thick rug.\n"); 

    add_item(({"beach", "sand", "pebbles"}), 
        "The narrow beach along the edge of the pond is made up of sand " + 
        "and small pebbles that have been washed up by the pond.\n");
    
    add_item(({"flowers", "wildflowers"}), 
        "There are a few flowers scattered around the clearing of " + 
        "different colours and varieties. They add to the beauty of this " + 
        "spot and their pleasant smell fills the air.\n"); 

    add_item(({"trees", "tree", "forest", "oaks", "oak", "trunks", 
        "leaves", "branches", "clearing"}), 
        "The ancient oaks seem to havbe missed a spot of ground " + 
        "here, leaving a small area next to the pond to be claimed " + 
        "by the grass. The trees tower above you, their trunks " + 
        "rising straight into the sky above you. The lowest branches " + 
        "of the oaks are far out of your reach, and form a nearly opaque " +
        "canopy high above.\n"); 

}

void
init()
{
    ::init(); 

    init_guild_support(); 

    add_action(pick_flowers, "pick"); 
    
}


