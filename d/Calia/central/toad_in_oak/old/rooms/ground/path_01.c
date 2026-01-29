/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_01.c
 *
 * A path on the ground level of the village of Toad-In-Oak just 
 * inside the west entrance of the village. 
 * 
 * HISTORY: [99-02-28] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground.c";

#include <stdproperties.h>
#include "defs.h"

#define STREAM TOAD_IN_OAK_OBJECTS + "stream.c"

// GLOBAL VARIABLES

object Stream; 

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
    Name:       query_pond_exits
    Purpose:    Returns a list of which exits lead to other pondside rooms.
    Arguments:  None
    Returns:    List of directions
*/
string*
query_pond_exits()
{
    return ({"southeast"}); 
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
    set_short("A path beneath a village in the trees."); 
    
    set_long("You are standing among the immense oak trees that " +
        "dominate this part of the forest, their leaves high " + 
        "above covering the area with green shadows. You can see " + 
        "the underside of a village built among the branches of " + 
        "the trees high above you. Grass covers the ground " + 
        "here in a thick green carpet stretching from the " + 
        "babbling stream that lies north of you to the dense " + 
        "thicket to the south. The scent of the oak trees and the " + 
        "grass fills the area.\n"); 

    /* Set properties. */
    add_prop(ROOM_I_TYPE, ROOM_BEACH); /*   Not a true beach, but 
                                            next to a stream. */ 
    add_prop(OBJ_I_CONTAIN_WATER, -1); /*   Infinite water due to the
                                            stream */ 
    /* Obejects */ 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("The small stream of clear sparkling water makes a " + 
        "babbling noise as it flows past you, heading west into " + 
        "the forest.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /* Exits */ 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_02", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "entrance_west", "west");         

    /* Items */ 
    
    add_item(({"path", "trail", "grass"}), 
        "The grass here is thick, green, and healthy despite the " + 
        "dim light at this level, and it covers the ground " + 
        "like a carpet. You can make out a very faint path through " + 
        "the grass that follows the bank of the stream towards " + 
        "the southeast.\n"); 

    add_item(({"trees", "tree", "oaks", "forest"}),         
        "The oak trees in this part of the forest are huge, " + 
        "towering high above you. Their branches and leaves " + 
        "form a green roof over the forest, letting only a few " + 
        "rays of sunshine make it down this far.\n"); 

    add_item(({"vegetation", "thicket", "shrubs", "vines", 
        "thorns", "wall"}), 
        "A dense thicket of branches, thorny vines, and other " + 
        "vegetation effectively forms a wall a short ways south " + 
        "of where you stand.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see what appears to be the underside of walkways " + 
        "running from tree to tree high above you. You can't see " + 
        "any great detail from down here.\n"); 

    if (! find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface")) 
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    }

}
