/* This door leads to the Abbey on the second level of the priests' quarters.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit "/std/door";

#include <stdproperties.h>
#include <macros.h>

void
create_door()
{
    set_door_desc("This is a large iridescent black mahogany door. The " +
        "hinges set in the very stone looks strong. Apart from an " +
        "indentation in the middle of the door it is unadorned.\n");

    add_item("hinges", "They appear very strong.\n");
    add_item("indentation", "It is in oval in shape and no bigger " +
        "than a fist.\n");
         
    set_door_id("eqshop_door");
    set_pass_command(({"ne","northeast"}));
    set_door_name(({"black mahogany door", "door", "black door",
        "iridescent black mahogany door", "mahogany door"}));
    set_other_room( DUNGONE + "corr8.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "push"}));
    set_open_mess(({"slowly push the door open.\n", 
        "The black mahogany door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", ""}));
    set_close_command(({"close", "pull"}));
    set_close_mess(({"pulls the black mahogany door and closes it.\n", "The " +
        "black mahogany door closes slowly.\n"}));
    set_fail_close("Why would you want to close an already closed door?\n");
}

int
open_door(string arg)
{
    if (member_array(arg, query_door_name()) < 0)
        return 0;
    
    if (!query_other_door())
        load_other_door();
    
    if (!query_open())
    {
        if (this_player()->query_guild_name_occ() != GUILD_NAME &&
            !present("takhisis_medallion", this_player()))
            write("There is no visible means of opening the door that " +
                "will not move.\n");
        else
        {
            write("You put your medallion in the indentation and the " +
                "door opens.\n");
            say(QCTNAME(this_player()) + " puts " +
                this_player()->query_possessive() + " medallion into " +
                "the indentation on the door and it opens.\n", this_player());
            do_open_door("");
            query_other_door()->do_open_door(check_call(query_open_mess()[1]));
        }
    }
    else
        write(check_call(query_fail_open()[0]));
    
    return 1;
}

int
close_door(string arg)
{
    if (member_array(arg, query_door_name()) < 0)
        return 0;
    
    if (!query_other_door())
        load_other_door();
    
    if (query_open())
    {
        if (this_player()->query_guild_name_occ() != GUILD_NAME &&
            !present("takhisis_medallion", this_player()))
        {
            write("There is no visible means of closing the door that " +
                "will not move.\n");
        }
        else
        {
            write("You put your medallion into the indentation and " +
                "it closes.\n");
            say(QCTNAME(this_player()) + " puts " +
                this_player()->query_possessive() + " medallion into the " +
                "indentation on the door and it closes.\n");
            do_close_door("");
            query_other_door()->do_close_door(check_call(query_close_mess()[1]));
        }
    }
    else
        write(check_call(query_fail_close()));
    
    return 1;
}
