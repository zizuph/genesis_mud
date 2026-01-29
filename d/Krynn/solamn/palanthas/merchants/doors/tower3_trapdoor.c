/*
 * Trap door in floor of top level of guard tower
 * in Merchants quarter of Palanthas
 * 
 * Mortis 02.2006
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("The trapdoor is a small three by three foot square of "
	+ "dark stained, thick oak planks set into the floor against the "
	+ "crenellated south wall.  It has a polished brass twist latch "
	+ "keeping it closed.\n");
    set_door_id("merchant_gtower1");
    set_pass_command(({"d","down"}));
    set_door_name(({"trapdoor", "door", "latch"}));
    set_other_room(MERCH + "merchant_tower1_2.c");
    set_open(1);
    set_fail_pass("You must first open the trapdoor before you will be able "
	+ "to use it effectively.\n");
    set_open_command(({"open", "push", "twist"}));
    set_open_mess(({"twists the brass latch and opens the oak trapdoor.\n", 
	"The oak trapdoor opens.\n"}));
    set_fail_open(({"The trapdoor is already open.\n", "The trapdoor is "
	+ " locked and will not budge.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pushes the oak trapdoor closed.\n", "The oak trapdoor "
	+ "closes.\n"}));
    set_fail_close("The trapdoor is already closed.\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is set into a brass keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the oak trapdoor.\n", "A loud 'click' is heard " +
        "as the oak trapdoor is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the oak trapdoor.\n", "A loud 'click' is " + 
        "heard as the oak trapdoor is unlocked.\n"}));
    set_fail_unlock("But the oak trapdoor is already unlocked.\n");
    set_key("guard_tower_trapdoor");
    set_pick(41);
    set_lock_name("guard_tower_trapdoor");
}
