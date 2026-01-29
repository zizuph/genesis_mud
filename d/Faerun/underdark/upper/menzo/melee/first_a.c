/*
 *  faerun/underdark/upper/menzo/melee/first_a1.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
 */

#include "defs.h"
#include <stdproperties.h>
#include <filter_funs.h>

inherit P_MENZO_MELEE + "std/base_room";

#define THIS_ROOM P_MENZO_MELEE + "first_a1.c"


/*
 * Function name: create_melee_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_melee_room()
{
	set_short("Training arena of Melee-magthere");
	set_long("Training arena....\n");
        
        add_exit("first_a2","east", "@@remove_slowness");
        add_exit("first_a3","north", "@@remove_slowness");
        add_exit("first_a7","south", "@@remove_slowness");
        add_exit("first52","west", "@@remove_slowness");

}

add_slowness()
{
    object *obs;

    // Find the players in our inventory
    obs = FILTER_LIVE(THIS_ROOM->subinventory());

    obs->catch_msg("You find it difficult to move " +
        "on this rocky ground.\n");
    obs->add_prop(LIVE_I_QUICKNESS, -3);
}

remove_slowness()
{
    object *obs;

    // Find the players in our inventory
    obs = FILTER_LIVE(THIS_ROOM->subinventory());
    obs->catch_msg("With relief you leave " +
        "the sharp rocky floor.\n");
    obs->add_prop(LIVE_I_QUICKNESS, 0);
}

/*
 * Function name: enter_env
 * Description  : Called when we enter the environment
 * Arguments    : to, from
 */
void enter_env(object to, object from)
{
    ::enter_env(to, from);
    add_slowness();
}