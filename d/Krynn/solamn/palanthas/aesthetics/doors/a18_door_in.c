/*
 * Inside door of poor home a18, north exit,
 * in the Aesthetics quarter of Palanthas.
 * 
 * Mortis 09.2006
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("A dark, old, wooden door with a badly tarnished, tin "
	+ "handle and keyhole.\n");
    set_door_id("a18_frontdoor");
    set_pass_command(({"south", "out"}));
    set_door_name(({"door"}));
    set_other_room(MONKS + "a18.c");
    set_open(0);
    set_fail_pass("You must first open the door before you will be able "
	+ "to use it effectively.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"turns the badly tarnished, tin handle and opens the "
	+ "dark, old, wooden door.\n", "The thin door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is "
	+ "locked and will not budge.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the dark, old, wooden door closed.\n", "The "
	+ "dark, old, wooden door closes.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(0);
    set_lock_name(({"keyhole", "lock"}));
    set_lock_desc("The lock on this door is set into a badly tarnished, " 
	+ "tin keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the thin door.\n", "A loud 'click' is heard " +
        "as the dark, old, wooden door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the thin door.\n", "A loud 'click' is " + 
        "heard as the dark, old, wooden door is unlocked.\n"}));
    set_fail_unlock("But the dark, old, wooden door is already unlocked.\n");
    set_key("a18_frontdoor");
    set_pick(23);
    set_lock_name("a18_frontdoor");
}
