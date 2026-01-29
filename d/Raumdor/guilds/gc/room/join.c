/*********************************************************************
 * - join.c                                                        - *
 * - This is the joining room of the Gentlemans Club located in    - *
 * - Drakmere                                                      - *
 * - Created by Damaris 10/2001                                    - *
 * - Last Modified by Valen 12/2001                                - *
 * - Last Modified by Damaris 1/2/2002                             - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"
inherit CLUB;
public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())
    {
	    /* Is a member, pass through as normal */
	    return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
        "member of the Gentleman's club!\n");
    return 1;
}
string
query_sign()
{
    return
        "               +---------------------------+\n"+
        "               |      Welcome to the       |\n"+
        "               |     Gentleman's Club      |\n"+
        "               |---------------------------|\n"+
        "               | This is an exclusive club |\n"+
        "               | for men only.             |\n"+
        "               |---------------------------|\n"+
        "               | Goblins, Minotaurs,       |\n"+
        "               | Mummers, females will not |\n"+
        "               | be allowed membership.    |\n"+
        "               |---------------------------|\n"+
        "               | To join club              |\n"+
        "               | <apply membership>        |\n"+
        "               | To leave club             |\n"+
        "               | <leave club>              |\n"+
        "               +---------------------------+\n";
}   
    
    
public void
create_guild_room()
{
    set_short("A Spacious room");
    set_long("This is a spacious room that denotes the scent of rich "+
        "herbs and spices. Scented candles have been placed on small "+
        "tables along the walls. There are also some lanterns firmly "+
        "attached to the walls themselves. A large counter of sorts is "+
        "sitting in the southwest corner with a small sign posted on it. "+
        "There is a staircase leading upwards to the private areas of "+
        "the club.\n");
    add_item(({"room", "area"}), query_long);
    add_item(({"sign"}), query_sign); 
    add_item(({"candles", "scented candles", "candle", "scented candle"}),
        "There are scented candles resting on some small tables.\n");
    add_item(({"table", "tables", "small table", "small tables"}),
        "There are small tables scattered in various places against the "+
        "walls, but done in a very orderly fashion.\n");
    add_item(({"counter", "large counter"}),
        "There is a large counter situated in the southwest corner.\n");
    add_item(({"stairs", "starcase", "stairway", "up"}),
        "There is a a highly polished stairway leading upward.\n");
    add_item(({"north", "south", "east", "west", "northwest"}),
        "There is a doorway in that direction.\n");
    add_item(({"southeast", "southwest", "northeast"}),
       "There is a wall in that direction.\n");

    add_exit("dining", "north");
    add_exit("gshop", "south");
    add_exit(DRAKMERE_DIR + "road04", "east");
    add_exit("gsit","west");
    add_exit("lobby", "up", members_only);
    add_exit("smoke", "northwest");
    set_no_exit_msg(({"northeast", "southwest", "southeast"}),
        "You walked into a wall.\n"+
        "OUCH! That's gotta hurt!\n");
}

int
apply_member(string str)
{
    if((str != "membership") && (str != "for membership"))
    {
        notify_fail("Apply for what? Membership perhaps?\n");
        return 0;
    }
    
    if (this_player()->query_gender() == G_FEMALE) 
    {
        write("Women aren't accepted in the Gentleman's club.\n"+
              "Your application has been denied!\n");
        return 1;
    }    

    if (this_player()->query_race_name() == "goblin") 
    {
        write("Goblins aren't accepted in the gentleman's club.\n"+
              "Your application has been denied!\n");
        return 1;
    }
    
    if (this_player()->query_race_name() == "minotaur") 
    {
        write("Minotaurs aren't accepted in the gentleman's club.\n"+
              "Your application has been denied!\n");
        return 1;
    }

    /* Verify if player is not Mummer of Sybarus. */
    if (this_player()->query_prop("_live_i_am_mummer"))
    {
        write("Gentlemen's club do not accept mummers.\n"+
              "Your application has been denied!\n");
       return 1;
    }

    if (present(OBJECT_ID, this_player()))
    {
      write("You are a member already!\n");
      return 1;
    }

    clone_object(OBJECT)->move(this_player());

    if(!(this_player()->add_cmdsoul(GUILD_SOUL)))
    {
        write("cmdsoul addition problem\n");
    }
    
    this_player()->update_hooks();
    write("Your membership has been accepted! A young human boy "+
          "hands you a black top hat.\n"+
          "Welcome to the Gentleman's club!\n"+
          "Please type <gchelp>.\n");

    write_file("/d/Raumdor/guilds/gc/log/membership",
               ctime(time()) + " " +
               capitalize(this_player()->query_real_name()) +
               " joined (age = " + (this_player()->query_age() / 43200) +
               ", avg = " + this_player()->query_average_stat() + ").\n");
                            
    return 1;
}

int
leave_club(string str)
{
    object ob;    

    if(str != "club")
    {
        notify_fail("Leave what? A club perhaps?\n");
        return 0;
    }

    if (!(ob = present(OBJECT_ID, this_player())))
    {
        write("You are not a member of the club!\n");
        return 1;
    }

    write_file("/d/Raumdor/guilds/gc/log/membership",
               ctime(time()) + " " +
               capitalize(this_player()->query_real_name()) +
               " left (age = " + (this_player()->query_age() / 43200) +
               ", avg = " + this_player()->query_average_stat() + ").\n");

    if (!this_player()->remove_cmdsoul(GUILD_SOUL)) 
    {
        write("It doesn't seem you were a member anyway.\n");
        return 1;
    }
    
    if(ob) ob->remove_object();   
    this_player()->update_hooks();
    write("Your application to leave the Gentleman's club has "+
          "been accepted.\n");
    return 1;
}

/**********************************************************************
 * - Function name: do_read                                         - *
 * - Description:   If a player wants to know what instructions can - *
 * -                be used.                                        - *
 * - Arguments:     str - string, hopefully "sign"                  - *
 * - Returns:       1/0                                             - *
 **********************************************************************/
int
do_read(string str)
{
    if (str != "sign")
    {
        notify_fail("Read what?\n");
        return 0;
    }

    write(query_sign());
    return 1;
}

void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with sweet spices and herbs.\n");
        return;
    }

    if ((str == "candle") || (str == "candles") || (str == "scented candle") ||
            (str == "scented candles"))
    {
        write("A soft sweet scent of jasmine and other spices intoxicates "+
            "your senses.\n");
       return;
    }
   
}

void
init()
{
    ::init();
    add_action(apply_member, "apply");
    add_action(leave_club, "leave");
    add_action(do_read, "read");
}
