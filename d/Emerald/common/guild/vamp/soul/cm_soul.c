inherit "/cmd/std/command_driver";
inherit "/d/Emerald/common/guild/vamp/lib/help";

#include "../guild.h"

void
catch_accept_response(int resp, object asker, object responder, string coven);

void
create()
{
    read_help_dir(VAMP_HELP_DIR, "cmhelp");
    set_help_type(({ "covenmaster", "cm" }));
}

string *
replace_soul()
{
    object ob = previous_object();

    if (!ob || !ob->query_vamp_covenmaster())
    {
        return ({});
    }

    return 0;
}

string get_soul_id() { return GUILD_NAME + " covenmaster"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
    return ([
                "cmaccept" : "cmaccept",
                //"cmbanish" : "cmbanish",
                "cmtitles" : "cmtitles",
                "cmhonour" : "cmhonour",
                "cmhonor"  : "cmhonour",
                "cmcreate" : "cmcreate",
                "cmlair"   : "cmlair",          
            ]) + help_cmdlist();
}

int
cmaccept(string str)
{
    object *oblist;
    string coven;
    object yn_ob;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Usage: " + query_verb() + "\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Please be more specific.\n");
        return 0;
    }

    coven = this_player()->query_vamp_coven();

    if (oblist[0]->query_vamp_coven() == coven)
    {
        write(oblist[0]->query_The_name(this_player()) + " is already " +
            "a member of your coven.\n");
        return 1;
    }

    if (oblist[0]->query_vamp_coven() != ROGUE_VAMPIRE)
    {
        write(oblist[0]->query_The_name(this_player()) + " is already " +
            "a member of another coven.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(oblist[0],
            &catch_accept_response(, this_player(), oblist[0], coven), 20.0))
		{
            // something failed in yn_ob...remove it.
            write("For some strange reason, you are unable to bring " +
                "yourself to ask " + oblist[0]->query_the_name(this_player()) +
                "to join.\n");
            yn_ob->remove_object();
        }
        else
		{
    	    write("You ask " + oblist[0]->query_the_name(this_player()) +
    		" if " + oblist[0]->query_pronoun() + " will join your coven.\n");
    	    oblist[0]->catch_tell(this_player()->query_The_name(oblist[0]) +
    		" has accepted you into " + this_player()->query_pronoun() +
    		" coven.  Do you wish to join? (Yes/No)\n");
		}
    }

    return 1;
}

void
catch_accept_response(int resp, object asker, object responder, string coven)
{
    if (!responder)
    {
        return;
    }

    if (resp == 0)
    {
        asker->catch_tell(responder->query_The_name(asker) +
            " denied you.\n");
        responder->catch_tell("Ok.\n");
        return;
    }

    if (resp < 0)
    {
        asker->catch_tell(responder->query_The_name(asker) +
            " failed to respond.\n");
        responder->catch_tell("No response.  Please try again if you wish to " +
            "continue.\n");
        return;
    }

    asker->catch_tell(responder->query_The_name(asker) +
        " joined your coven.\n");
    responder->catch_tell("Ok.\n");

    responder->set_vamp_coven(coven);
}

int
cmbanish(string str)
{
    object who;

    if (!strlen(str))
    {
        notify_fail("Usage: " + query_verb() + "\n");
        return 0;
    }

    str = lower_case(str);

    setuid();
    seteuid(getuid());

    if (this_player()->query_vamp_coven() != MANAGER->query_coven(str))
    {
        write(capitalize(str) + " is not a member of your coven.\n");
        return 1;
    }

    if (who = find_player(str))
    {
        who->set_vamp_coven(ROGUE_VAMPIRE);
        who->catch_tell("You have been banished from your coven.\n");
        write("Ok.\n");
        return 1;
    }

    if (MANAGER->query_punished(str, BANISH))
    {
        write(capitalize(str) + " is already banished.\n");
        return 1;
    }

    
    MANAGER->add_punishment(str, BANISH);
    write("Ok.\n");
    
    return 1;
}

int
cmtitles(string str)
{
    string *titles, cmtitle = "", s, title;
    int i, level;

    setuid();
    seteuid(getuid());

    if (str == "clear")
    {
        MANAGER->set_guild_titles(this_player()->query_vamp_coven(), ({}));
        cmtitles("");
    
        VAMPS(users())->update_title();
        return 1;
    }
    
    if (str == "factor")
    {
        write("Current factor: " + 
            MANAGER->query_max_level(this_player()->query_vamp_coven()) + "\n");
        return 1;
    }

    if (strlen(str) && sscanf(str, "factor %d", level))
    {
        if (level < 1)
	{
            write("The factor must be positive.\n");
            return 1;
	}

        MANAGER->set_max_level(this_player()->query_vamp_coven(), level);
        cmtitles("factor");

        VAMPS(users())->update_title();

        return 1;
    }

    titles = MANAGER->query_guild_titles(this_player()->query_vamp_coven());

    notify_fail("Usage: cmtitles add [<level> | covenmaster] <title>\n" +
                "                remove <level> | covenmaster\n" +
                "                factor [<factor>]\n");

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
    MANAGER->set_guild_titles(this_player()->query_vamp_coven(), ({ cmtitle }) + titles);
    cmtitles("");

    VAMPS(users())->update_title();

    return 1;
}

int
cmhonour(string str)
{
    string name, title, titles, *members, coven;
    object who;
    int i;

    notify_fail("Usage: cmhonour add     <name> <title>\n" +
                "                remove  <name>\n" +
                "                list   [<name>]\n" +
                "                display\n" +
                "                no display\n");

    if (!strlen(str))
    {
        return 0;
    }

    coven = this_player()->query_vamp_coven();

    setuid();
    seteuid(getuid());

    if (str == "display")
    {
        MANAGER->set_ptitles_shown(coven, 1);
        write("Ok.\n");
        return 1;
    }

    if (str == "no display")
    {
        MANAGER->set_ptitles_shown(coven, 0);
        write("Ok.\n");
        return 1;
    }
  
    if (sscanf(str, "add %s %s", name, title) != 2)
    {
        if (sscanf(str, "remove %s", name) != 1)
        {
            if (sscanf(str, "list %s", name) != 1)
            {
                if (str != "list")
                {
                    return 0;
                }

                titles = "";
                members = MANAGER->query_all_coven_members(coven);
                for (i = 0; i < sizeof(members); i++)
                {
                    if (!SECURITY->query_wiz_level(members[i]) &&
                        !wildmatch("*jr", members[i]) &&
                        strlen(title = 
                        MANAGER->query_personal_title(members[i])))
                    {
                        titles += sprintf("%-13s %s\n", 
                            capitalize(members[i]) + ":", title);
		    }
                }
               
                write(strlen(titles) ? titles : "No honourary titles.\n");
                return 1;
            }

            if (coven != MANAGER->query_coven(name))
	    {
                write(capitalize(name) + " is not a member of your coven.\n");
                return 1;
	    }

            title = MANAGER->query_personal_title(name);
            write (strlen(title) ? title + "\n" : "None\n");
            return 1;
        }

        name = lower_case(name);

        if (coven != MANAGER->query_coven(name))
	{
            write(capitalize(name) + " is not a member of your coven.\n");
            return 1;
	}

        if (!MANAGER->remove_personal_title(name))
        {
            notify_fail("Could not remove " + capitalize(name) +
                "'s honourary title.  Perhaps that person is not a member.\n");
            return 0;
        }
    }
    else
    {
        if (coven != MANAGER->query_coven(name))
	{
            write(capitalize(name) + " is not a member of your coven.\n");
            return 1;
	}

	if (!MANAGER->add_personal_title(name, title))
	{
	    notify_fail("Could not give " + capitalize(name) + " an " +
		"honourary title.  Perhaps that person is not a member.\n");
	    return 0;
	}
    }

    write("Ok.\n");
    
    if (who = find_player(name))
    {
        who->update_title();
    }

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

    if (MANAGER->query_coven(str) != this_player()->query_vamp_coven())
    {
         write(capitalize(str) + " is not a member of your coven.\n");
         return 1;
    }

    if (!MANAGER->set_covenmaster(str))
    {
        notify_fail("Could not designate " + capitalize(str) +
            " as covenmaster.\n");
        return 0;
    }

    users()->update_covenmaster_status();

    write("Ok.\n");
    return 1;
}

int
cmlair(string str)
{
    object env;
    string coven, lair;

    if (!strlen(str))
    {
        lair = LAIR_MANAGER->query_lair(this_player()->query_vamp_coven());

        if (!strlen(lair) || LOAD_ERR(lair) || !find_object(lair))
	{
            write("Could not determine current lair.\n");
            return 1;
	}

        write("Current lair: " + lair->short() + " (" + lair->query_domain() +
            " Domain)\n");
        return 1;
    }

    if (str != "here")
    {
        notify_fail("Usage: cmlair [here].\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (!(env = environment(this_player()))->query_vamp_lair() ||
        ((coven = LAIR_MANAGER->query_coven(file_name(env))) &&
        coven != this_player()->query_vamp_coven()))
    {
        write("It is not possible to lair here.\n");
        return 1;
    }

    LAIR_MANAGER->set_lair(this_player()->query_vamp_coven(), file_name(env));
    
    write("Ok.\n");
    return 1;
}
