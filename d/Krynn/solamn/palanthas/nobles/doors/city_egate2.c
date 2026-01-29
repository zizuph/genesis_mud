/*
 * The East City Gate of Palanthas
 * Too large for most mortals to open alone.  Team can push open.
 * Gatemaster in southern tower well has capability to operate the
 * doors.  Can be bribed for 15 plats to open the gates.  He does
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
    set_door_desc("The EAST Gate.\n");
    set_door_id("city_east_gate");
    set_pass_command(({"w","west"}));
    set_door_name(({"gate", "east gate", "east gates"}));
    set_other_room(NOBLE + "er5.c");
    set_open(1);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed gate.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly pushes the gate open.\n", 
        "The metal gate opens slowly.\n"}));
    set_fail_open(({"But the gate is already open.\n", "The gate is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the metal gate closed.\n", "The " +
        "metal gate closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed gate?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("This is the gate's lock.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the metal gate.\n", "A loud 'click' is heard as the " +
        "metal gate is locked.\n"}));
    set_fail_lock(({"But the gate is already locked.\n", "You cannot lock " +
        "this gate when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the metal gate.\n", "A loud 'click' is " + 
        "heard as the metal gate is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked gate?\n");
    set_key("palanthas_city_key");
    set_pick(80);
    set_lock_name("city_east_gate");
}
