/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_03.c
 *
 * A path on the ground level of the village of Toad-In-Oak near the
 * west side of the village, and next to the duck pond
 * 
 * HISTORY: [99-03-04] Created by Kcirderf 
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
    return ({"north"}); 
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

    set_long("You are standing near a small pond surrounded by " +
        "the spectacular oaks that make up this part of the " + 
        "forest. From the pond and the little stream to the " +
        "dense thicket to the west, the ground is carpeted " + 
        "with thick green grass. High above among the branches of " + 
        "the trees you see the underside of a small village. The " + 
        "smell of oak mixes with that of the grass to give the " + 
        "area a pleasant smell.\n"); 

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
    Stream->set_long("The water of the small stream is clear and bright, " +
        "and sparkles as it flows into the pond.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    Pond = clone_object(STREAM); 
    Pond->set_name("pond"); 
    Pond->remove_name("stream"); 
    Pond->move(this_object(), 1); 
    Pond->set_object("pond"); 
    Pond->set_long(Pond_Room->describe); 

    /*  Exits  */ 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_02", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04", "southeast"); 

    /* Items */ 

    add_item(({"path", "trail", "grass"}),
        "The grass here is is green and healthy despite the " + 
        "dim light of the area. Along the edge of the pond you " + 
        "can see a faint path leading from the north to the " + 
        "southeast.\n"); 

    add_item(({"trees", "oaks", "tree", "forest"}), 
        "The trees here are true giants, their highest leaves and " +
        "branches forming a ceiling far above you, covering the " + 
        "ground with eternal twilight.\n"); 

    add_item(({"vegetation", "thicket", "shrubs", "vines", 
        "thorns", "wall"}), 
        "A dense tangle of branches, shrubs, and vines covered in " +
        "unpleasant looking thorns forms an impassible barrier " + 
        "a little ways west of the pond.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see the underside of the village walkways in " + 
        "the trees above you, but it's impossible to make out any " + 
        "details from this angle.\n"); 
}
