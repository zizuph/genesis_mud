/* This door leads to the most secret and vulnerable area of the temple.
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_door()
{
    set_door_desc("This is a very large door made of thick oak.\n");
    set_door_id("raent_door");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({"door", "oak door", "heavy oak door", "large oak door"}));
    set_other_room( RED + "entrance.c");
    set_open(1);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly pushes the door open.\n", 
        "The heavy oak iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", "The door is " +
        "locked.\n"}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the heavy oak door and closes it.\n", "The " +
        "heavy oak door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
}

int
open_door(string str)
{
    if (member_array(str, query_door_name()) < 0)
        return 0;
    
    if (!query_other_door())
        load_other_door();
    
    if (!query_open())
    {
        if (query_locked())
            write(check_call(query_fail_open()[1]));
        else
            write("The door is devised as to open from the inside.\n");
    }
    else
        write(check_call(query_fail_open()[0]));

    return 1;
}

int
close_door(string str)
{
    if (member_array(str, query_door_name()) < 0)
        return 0;
     
    if (!query_other_door())
        load_other_door();
     
    if (query_open())
        write("The door is devised as to close from the inside.\n");
    else
        write(check_call(query_fail_close()));
    
    return 1;
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
