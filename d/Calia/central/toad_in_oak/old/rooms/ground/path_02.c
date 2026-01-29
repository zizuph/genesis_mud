/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_02.c
 *
 * A path on the ground level of the village of Toad-In-Oak near the
 * west side of the village, and next to the duck pond
 * 
 * HISTORY: [99-03-03] Created by Kcirderf 
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
    return ({"northeast", "south"}); 
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
    set_short("A path beneath a village in the trees"); 

    set_long("You are standing among the giant oaks that " + 
        "dominate this part of the forest, their leaves high above " + 
        "casting green shadows on the ground. High above you can " +
        "see the underside of a village built in the trees. A " + 
        "thick layer of green grass covers the ground " + 
        "from the small pond and stream that flows from it to the " +
        "dense thicket that lies west of you. A little bridge " + 
        "has been built a short distance downstream from the pond.\n"); 
    
    /*  Set properties. */

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
    Stream->set_long("A stream of clear blue water flows from the pond, " + 
        "making a babbling noise as it flows to the northwest. A wooden " + 
        "crosses the stream, allowing you to walk northeast from " + 
        "here.\n"); 
    Stream->set_adjectives(({"clear", "small", "blue"})); 
    Stream->add_item(({"water", "blue water", 
        "clear water", "clear blue water"}), Stream->query_long()); 

    Pond = clone_object(STREAM); 
    Pond->set_name("pond"); 
    Pond->remove_name("stream"); 
    Pond->move(this_object(), 1); 
    Pond->set_object("pond"); 
    Pond->set_long(Pond_Room->describe); 

    /*  Exits  */ 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_01", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_03", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_11", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW+ "walkway_17", "up"); 

    /*  Items  */ 
      
    add_item(({"path", "trail", "grass"}), 
        "The grass here is green and healthy even though little " + 
        "sunlight reaches it. It covers the ground like a thick " + 
        "carpet and feels springy under your feet. You can make " + 
        "out a faint path along the bank of the stream leading " + 
        "to the northwest and the south and also to the bridge.\n"); 

    add_item(({"trees", "tree", "oaks", "forest"}), 
        "The trees here are tremendous, reaching high into the " + 
        "air above you. Their upper branches and leaves form a " + 
        "canopy that covers the ground in ever shifting green " + 
        "shadows.\n"); 

    add_item(({"vegetation", "thicket", "shrubs", "vines", 
        "thorns", "wall"}), 
        "A dense thicket of twisted branches and vines, all " + 
        "covered in needle like thorns lies a little to the west " +
        "of the path here.\n"); 

    add_item(({"bridge", "root"}), 
        "The little bridge is a remarkable structure. It forms a " + 
        "graceful arch across the stream and the surface is flat " + 
        "from side to side except at the very edge were it curves " +
        "upwards to prevent anyone from falling off. It could " + 
        "have been carved from a single piece of wood as you can " + 
        "find no sign of the wood being joined anywhere. The " + 
        "bridge is the same brown as the trunks of the nearby " + 
        "trees and gives off the same fresh smell as the living " + 
        "oaks.\n");

    add_item(({"village", "walkways"}), 
        "You can see the underside of the village walkways in " + 
        "the trees above you, but it's impossible to make out any " + 
        "details from this angle.\n"); 

}
