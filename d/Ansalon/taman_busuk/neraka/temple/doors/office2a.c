/* This is one of the doors which leads to one of the offices.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This is a dark wooden door. It is decorated with " +
        "a carving of a small dragon tearing the flesh from the bones " +
        "of a screaming elf.\n");
    set_door_id("office2_door");
    set_pass_command(({"se","southeast"}));
    set_door_name(({"door", "dark door", "wooden door", "dark wooden door"}));
    set_other_room( LVLTWO + "office2.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The dark wooden door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is locked " +
        "and probably for a good reason.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the dark wooden door and closes it.\n", "The " +
        "dark wooden door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("This lock is made of dark metal and shaped as a " +
        "ogre's head.\n");
    set_lock_command("lock");
    set_lock_mess(({"locks the door.\n", "A loud 'click' is heard as the " +
        "dark wooden door is locked.\n"}));
    set_fail_lock(({"But the door is already locked.\n", "You cannot lock " +
        "this door when it is open.\n"})); 
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the dark wooden door.\n", "A loud 'click' is " + 
        "heard as the dark wooden door is unlocked.\n"}));
    set_fail_unlock("Why unlock an already unlocked door?\n");
    set_key("office2_key");
    set_pick(80);
    set_lock_name("office2_lock");
}

