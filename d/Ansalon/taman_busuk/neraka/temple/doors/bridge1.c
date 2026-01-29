/* This is the door that opens up to the stonebridge in
 * the Great Hall of Audience.
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
        "and arched. It is made of black iron and you presume it to be very " +
        "heavy. It is beautifully engraved with pictures of dragons " +
        "swooping down over a scorched and barren landscape.\n");
    set_door_id("priest_bridge");
    set_pass_command(({"s","south"}));
    set_door_name(({"iron door", "door", "heavy door", "black door"}));
    set_other_room( TEMPLE + "bridge1.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The black iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the black iron door and closes it.\n", "The " +
        "black iron door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("This lock is made of black metal and very ornate. It has " +
        "a figure of a fierce dragon's head looking straight at you. The " +
        "dragon has its teeth bared and that is where the keyhole is.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the door.\n", "A loud 'click' is heard as the " +
        "black iron door is locked.\n"}));
    set_fail_lock(({"But the door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the black iron door.\n", "A loud 'click' is " + 
        "heard as the black iron door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?\n");
    set_key("priest_bridge_key");
    set_pick(80);
    set_lock_name("priest_dias_lock");
}

