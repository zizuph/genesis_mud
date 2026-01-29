/*
 * Back door for servants in merchant house Trusq estate
 * in Shipping quarter of Palanthas
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
    set_door_desc("This thin door is the servants entrance into the "
	+ "estate.  It has a tarnished brass handle with a large keyhole.\n");
    set_door_id("trusq_backdoor");
    set_pass_command(({"north","in", "door"}));
    set_door_name(({"door", "backdoor"}));
    set_other_room(SHIP + "trusq_kitchen.c");
    set_open(0);
    set_fail_pass("You must first open the door before you will be able "
	+ "to use it effectively.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"turns the brass handle and opens the thin door.\n", 
	"The thin door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is "
	+ "locked and will not budge.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the thin door closed.\n", "The thin door "
	+ "closes.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is set into a large keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the thin door.\n", "A loud 'click' is heard " +
        "as the thin door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the thin door.\n", "A loud 'click' is " + 
        "heard as the thin door is unlocked.\n"}));
    set_fail_unlock("But the thin door is already unlocked.\n");
    set_key("trusq_backdoor");
    set_pick(28);
    set_lock_name("trusq_backdoor");
}
