
#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit SOUL_DIR+"help";

#include <std.h>

#define VAMP_I_LAST_REMOVE  "_vamp_i_last_remove"

public void create()
{
    set_help_type(({ "cm", "covenmaster" }));
    read_help_dir(HELP_DIR,"cmhelp");
}

string *
replace_soul()
{
    object ob = previous_object();

    if (!ob || !OCC_MANAGER->is_covenmaster(ob))
    {
        return ({});
    }

    return 0;
}

string get_soul_id() { return OCC_GUILD_NAME + " covenmaster"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
    return ([
                "vtitles" : "vtitles",
                "bgtitles" : "bgtitles",
                "bghonour" : "bghonour",
                "bghonor"  : "bghonour",
                "vhonour" : "vhonour",
                "vhonor"  : "vhonour",
                "cmcreate" : "cmcreate",
                "cmremove" : "cmremove",
            ]) + help_cmdlist();
}


int
do_titles(string str,object manager)
{
    string *titles, cmtitle = "", s, title;
    int i, level;

    setuid();
    seteuid(getuid());

    if (str == "clear")
    {
        manager->set_guild_titles(({}));
        do_titles("",manager);
    
        users()->update_title();
        return 1;
    }
    
    if (str == "factor")
    {
        write("Current factor: " + 
            manager->query_max_level() + "\n");
        return 1;
    }

    if (strlen(str) && sscanf(str, "factor %d", level))
    {
        if (level < 1)
	{
            write("The factor must be positive.\n");
            return 1;
	}

        manager->set_max_level(level);
        do_titles("factor",manager);

        users()->update_title();

        return 1;
    }

    titles = manager->query_guild_titles();

    if (!pointerp(titles))
    {
        titles = ({});
    }
    else if (sizeof(titles))
    {
        cmtitle = titles[0];
        titles = (sizeof(titles) > 1 ? titles[1..] : ({}));
    }

    if (!strlen(str))
    {
        for (i = 0; i < sizeof(titles); i++)
        {
            write(sprintf("%2d. %s\n", i + 1, titles[i]));
        }

        if (strlen(cmtitle))
        {
            write("Covenmaster: " + cmtitle + "\n");
        }
        else if (i == 0)
        {
            write("No titles.\n");
        }

        return 1;
    }

    if (sscanf(str, "add %s", s))
    {
        if (sscanf(s, "%d %s", level, title) != 2)
        {
            if (sscanf(s, "covenmaster %s", title) != 1)
            {
                /* Default to giving a title for the next level */ 
                titles += ({ s });
            }
            else
            {
                /* The covenmaster title is being defined */ 
                cmtitle = title;
            }
        }
        else
        {
            /* Add a title for a specific level */
 
            if ((--level < 0) || (level > sizeof(titles)))
            {
                notify_fail("Not that many levels.\n");
                return 0;
            }

            if (level == sizeof(titles))
            {
                titles += ({ title });
            }
            else if (level == 0)
            {
                titles = ({ title }) + titles;
	    }
            else
            {
                titles = titles[..(level - 1)] + ({ title }) + titles[level..];
            }
        }
    }
    else if (sscanf(str, "remove %s", s))
    {
        if (sscanf(s, "%d", level) != 1)
        {
            if (s != "covenmaster")
            {
                return 0;
            }

            cmtitle = "";
        }
        else
        {
            if ((--level < 0) || (level >= sizeof(titles)))
            {
                notify_fail("Not that many levels.\n");
                return 0;
            }

            titles = exclude_array(titles, level, level);
        }
    }

    setuid();
    seteuid(getuid());
    manager->set_guild_titles(({ cmtitle }) + titles);
    do_titles("",manager);

    users()->update_title();

    return 1;
}

int
honour(string str,object manager)
{
    string name, title, titles, *members;
    object who;
    int i;


    if (!strlen(str))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (str == "display")
    {
        manager->set_ptitles_shown(1);
        write("Ok.\n");
        return 1;
    }

    if (str == "no display")
    {
        manager->set_ptitles_shown(0);
        write("Ok.\n");
        return 1;
    }
  
    if (sscanf(str, "add %s %s", name, title) == 2)
    {
        name = lower_case(name);
        if (!manager->load_data(name))
        {
	        notify_fail("Could not give " + capitalize(name) + " an " +
		    "honourary title.  Perhaps that person is not a member.\n");
	        return 0;
	    }
    	if (!manager->add_personal_title(name, title))
    	{
	        notify_fail("Could not give " + capitalize(name) + " an " +
		    "honourary title.  Perhaps that person is not a member.\n");
	        return 0;
	    }
	    write("You give " +capitalize(name) + " the honorary title of '"+
	    title + "'.\n");
        if (who = find_player(name))
        {
            who->update_title();
        }
	    return 1;
	}
    if (sscanf(str, "remove %s", name) == 1)
    {
        name = lower_case(name);
        if (!manager->load_data(name))
        {
            notify_fail("Could not remove " + capitalize(name) +
                "'s honourary title.  Perhaps that person is not a member.\n");
            return 0;
        }
        if (!manager->remove_personal_title(name))
        {
            notify_fail("Could not remove " + capitalize(name) +
                "'s honourary title.  Perhaps that person is not a member.\n");
            return 0;
        }
	    write("You remove the honrary title of " +capitalize(name) + 
	    ".\n");
        if (who = find_player(name))
        {
            who->update_title();
        }
	    return 1;
    }
    if (sscanf(str, "list %s", name) == 1)
    {
        name = lower_case(name);
        title = manager->query_personal_title(name);
        write (strlen(title) ? title + "\n" : "None\n");
        return 1;
    }

    if (str != "list")
    {
        return 0;
    }

    titles = "";
    members = manager->query_all_guild_members();
    for (i = 0; i < sizeof(members); i++)
    {
        if (!SECURITY->query_wiz_level(members[i]) &&
            !wildmatch("*jr", members[i]) &&
            strlen(title = 
            manager->query_personal_title(members[i])))
        {
            titles += sprintf("%-13s %s\n", 
                capitalize(members[i]) + ":", title);
		}
    }
    write(strlen(titles) ? titles : "No honourary titles.\n");
    return 1;

}

int
cmcreate(string str)
{
    if (!strlen(str))
    {
        notify_fail("Usage: cmcreate <name>.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (!OCC_MANAGER->load_data(str))
    {
         write(capitalize(str) + " is not a member of your coven.\n");
         return 1;
    }

    if (!OCC_MANAGER->set_covenmaster(str))
    {
        notify_fail("Could not designate " + capitalize(str) +
            " as covenmaster.\n");
        return 0;
    }

    users()->update_vamp_souls();

    write("Ok.\n");
    return 1;
}

int bghonour(string str)
{
    notify_fail("Usage: bghonour add     <name> <title>\n" +
                "                remove  <name>\n" +
                "                list   [<name>]\n" +
                "                display\n" +
                "                no display\n");
    return honour(str,LAY_MANAGER);
}

int vhonour(string str)
{
    notify_fail("Usage:  vhonour add     <name> <title>\n" +
                "                remove  <name>\n" +
                "                list   [<name>]\n" +
                "                display\n" +
                "                no display\n");
    return honour(str,OCC_MANAGER);
}

int vtitles(string str)
{
    notify_fail("Usage:  vtitles add [<level> | covenmaster] <title>\n" +
                "                remove <level> | covenmaster\n" +
                "                factor [<factor>]\n");

    return do_titles(str,OCC_MANAGER);
}

int bgtitles(string str)
{
    notify_fail("Usage: bgtitles add [<level>] <title>\n" +
                "                remove <level>\n" +
                "                factor [<factor>]\n");

    return do_titles(str,LAY_MANAGER);
}

int cmremove(string str)
{
    notify_fail("Remove which Bloodguard from the Coven?\n");
    
    setuid();
    seteuid(getuid());
    if (!str)
    {
        return 0;
    }
    
    object player=find_player(str);
    if (!player)
    {
        return 0;
    }
    if (player->query_wiz_level())
    {
        return 0;
    }
    if (!IS_BG(player))
    {
        return 0;
    } 
    object statue=find_object(NPC_DIR+"statue");
    if (!statue)
    {
        write("You cannot sense the Eldest.\n");
        return 1;
    } 
    statue=object_clones(statue)[0];
    if (!statue)
    {
        write("You cannot sense the Eldest.\n");
        return 1;
    } 

    if (TP->query_prop(VAMP_I_LAST_REMOVE)!=str)
    {
        TP->add_prop(VAMP_I_LAST_REMOVE,str);
        write("Are you certain you wish to remove "+
        CAP(str)+"? Repeat your command to confirm.\n");
        return 1;
    }        

    write_file(BG_JOIN_LOG,ctime(time())+ ":  "+
        TP->query_real_name()+ " has removed "+
        CAP(str)+ "from the Bloodguards.\n");
    player->catch_msg("A thought passes through your mind: "+
        "You have broken your oath, and not shown your loyalty "+
        "to the Coven as you had promised me.\n");
    player->set_hp(0);
    player->remove_bloodguard(0);
    player->do_die(statue);
    TP->catch_msg("A thought passes through your mind: So be it.\n");
    return 1;
}




