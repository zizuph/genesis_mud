/*
 * Outside door to Kirk's hq on Jems Court
 * in Aesthetics quarter of Palanthas.
 * 
 * Mortis 05.2006
 *
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("An old, nicked, cut, and graffit covered wooden door with "
	+ "a new, iron handle and keyhole.\n");
    set_door_id("brix_kirk_frontdoor");
    set_pass_command(({"east","in", "door"}));
    set_door_name(({"door"}));
    set_other_room(MONKS + "brix_kirk_parlour.c");
    set_open(0);
    set_fail_pass("You must first open the door before you will be able "
	+ "to use it effectively.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"turns the new, iron handle and opens the "
	+ "old, nicked, cut, and graffit covered wooden door.\n", "The old, "
	+ "wooden door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is "
	+ "locked and will not budge.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the old, nicked, cut, and graffit covered wooden "
	+ "door closed.\n", "The old, wooden door closes.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(1);
    set_lock_name(({"keyhole", "lock"}));
    set_lock_desc("The lock on this door is set into a new, iron keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the old, wooden door.\n", "A loud 'click' is heard "
	+ "as the old, wooden door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock "
	+ "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the old, wooden door.\n", "A loud 'click' is "
	+ "heard as the old, wooden door is unlocked.\n"}));
    set_fail_unlock("But the old, wooden door is already unlocked.\n");
    set_key("brix_kirk_frontdoor");
    set_pick(43);
    set_lock_name("brix_kirk_frontdoor");
}
