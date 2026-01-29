/*********************************************************************
 * - join.c                                                        - *
 * - This is the joining room of the Ladies Club located in        - *
 * - Drakmere                                                      - *
 * - Created by Damaris 5/2003                                     - *
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
        "member of the Ladies club!\n");
    return 1;
}

string
query_sign()
{
    return
        "               +---------------------------+\n"+
        "               |      Welcome to the       |\n"+
        "               |        Ladies Club        |\n"+
        "               |---------------------------|\n"+
        "               | This is an exclusive club |\n"+
        "               | for ladies only.          |\n"+
        "               |---------------------------|\n"+
        "               | Goblins, Minotaurs, males |\n"+
        "               | and dancers will not be   |\n"+
        "               | allowed membership.       |\n"+
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
    set_short("An intimate parlor");
    set_long("This is an intimate parlor that denotes the sweet scents "+
        "of rich herbs and spices along with delecate perfumes. There are "+
        "scented candles placed upon a few small tables along the walls. "+
        "There are also some delicate lanterns firmly attached to the "+
        "walls themselves. A charming counter with a sign is sitting before "+
        "a large staircase that leads upwards to the private areas of "+
        "the club.\n");
    add_item(({"room", "area", "parlor"}), query_long);
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
     
    add_exit(DRAKMERE_DIR + "road05", "west");
    add_exit("lobby", "up", members_only);
    add_exit("lsit", "northeast");
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
    
    if (this_player()->query_gender() == G_MALE) 
    {
        write("Males aren't accepted in the Ladies club.\n"+
              "Your application has been denied!\n");
        return 1;
    }    

    if (this_player()->query_race_name() == "goblin") 
    {
        write("Goblins aren't accepted in the Ladies club.\n"+
              "Your application has been denied!\n");
        return 1;
    }
    
    if (this_player()->query_race_name() == "minotaur") 
    {
        write("Minotaurs aren't accepted in the gentleman's club.\n"+
              "Your application has been denied!\n");
        return 1;
    }

    /* Verify if player is not Dancer of the veils. */
    if (this_player()->query_prop("_live_i_am_dancer_of_veils"))
    {
        write("No self respecting lady would be a dancer.\n"+
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
    write("Your membership has been accepted! A young female "+
          "hands you a pleated charmeuse hat.\n"+
          "Welcome to the Ladies club!\n"+
          "Please type <lchelp>.\n");

    write_file("/d/Raumdor/guilds/lc/log/membership",
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

    write_file("/d/Raumdor/guilds/lc/log/membership",
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
    write("Your application to leave the Ladies club has "+
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

    if ((str == "candle") || (str == "candles") || (str == "scented candle") || (str == "scented candles"))
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
