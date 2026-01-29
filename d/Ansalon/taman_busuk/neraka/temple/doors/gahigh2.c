/* This door leads to the most secret and vulnerable area of the temple.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This is a very large door made of black iron. " +
        "It has a large lock on it.\n");
    set_door_id("gahigh_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"door", "iron door", "black door", "large door"}));
    set_other_room( GREEN + "stair3.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly pushes the door open.\n", 
        "The black iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is " +
        "locked.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the black iron door and closes it.\n", "The " +
        "black iron door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("It is large and very complex lock.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the black iron door.\n", "A loud 'klick' " +
        "is heard from the black iron door as it is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "The door needs to " +
        "be closed before you can lock it.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the black iron door.\n", "A loud " +
        "'klick' is heard from the black iron door as someone locks " +
        "it.\n"}));
    set_fail_unlock("Why do you want to unlock a door that is already " +
        "locked?\n");
    set_key("green_high_key");
    set_pick(90);
}
