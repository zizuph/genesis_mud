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
    set_door_desc("This is a large iridescent black iron door. The " +
        "hinges set in the very stone looks strong. Apart from an " +
        "indentation in the middle of the door it is unadorned.\n");

    add_item("hinges", "They appear very strong.\n");
    add_item("indentation", "It is in oval in shape and no bigger " +
        "than a fist.\n");
         
    set_door_id("labbey_door");
    set_pass_command(({"w","west"}));
    set_door_name(({"black iron door", "door", "black door",
        "iridescent black iron door", "iron door"}));
    set_other_room( DUNGONE + "darkabbey.c");
    set_open(0);
    set_fail_pass("You stop as you realize how silly it is to try to walk " +
        "through a closed door.\n");
    set_open_command(({"open", "pull"}));
    set_open_mess(({"slowly pulls the door open.\n", 
        "The large iridescent black iron door opens slowly.\n"}));
    set_fail_open(({"But the door is already open.\n", ""}));
    set_close_command(({"close", "push"}));
    set_close_mess(({"pushes the black iron door and closes it.\n", "The " +
        "large iridescent black iron door closes slowly.\n"}));
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
