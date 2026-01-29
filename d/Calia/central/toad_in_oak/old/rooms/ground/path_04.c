/*
 * /d/Calia/central/toad_in_oak/rooms/ground/path_04.c
 *
 * A path at the ground level of Toad-in-Oak, near the west side of
 * the village, just north of the village green.
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

    set_short("A path beneath a village in the trees"); 

    set_long("You stand among the tremendous trees that make up " + 
        "this part of the forest, their leaves far above blocking " +
        "most of the light and giving the area a look of perpetual " + 
        "twilight. Far above you can see what appears to be a " + 
        "small village nestled among the branches of the trees. A " + 
        "relatively narrow strip of lush grass covers the ground " + 
        "between a small stream to the east and a dense thicket to " + 
        "the west. The area is filled with the scent of the trees " + 
        "and the pleasant sounds of songbirds and tree frogs.\n"); 

    /*  Set properties. */

    add_prop(ROOM_I_TYPE, ROOM_BEACH); 
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /* Obejects */ 

    Stream = clone_object(STREAM); 
    Stream->move(this_object(),1); 
    Stream->set_long("The stream of clear blue water makes a soft babbling " + 
        "as it flows past you on it's way through the forest.\n"); 
    Stream->set_adjectives(({"clear", "small", "sparkling"})); 
    Stream->add_item(({"water", "sparkling water"}), Stream->query_long()); 

    /*  Exits  */ 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "path_03", "northwest"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "south"); 
    add_exit(TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "southeast"); 

    /*  Items  */ 

    add_item(({"path", "trail", "grass"}), 
        "The grass around here thrives despite the lack of " + 
        "light, covering the ground like a thick green rug. " + 
        "Here the grass is merely a narrow strip between the " + 
        "water and the wall of vegetation, but to the south and " + 
        "the southeast you can see that it widens into a large " + 
        "clearing.\n"); 

    add_item(({"trees", "oaks", "oak", "tree", "forest"}), 
        "The trees here are titanic, stretching so far above you " + 
        "that they seem to touch the sky. Their upper leaves form " + 
        "a green ceiling far above, letting little light reach the " + 
        "ground.\n"); 

    add_item(({"village", "walkways"}), 
        "You can see the underside of the village walkways among " + 
        "the branches high above you, but it's impossible to see " + 
        "any details from down here.\n"); 

    add_item(({"vegetation", "thicket", "branches", "vines", 
        "thorns", "wall", "shrubs"}), 
        "A dense tangle of shrubs, fallen branches, and thorny " + 
        "vines forms a natural wall to the west of you.\n"); 

    add_item(({"clearing"}), 
        "South of here you can see a large area of open grass, " + 
        "but you can't see any great detail from here.\n"); 

    if (! find_object(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface")) 
    {
        force_load_room(TOAD_IN_OAK_ROOMS_GROUND + "pond_surface"); 
    }

}
