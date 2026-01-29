/* This door leads to the Abbey on the second level of the priests' quarters.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This is a large mahogany door. The wood has been " +
        "tainted blakck and a whirling pattern of twisting thorned vines " +
        "decorates it. A large metal ring hangs on the middle of it for " +
        "opening but there is no lock.\n");
    set_door_id("abbey_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"door", "mahogany door", "black door"}));
    set_other_room( LVLTWO + "corr3.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly push the door open.\n", 
        "The black mahogany door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", ""}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the black iron door and closes it.\n", "The " +
        "black iron door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name("lock");
    set_lock_desc("There is no lock on this door.\n");
    set_lock_command("lock");
    set_lock_mess(({""}));
    set_fail_lock(({"The door does not have a lock to lock.\n", "Even if " +
        "you closed this door, you still could not lock it since there " +
        "is no lock.\n"}));
    set_unlock_command("unlock");
    set_fail_unlock("Why do you want to unlock a door that doesn't even " +
        "have a lock?\n");
}

int
lock_door(string arg)
{
    if (!lock_procedure(arg))
        return 0;
    
    if (!query_other_door())
        load_other_door();
    
    if (!query_locked())
    {
        if (query_open())
            write(check_call(query_fail_lock()[1]));
        else
            write(check_call(query_fail_lock()[0]));
    }
    else
        write(check_call(query_fail_lock()[0]));
    
    return 1;
}

int
unlock_door(string arg)
{
    if (!lock_procedure(arg))
        return 0;
    
    if (!query_other_door())
        load_other_door();
    
    if (query_locked())
    {
        write(query_fail_unlock());
    }
    else
        write(query_fail_unlock());
    
    return 1;
}
