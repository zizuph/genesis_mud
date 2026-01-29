/* This door leads to the most secret and vulnerable area of the temple.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <language.h>
#include "/d/Ansalon/guild/pot/guild.h"

void
create_door()
{
    set_door_desc("This is a very large door made of black iron. " +
        "It has a large lock on it.\n");
    set_door_id("cavern_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"door", "iron door", "black door", "large door"}));
    set_other_room( DUNGTHREE + "cavern1.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The black iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is " +
        "locked.\n"}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the black iron door and closes it.\n", "The " +
        "black iron door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
    set_locked(1);
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
    set_key("cavern_key");
    set_pick(90);
    set_lock_name("cavern_lock");
}

int
pass_door(string str)
{
    int dexh;
    string verb = query_verb();

    /* query_verb() will change in this function which is why we need
     * to copy the code from the ::pass_door instead of simply returning
     * that
     */
    if (environment()->check_guards())
        return 1;
    else
    {
        if (!query_other_door())
            load_other_door();
            
        dexh = 2 + (this_player()->query_stat(SS_DEX) / 25);

        if (query_open())
        {
            if ((int)this_player()->query_prop(CONT_I_HEIGHT) >
                query_prop(DOOR_I_HEIGHT) * dexh)
            {
                write("The " + query_door_name()[0] + " is more than " +
                    LANG_WNUM(dexh) + " times lower than you.\n" +
                    "You're too tall and not enough dexterous to get through.\n");
                return 1;
            }
            else if((int)this_player()->query_prop(CONT_I_HEIGHT) >
                query_prop(DOOR_I_HEIGHT))
            {
                write("You bend down to pass through the " + short() + ".\n");
                tell_room(environment(this_object()), QCTNAME(this_player()) +
                    " bends down to pass through the " + query_door_name()[0] +
                    ".\n", this_player());
            }
            
            this_player()->move_living(verb, query_other_room());
        }
        else
            write(check_call(query_fail_pass()));
       
        return 1;
    }
}            
