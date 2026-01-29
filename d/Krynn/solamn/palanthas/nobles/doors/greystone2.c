/*
 * The main entrance door of the Greystone Inn of Palanthas.
 * 
 * Mortis 11.2005
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("The door leading southwest into the Greystone Inn is "
	+ "of thick, dark-stained mahogany.  It appears quite old and very "
	+ "solid.  Ornate curves rim its outer edges and the name \"Havecius\""
	+ "is carved in the formal, blocky ancient style at shoulder height.  "
	+ "Its dark, wrought iron handle bears ornate twists down its human "
	+ "hand sized length.\n");
    set_door_id("greystone_entrance");
    set_pass_command(({"sw","southwest", "in"}));
    set_door_name(({"door", "entrance"}));
    set_other_room(NOBLE + "greystone.c");
    set_open(1);
    set_fail_pass("You must first open the door before you will be able to "
	+ "use it effectively.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"pushes the door open.\n", 
        "The mahogany door opens.\n"}));
    set_fail_open(({"The door is already open.\n", "The door is locked " +
        "and will not budge.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the mahogany door closed.\n", "The " +
        "mahogany door closes.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is set into a dark iron keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the mahogany door.\n", "A loud 'click' is heard " +
        "as the mahogany door is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the mahogany door.\n", "A loud 'click' is " + 
        "heard as the mahogany door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?\n");
    set_key("greystone_entrance");
    set_pick(46);
    set_lock_name("greystone_entrance");
}
