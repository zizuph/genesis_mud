/**********************************************************************
 * - family                                                         - *
 * - Where members of the Thanar race guild can join a Coven.       - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/
#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#include "../guild.h"

inherit GUILD_ROOM;
inherit SCROLL;
string
query_plaque(void)
{
    return("\n\t _______________________________________________________\n"+
     "\t/ \\                                                     \\\n"+
     "\t\\_/_____________________________________________________/\n"+
     "\t|                                                       |\n"+
     "\t|                                                       |\n"+
     "\t|                    Thanar Covens                      |\n"+
     "\t|                                                       |\n"+
     "\t|  list covens         = To list the Covens of Thanar.  |\n"+
     "\t|  list <coven name>   = To list members of a Coven.    |\n"+
     "\t|  choose <coven name> = To join a coven.               |\n"+
     "\t|  leave coven         = To leave your present Coven.   |\n"+
     "\t|  list                = List current guilds you are    |\n"+
     "\t|                      = affiliated with.               |\n"+
     "\t|                                                       |\n"+
     "\t|_______________________________________________________|\n"+
     "\t/ \\                                                     \\\n"+
     "\t\\_/_____________________________________________________/\n"+
     "\n"); 
}

public void
create_guild_room()
{
    setuid(); seteuid(getuid());

    set_short("Upper Vestibule");
    set_long("    This is the upper vestibule. It is just as "+
      "grand as the lower vestibule and is constructed with "+
      "the same marvelous marble. There are six war banners "+
      "that hang upon the walls each denoting a given Coven "+
      "of Thanar. A large marble table is erected in the "+
      "center of the room with a golden plaque placed upon "+
      "its surface.\n");
    add_item(({ "vestibule", "room", "area", "chamber"}), query_long);
    add_cmd_item("plaque", "read", query_plaque);

    add_item(({"war banners", "banners"}),
      "The war banners are large and elaborately crafted by "+
      "skilled hands. Sturdy threads are woven in various "+
      "patterns in each. There are six war banners in total and "+
      "you should be able to examine each one a bit closer.\n");
    add_item(({"banner"}),
      "Which banner did you want to look at? The first one perhaps?\n");
    add_item(({"first banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of onyx and "+
      "silver. He is holding up a short blade in victory. "+
      "At the top right corner written in blood is the word 'Blade'.\n");
    add_item(({"second banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of saphire and "+
      "silver. He has his arms outstretched calling to nature in victory. "+
      "At the top right corner written in blood is the word 'Elemin'.\n");
    add_item(({"third banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of ruby and "+
      "gold. He is standing in victory over a pit of fire. "+
      "At the top right corner written in blood is the word 'Flame'.\n");
    add_item(({"fourth banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of onyx and "+
      "gold. He is holding up a battle claw in victory. "+
      "At the top right corner written in blood is the word 'Goth'.\n");
    add_item(({"fifth banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of saphire and "+
      "gold. He is surounded by a bloodied battlefield but stand victorious. "+
      "At the top right corner written in blood is the word 'Hellstone'.\n");
    add_item(({"sixth banner"}),
      "This banner is faintly worn although the workmanship "+
      "has been elaborately done. There is an image depicted "+
      "of a human warrior wearing the colours of emerald and "+
      "silver. He is holding up a staff and casting a spell in victory. "+
      "At the top right corner written in blood is the word 'Magi'.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
  
    add_exit("join", "down");
      
}

/*
 * List the available covens, for convenience.
 */
public int
list(string str)
{
    if (!strlen(str))
    {
	if (str = this_player()->list_major_guilds())
	    write("You are a member of the following guilds.\n" + str);
	else
	    write("You are not a member of any important guilds.\n");
	return 1;
    }

    str = capitalize(lower_case(str));

    if (lower_case(str) == "covens")
    {
	return print_scroll(sort_array(m_indexes(COVENS)),
	    "These are the available covens of the " + GUILD_NAME);
    }

    if (member_array(str, m_indexes(COVENS)) == -1)
    {
	write("That is not a Coven of the " + GUILD_NAME + ".\n");
	return 1;
    }
    else
    {
        int i;
        string *lst;
	mixed tmp = ([]) + SERVER->query_coven(str);

	tmp = m_indexes(tmp) - ({ COVEN_CLRS });

        i = sizeof(tmp);
        lst = ({});
        
        while(--i >= 0)
        {
            if(!wildmatch("*jr", tmp[i]) &&
               !SECURITY->query_wiz_level(tmp[i]))
                   lst += ({tmp[i]});
        }
        
	if (!sizeof(lst))
	{
	    write("The Coven " + str + " is currently empty and in " +
		"need of a claimant.\n");
	    return 1;
	}

	lst = sort_array(map(lst, capitalize));
	return print_scroll(lst, "The following " + GUILD_NAME +
	    " belong to the Coven " + str);
    }
}

public int
choose_coven(string str)
{
    string *tmp, name;

    /* Not a member, go away. */
    if (!IS_MEMBER(this_player()))
    {
	return 0;
    }

    /* Input would be helpful. */
    if (!strlen(str))
    {
	notify_fail("Choose what? A coven maybe?\n");
	return 0;
    }

    name = this_player()->query_real_name();

    /* Stoopid goblinie, your already in a coven. */
    if (SERVER->query_coven(name))
    {
	write("You already belong to a coven.\n");
	return 1;
    }

//    str = capitalize(lower_case(str));

    /* Are we asking to join a real coven? */
    tmp = SERVER->query_coven("all");
    if (member_array(str, tmp) == -1)
    {
	write("No such coven exists, try again.\n");
	return 1;
    }

    /* Rut-roh! An error.. ickyness */
    if (!SERVER->add_to_coven(name, str, name))
    {
	write("An error has prevented you from claiming " +
	  "that coven, please make a bug report.\n");
	return 1;
    }

    write("You choose the Coven " + str + " as your own.\n");
    say(QCTNAME(this_player()) + " has chosen the Coven " +
      str + " as " + this_player()->query_possessive() +" own.\n");


    write_file(LOG + "members",
               ctime(time()) + " " +
               capitalize(this_player()->query_real_name()) +
               " (age = " + (this_player()->query_age() / 43200) +
               ", avg = " + this_player()->query_average_stat() +
               ") joined coven " + str + ".\n");

    return 1;
}


/*
 * Leave a coven.
 */
public int
leave_coven(string str)
{
    string coven, name = this_player()->query_real_name();

    if (!IS_MEMBER(this_player()) || !(coven = SERVER->query_coven(name)))
    {
	return 0;
    }

    str = lower_case(str);

    if (str != "my coven" && str != "coven" &&
        str != lower_case("coven " + coven))
    {
	return notify_fail("Leave what, your Coven?");
    }

    if (!SERVER->remove_from_coven(name, name))
    {
	write("An error occured preventing your leaving.\n" +
	    "Please make a bug report.\n");
	return 1;
    }

    write("You leave the Coven " + coven + " and turn in your " +
	"badge for your old one.\n");
    say(QCTNAME(this_player()) + " has left the Coven " + coven + ".\n");

    /* reinitialize colours of the badge */
    present(OBJECT_ID, this_player())->init();

    write_file(LOG + "members",
               ctime(time()) + " " +
               capitalize(this_player()->query_real_name()) +
               " (age = " + (this_player()->query_age() / 43200) +
               ", avg = " + this_player()->query_average_stat() +
               ") left coven " + coven + ".\n");

    return 1;
}

/*
 * Give us some commands.
 */
public void
init()
{
    ::init();
    add_action(list, "list");
    add_action(leave_coven, "leave");
    add_action(choose_coven, "choose");

}
