/*
 * /d/Calia/central/toad_in_oak/rooms/ground/pond_surface.c
 *
 * This is the surface of the Toad-in-Oak duck pond. This is a special 
 * room used only as a place for ducks and other animals to swim. No mortal
 * will ever get in here.  
 *
 * HISTORY: [99-07-13] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground"; 

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#include "defs.h"

#define DUCK TOAD_IN_OAK_ANIMALS + "duck"

// GLOBAL VARIABLES

string* Pond_Rooms = ({ TOAD_IN_OAK_ROOMS_GROUND + "pond_shore", 
                        TOAD_IN_OAK_ROOMS_GROUND + "path_01", 
                        TOAD_IN_OAK_ROOMS_GROUND + "path_02", 
                        TOAD_IN_OAK_ROOMS_GROUND + "path_03", 
                        TOAD_IN_OAK_ROOMS_GROUND + "path_04",
                        TOAD_IN_OAK_ROOMS_GROUND + "path_11"});

// FUNCTIONS

/* Forward Declarations */ 

string contents(); 
string describe(); 
void enter_inv(object ob, object from);
void leave_inv(object ob, object to); 
void move_duck(); 

/*
 * Function name: contents
 * Description:   Describes what's currently swimming around on the pond
 * Arguments:     None.
 * Returns:       string describing the contents
 */
string
contents()
{
    object *living_things; 
    string contents = "";     
    
    living_things = FILTER_LIVE(all_inventory(this_object())); 
    if (sizeof(living_things)) 
    {
        contents = " You can see " + COMPOSITE_ALL_LIVE(living_things) + 
            " on the surface of the pond."; 
    }        
    return contents; 
}

/*
 * Function name: describe
 * Description:   Describes the Toad-in-Oak duck pond, including
 *                any ducks currently on it. 
 * Arguments:     None.
 * Returns:       string describing the pond
 */
string
describe()
{
  
    return "The stream that flows through the village has formed " +
        "a small pond here. The water looks to be a little muddy " +
        "as if something had been stirring up the mud at the " + 
        "bottom." + contents() + "\n"; 
}

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

/*  Name:       move_duck
    Purpose:    Moves a duck into or out of the pond
    Arguments:  None
    Returns:    Nothing
*/ 
void
move_duck()
{
    object duck; 
    object here = this_object(); 
    int next; 

    if (Control_Room->count("duck") > 0)
    {
        duck = Control_Room->random_item("duck"); 
        if (environment(duck) == here)
        {
            duck->move_living("X", Pond_Rooms[random(sizeof(Pond_Rooms))], 0 ,0); 
        }
        else
        {
            duck->move_living("X", here, 0, 0); 
        }

        next = (20 + random(40)) / (Control_Room->count("duck")); 

//      set_alarm(itof(next), 1.0, move_duck); 
//      tell_room(here, "Next duck moves in " + next + " seconds.\n"); 
    }
    return;
}
     
// ROOM DEFINITION

void 
reset_room()
{
    int ducks_needed = 4 - Control_Room->count("ducks"); 
    int x; 
    object duck; 

    for (x = 0; x < ducks_needed; x++)
    {
        duck = clone_object(DUCK); 
        duck -> move_living("X", this_object()); 
    }

}

void
create_tio_ground_room()
{

    /* Descriptions */ 

    set_short("The surface of the Toad-in-Oak duck pond"); 

    set_long("You are standing on the surface of a small pond. How are " + 
        "accomplishing this miraculous feat? I have no idea. If you " + 
        "aren't a wizard, you shouldn't be able to get here, and if you " + 
        "are you should go away and stop pestering the ducks. This room " + 
        "is only here so some aquatic animals can get away from mortals, " +
        "and so that they can be seen from the edges of the pond.\n"); 
 
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_room(); 

//    move_duck(); 
    
    return; 
}


