/*
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include "/d/Ansalon/guild/pot/guild.h"

string
door_cond()
{
    if (query_locked())
    {
        return "placed across the door that barrs it shut";
    }
    else
    {
        return "that can be lowered down barring it shut";
    }
}

void
create_door()
{
    set_door_desc("This is a very large door made of thick oak. " +
        "It has a wooden beam @@door_cond@@.\n");
    set_door_id("bkaent_door");
    set_pass_command(({"e","east"}));
    set_door_name(({"door", "oak door", "heavy oak door", "large oak door"}));
    set_other_room( NINNER + "s22.c");
    set_open(1);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The heavy oak door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is " +
        "locked.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the heavy oak door and closes it.\n", "The " +
        "heavy oak door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(0);
    set_lock_name(({"lock", "beam", "wooden beam"}));
    set_lock_desc("It is a wooden beam that can be lowered as to barr " +
        "the door.\n");
    set_lock_command(({"lock", "lower", "move"}));
    set_lock_mess(({"lowers the wooden beam infront of the heavy oak door.\n",
        "A loud noise is heard from the heavy oak door as it is locked.\n"}));
    set_fail_lock(({"The door is already locked.\n", "The door needs to " +
        "be closed before you can lock it.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"unlocks the heavy oak door.\n", "A loud " +
        "noise is heard from the black iron door as someone unlocks " +
        "it.\n"}));
    set_fail_unlock("Why do you want to unlock a door that is already " +
        "locked?\n");
}
