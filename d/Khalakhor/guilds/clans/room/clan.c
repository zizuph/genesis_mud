/**********************************************************************
 * - clan.c                                                         - *
 * - Clan Join Clan room                                            - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/

#pragma strict_types

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "../guild.h"

inherit GUILD_ROOM;
inherit SCROLL;

#include "seated2.c"
#include "fireplace.c"

string
read_scroll(void)
{
    return(
    //"list clans         = To list the Clans of Clan.\n"+
    "list clans         = To list the Clans of Khalakhor.\n"+
    "list <clan name>   = To list members of a Clan.\n"+
    "choose <clan name> = To join a clan.\n"+
    "request tunic      = To obtain a new tunic.\n"+
    "leave clan         = To leave your present Clan.\n"+
    "list               = List current guilds you are affiliated "+
    "with.\n\n"+
    "Notation: First claimant to a Clan may <idea tunic> suggest "+
    "two colours for their tunic for approval.\n");
}
static public string *garland;
static mapping select = ([ "MAX":0 ]);

nomask static int
select_banner(string str)
{
    string verb = query_verb(), name;
    object ob;
    if ((str != "banner"))
    {
        notify_fail("Select what? A banner maybe?\n");
        return 0;
    }
    /* Are there any left to pick? */
    if (select["MAX"] >= BANNER_LIMIT[1])
    {
        write(BANNER_LIMIT[1]);
        return 1;
    }
    
    /* See if we select too many already */
    name = this_player()->query_name();
    if (select[name] >= BANNER_LIMIT[0])
    {
        write(BANNER_LIMIT[2]);
        return 1;
    }
    setuid();
    seteuid(getuid());
    clone_object(GOBJ + "banner")->move(TP, 1);
    write("You look over the banners along the wall and select "+
    "one.\n");
    say(this_player()->query_name() + " looks over the banners along "+
    "wall and selects one.\n");
    
    /* Adjust the limits */
    select["MAX"]++;
    select[name]++;
    return 1;
}
/*
 * The room itself.
 */
public void
create_guild_room()
{
    setuid(); seteuid(getuid());
    set_short("Hall of Clans");
    set_long("   The enormity of this hall is breathtaking with "+
    "immense banners adorning the glistening grey stonewalls. "+
    "Various coats of arms are displayed in no set preference "+
    "along the northern wall with a massive fireplace in the "+
    "center. The western wall is aligned with banners of every "+
    "shape and size indicating this is the Hall of Clans. Within "+
    "the center of this wall is a scroll. ");
    
    add_item(({"coat of arms", "coat of arm"}),
    "The coat of arms displayed are of all the clans of Khalakhor. "+
    "They range from crossed swords to axes to vessels and even a "+
    "few have large oak trees and animals.\n");
    
    
    add_item(({"scroll"}),
    "The scroll is reads:\n"+
    "@@read_scroll@@");
    add_cmd_item("scroll", "read", read_scroll);
    add_item(({"banner", "banners"}),
    "There are banners along the wall that may be selected for "+
    "use.\n");
    
    add_item(({"fire"}),
    "The fire dances with golden light which fills the hall with "+
    "warmth and peace.\n");
    add_item(({"fireplace"}),
    "The fireplace is quite large with a holder placed on one side "+
    "with tools to stoke the fire and logs on the otherside to "+
    "place on the fire.\n");
    add_item(({"tool", "tools", "poker", "fireplace poker"}),
    "There are tools in a holder next to the fireplace so one can "+
    "stoke the fire.\n");
    add_item(({"log", "logs", "stack"}),
    "Logs for the fire are piled in a neat stack next to the "+
    "fireplace.\n");
    add_item(({"north", "northeast", "northwest", "west"}),
    "There is a wall in that direction.\n");
    add_item(({"east"}),
    "An archway leading to the commons area is in that direction.\n");
    add_item(({"south"}),
    "An archway leading the the sleeping area is in that "+
    "direction.\n");
    
    add_item(({"hall", "grand hall", "room", "area"}),
    "The enormity of this hall is breathtaking with "+
    "immense banners adorning the glistening grey stonewalls. "+
    "Various coats of arms are displayed in no set preference "+
    "along the northern wall with a massive fireplace in the "+
    "center. The western wall is aligned with banners of every "+
    "shape and size indicating this is the Hall of Clans. Within "+
    "the center of this wall is a scroll.\n");
    add_item(({"chair","chairs"}), seat_desc);
    add_my_desc(seat_desc, this_object());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    
    add_exit("cboard", "east");
    add_exit("start", "south");

    add_fail("auto", "You walked into a wall!\n"+
    "Ouch! That's gotta hurt!\n");

}

/*
 * List the available clans, for convenience.
 */
 
public int
list(string str)
{
    string full_name;
    //full_name = str;
    if (!strlen(str))
    {
        if (str = this_player()->list_major_guilds())
        write("You are a member of the following guilds.\n" + str);
        else
        write("You are not a member of any important guilds.\n");
        return 1;
    }
    //str = capitalize(lower_case(str));
    if (lower_case(str) == "clans")
    {
        return print_scroll(sort_array(m_indexes(CLANS)),
        "These are the available Celtic Clans within Khalakhor");
    }
    // Once again, no.
    //if (!member_array(str, m_indexes(CLANS)))
    // Why does it use different methods of getting a clan list?
    foreach (string clan : m_indexes(CLANS))
    {
        if (lower_case(clan) == lower_case(str))
        {
            full_name = clan;
            break;
        }
    }
    if (!full_name)
    {
        write("That is not a Clan of Khalakhor.\n");
        return 1;
    }
    else
    {
        int i;
        string *lst;
        // mixed tmp = ([]) + SERVER->query_clan(str);
        mixed tmp = ([]) + SERVER->query_clan(full_name);
        tmp = m_indexes(tmp) - ({ CLAN_CLRS });
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
            write("The Clan " + full_name + " is "+
            "currently empty and in need of a claimant.\n");
            return 1;
        }
        lst = sort_array(map(lst, capitalize));
        return print_scroll(lst, "The following Celts "+
        "belong to the " + full_name);
        }
}

/*
 * Request tunic
 */
public int
request(string str)
{
    object tunic;
    if (str != "tunic")
    {
        NF("Request what? A tunic maybe?\n");
        return 0;
    }
    if (!IS_MEMBER(TP))
    {
        write("The " + GUILD_NAME + " do not grant requests to "+
        "non-members.\n");
        return 1;
    }
    if (objectp(tunic = present(OBJECT_ID, TP)) &&
    (!tunic->query_prop(OBJ_I_BROKEN)))
    {
        write("You don't need another tunic.\n");
        return 1;
    }
    if (tunic)
    tunic->remove_object();
    clone_object(OBJECT)->move(TP, 1);
    write("A young lad enters, hands you a new tunic, then "+
    "departs.\n");
    say (QCTNAME(TP) + " is given a new tunic by a young lad.\n");
    return 1;
}

public int
choose_clan(string str)
{
    string *tmp, name, full_name;
    //full_name = str;

    /* Not a member, go away. */
    
    if (!IS_MEMBER(this_player()))
    {
        return 0;
    }
    /* Input would be helpful. */
    if (!strlen(str))
    {
        notify_fail("Choose what? A clan maybe?\n");
        return 0;
    }
    name = this_player()->query_real_name();
    
    if (SERVER->query_clan(name))
    {
        write("You already belong to a clan.\n");
        return 1;
    }
    // This will never work correctly!      Lavellan, 2011/02/25
    //str = capitalize(lower_case(str));
    
    /* Are we asking to join a real clan? */
    tmp = SERVER->query_clan("all");
    foreach (string clan : tmp)
    {
        if (lower_case(clan) == lower_case(str))
        {
            full_name = clan;
            break;
        }
    }
    //if (!member_array(str, tmp))
    if (!full_name)
    {
        write("No such clan exists, try again.\n");
        return 1;
    }
    /* Rut-roh! An error.. ickyness */
    if (!SERVER->add_to_clan(name, full_name, name))
    {
        write("An error has prevented you from claiming "+
        "that clan, please make a bug report.\n");
        return 1;
    }
    write("You choose " + full_name + " as your own.\n" +
    "A servant of the Clans fetches your new tunic " +
    "and places it upon your shoulders, taking the old " +
    "one away with him.\n");
    say(QCTNAME(this_player()) + " has chosen the Clan " +
    full_name + " as " + HIS(TP) +" own.\n");
    
    /* In case we don't have one */
    if (!present(OBJECT_ID, this_player()))
    {
        clone_object(OBJECT)->move(this_player());
    }
    /* This resets the player's tunic with clan colours */
    present(OBJECT_ID, this_player())->init();
    write_file(LOG + "members",
    ctime(time()) + " " +
    capitalize(this_player()->query_real_name()) +
    " (age = " + (this_player()->query_age() / 43200) +
    ", avg = " + this_player()->query_average_stat() + 
    ") joined clan " + str + ".\n");
    return 1;
}


/*
 * Leave a clan.
 */
 
public int
leave_clan(string str)
{
    string clan, name = this_player()->query_real_name();
    if (!IS_MEMBER(this_player()) || !(clan = SERVER->query_clan(name)))
    {
        return 0;
    }
    str = lower_case(str);
    if (str != "my clan" && str != "clan" &&
        str != lower_case("clan " + clan))
        {
        return notify_fail("Leave what, your Clan?");
    }
    if (!SERVER->remove_from_clan(name, name))
    {
        write("An error occured preventing your leaving.\n" +
        "Please make a bug report.\n");
        return 1;
    }
    write("You leave " + clan + " and turn in your "+
    "tunic for your old one.\n");
    say(QCTNAME(this_player()) + " has left the " + clan + ".\n");
    /* reinitialize colours of the tunic */
    present(OBJECT_ID, this_player())->init();
    write_file(LOG + "members",
    ctime(time()) + " " +
    capitalize(this_player()->query_real_name()) +
    " (age = " + (this_player()->query_age() / 43200) +
    ", avg = " + this_player()->query_average_stat() +
    ") left clan " + clan + ".\n");
    return 1;
}

/*
 * Give us some commands.
 */
 
public void
init()
{
    ::init();
    init_seat();
    init_fire();
    add_action(list, "list");
    add_action(request, "request");
    add_action(leave_clan, "leave");
    add_action(choose_clan, "choose");
    add_action(select_banner, "select");
}
