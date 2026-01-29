#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This is a heavy black iron door without any ornaments.\n");
    set_door_id("wa_platform");
    set_pass_command(({"e","east"}));
    set_door_name(({"iron door", "door", "heavy door", "black door"}));
    set_other_room( WHITE + "platform.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try and pass " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"takes slowly pushes the door open.", 
        "The heavy black iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls on the heavy door and closes it.\n", "The heavy " +
        "black iron door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(1);
    set_lock_name("lock");
    set_lock_desc("This is a sturdy lock.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the door.\n", "A loud 'click' is heard as the " +
        "heavy iron door is locked.\n"}));
    set_fail_lock(({"But the door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the heavy iron door.\n", "A loud 'click' is " + 
        "heard as the heavy iron door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?");
    set_key("wa_platform_key");
    set_pick(80);
    set_lock_name("wa_platform_lock");
}
