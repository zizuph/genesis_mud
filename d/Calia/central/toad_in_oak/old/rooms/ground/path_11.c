/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_11.c
 *
 * A path on the ground level of Toad-in-Oak, on the eastern side of the 
 * village itself. This is one of only two places where the stream can be
 * crossed
 *
 * HISTORY: [99-03-19] Created by Kcirderf 
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

object Stream; 
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
    return ({"southeast", "southwest"}); 
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

void create_tio_ground_room()
{

    /*  Description  */ 
    set_short("A path beneath a village in the trees "); 

    set_long("You stand next to a small stream that flows out of " + 
        "a small pond to the southeast and winds its way " + 
        "between the giant oaks that make up this part of the " + 
        "forest. High above, nestled among the branches of the " + 
        "trees, you can see the underside of a small village. The " + 
        "ground is covered with a thick carpet of green grass. To " +
        "the southwest a small bridge crosses the stream.\n"); 

    /*  Properties  */

    add_prop(ROOM_I_TYPE, ROOM_BEACH); 
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /* Obejects */ 

    if (! find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface")) 
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    }

    Pond_Room = find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("The stream babbles as it flows past you, it's water " + 
        "clear and sparkling. It flows from the the small pond, " +
        "passes under the bridge, and continues through the trees " +
        "to the west.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    Pond = clone_object(STREAM); 
    Pond->set_name("pond"); 
    Pond->remove_name("stream"); 
    Pond->move(this_object(), 1); 
    Pond->set_object("pond"); 
    Pond->set_long(Pond_Room->describe); 

    /*  Exits  */ 

    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_10", "east"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "pond_shore", "southeast"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_02", "southwest"); 

    /*  Items  */ 

    add_item(({"path", "trail", "grass", "ground"}), 
        "The grass is thick, green, and healthy. It covers the " + 
        "ground like a carpet, filling in any empty space between " +
        "the huge trees. You can see a faint path leading to the " + 
        "east and towards the bridge.\n"); 
    
    add_item(({"trees", "oaks", "tree", "oak", "forest", "branches", 
        "leaves"}), 
        "The oaks here are incredible, making you feel tiny as you " +
        "look at them. Their upper branches and leaves block out " + 
        "most of the light before it reaches this level.\n"); 

    add_item(({"village", "walkways"}), 
        "You can't see much of the village from way down here, " + 
        "only the underside of the walkways that run between the " +
        "trees.\n"); 
    
    add_item(({"bridge", "root"}), 
        "This little bridge is quite remarkable. It crosses the " + 
        "stream with a graceful arch, the surface is " + 
        "perfectly flat, and the sides curve upwards to prevent " + 
        "anyone from falling off. However you can't see any sign " + 
        "of two pieces of wood being fastened together, and the " + 
        "bridge is covered with the same brown bark of the " + 
        "surrounding trees.\n"); 

    return; 

}
