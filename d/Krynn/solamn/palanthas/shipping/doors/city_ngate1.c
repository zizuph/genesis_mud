/*
 * The North City Gate of Palanthas
 * Too large for most mortals to open alone.  Team can push open.
 * Gatemaster in northern tower well has capability to operate the
 * doors.  Can be bribed for 15 plats to open the gates?  He does
 * not have the key to lock/unlock them.
 * The Chief Officer of the Constabulary of Palanthas has access to
 * the key that fits the city gates.
 *
 * Mortis 10.05
 */

#pragma strict_types

#include "../../local.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("The NORTH Gate.\n");
    set_door_id("city_north_gate");
    set_pass_command(({"n","north"}));
    set_door_name(({"gate", "north gate", "north gates"}));
    set_other_room(SHIP + "tr4.c");
    set_open(1);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly pushes the door open.\n", 
        "The oak door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the oak door closed.\n", "The " +
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
    set_key("palanthas_city_key");
    set_pick(80);
    set_lock_name("city_north_gate");
}
