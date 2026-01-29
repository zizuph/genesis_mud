/* This is the door that leads from the room of the Nightlord/lady.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This door is approximately six feet high, four feet wide " +
        "and arched. It is made of well-polished oak and on the centre of " +
        "the door is an inlay of onyx in the shape of a crescent.\n");
    set_door_id("priest_inquisitor_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"door", "oak door", "well-polished door"}));
    set_other_room( DUNGTWO + "court.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The oak door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the oak door closed.\n", "The " +
        "oak door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("The lock on this door is made of bronze and has a small " +
        "decore of silverthread in the form of a thorned vine which circles " +
        "the keyhole.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the oak door.\n", "A loud 'click' is heard as the " +
        "oak door is locked.\n"}));
    set_fail_lock(({"But the door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the oak door.\n", "A loud 'click' is " + 
        "heard as the oak door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?\n");
    set_key("priest_inquisitor_key");
    set_pick(80);
    set_lock_name("priest_inquisitor_lock");
}
