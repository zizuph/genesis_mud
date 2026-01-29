/*
 * Office door out of private office on office floor of
 * merchant house Trusq estate in Shipping quarter
 * of Palanthas
 * 
 * Mortis 03.2006
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This oak door leads out of this private office in the "
	+ "west of the room.  It has a polished brass handle with a "
	+ "keyhole.\n");
    set_door_id("trusq_office_door");
    set_pass_command(({"west","out", "door"}));
    set_door_name(({"door"}));
    set_other_room(SHIP + "trusq_office.c");
    set_open(0);
    set_fail_pass("You must first open the door before you will be able "
	+ "to use it effectively.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"turns the brass handle and opens the oak door.\n", 
	"The oak door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is "
	+ "locked and will not budge.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the oak door closed.\n", "The oak door "
	+ "closes.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is set into a keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the oak door.\n", "A loud 'click' is heard " +
        "as the oak door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the oak door.\n", "A loud 'click' is " + 
        "heard as the oak door is unlocked.\n"}));
    set_fail_unlock("But the oak door is already unlocked.\n");
    set_key("trusq_office_door");
    set_pick(29);
    set_lock_name("trusq_office_door");
}
