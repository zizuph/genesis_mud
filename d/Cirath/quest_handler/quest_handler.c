#pragma strict_types
#pragma no_clone
#pragma no_shadow

inherit "/std/room";

#include "quest_handler.h"

#include <std.h>
#include <stdproperties.h>
#include <filepath.h>


#define GROUP 0
#define BIT   1
#define XP    2
#define DEACT 3
#define DESC  4

static private mapping quest_info = ([]);

string usage()
{
    return "- quest add\n" +
           "    Add a quest to the quest handler.\n" +
           "- quest remove\n" +
           "    Remove a quest from the quest handler.\n" +
           "- quest activate\n" +
           "    Activate a deactivated quest.\n" +
           "- quest deactivate\n" +
           "    Deactivate a quest.  Quest information will be\n" +
           "    retained, but quest bits will not be set by\n" +
           "    the quest handler.\n" +
           "- quest list [-sort name | group | bit | exp]\n" +
           "    List the quests handled by the quest handler.\n" +
           "- quest log <quest name>\n" + 
           "    View the quest log of a given quest.\n" +
           "- quest stats [<quest name>]\n" +
           "    View statistics of a given quest.\n" +
           "- quest info <name> [<quest name>]\n" +
           "    View quest log entries for a particular player\n" +
           "    You may specify a particular quest to search;\n" +
           "    otherwise, all quests will be searched.\n" +
           "- quest tail <quest name>\n" +
           "    Tail the quest log of a given quest.\n" +
           "- quest save <quest name> <file name>\n" +
           "    Save the quest log of a give quest to a given file.\n";
}

void create_room()
{
    add_prop(ROOM_I_NO_CLEANUP, 1);

    set_long(usage());

    quest_info = restore_map(QH_SAVE_FILENAME);
}

void save()
{
    save_map(quest_info, QH_SAVE_FILENAME);
}

mapping query_quest_info()
{
    return quest_info + ([]);
}

static nomask int admin_check(object who)
{
#ifdef NO_ADMIN_CHECK
    return 1;
#else
    int rank = SECURITY->query_wiz_rank(this_player()->query_real_name());

    return ((rank >= WIZ_ARCH) ||
            ((rank >= WIZ_STEWARD) &&
            SECURITY->query_wiz_dom(this_player()->query_real_name()) ==
            domain(this_object())));
#endif
}

int quest(string str)
{
    string *words;

    notify_fail(usage());

    if (!strlen(str) || !sizeof(words = explode(str, " ") - ({ "" })))
    {
        return 0;
    }

    return call_other(this_object(), "_quest_" + words[0], words[1..]);
}

static void quest_add_collect_desc(object who, string desc, mixed *info)
{
    string *quests;
    mixed *qinfo;
    int i;

    if (desc == "~q")
    {
        return;
    }

    set_this_player(who);

    quest_info[info[0]] = info[1..] + ({ 0, desc });
    save();
    write("Ok.\n");

    quests = (string *)m_indices(quest_info) - ({ info[0] });
    for (i = 0; i < sizeof(quests); i++)
    {
        if (pointerp(qinfo = quest_info[quests[i]]) &&
            (qinfo[GROUP] == info[1]) && (qinfo[BIT] == info[2]))
        {
            write("\nNB.  There is already at least " +
                "one other quest registered with this quest " +
                "bit.  Be sure that you have specified the " +
                "correct group and bit for this quest.\n");
            return;
        }
    }    
}
    
static void quest_add_collect_xp(object who, string xp, mixed *info)
{
    int i;

    if (xp == "~q")
    {
        return;
    }

    set_this_player(who);

    if (!sscanf(xp, "%d", i))
    {
        write("You must give an experience value. (~q to quit)\n: ");
    }
    else if (i < 0)
    {
        write("You must give an experience value greater than 0. " +
            "(~q to quit)\n: ");
    }
    else
    {
        write("Please give a short (one-line) description of the quest.\n: ");
        input_to(&quest_add_collect_desc(who, , info + ({ i })));
        return;
    }

    input_to(&quest_add_collect_xp(who, , info));
}

static void quest_add_collect_bit(object who, string bit, mixed *info)
{
    int i;

    if (bit == "~q")
    {
        return;
    }

    set_this_player(who);

    if (!sscanf(bit, "%d", i) || (i < 0) || (i > 19))
    {
        write("You must select a group from 0 to 19. (~q to quit)\n: ");
        input_to(&quest_add_collect_bit(who, , info));
        return;
    }

    write("Select an experience amount for this quest. (~q to quit)\n: ");
    input_to(&quest_add_collect_xp(who, , info + ({ i })));
}

static void quest_add_collect_group(object who, string group, mixed *info)
{
    int i;

    if (group == "~q")
    {
        return;
    }

    set_this_player(who);

    if (!sscanf(group, "%d", i) || (i < 0) || (i > 4))
    {
        write("You must select a group from 0 to 4. (~q to quit)\n: ");
        input_to(&quest_add_collect_group(who, , info));
        return;
    }

    write("Select a quest bit (0 - 19). (~q to quit)\n: ");
    input_to(&quest_add_collect_bit(who, , info + ({ i })));
}

static void quest_add_collect_name(object who, string name)
{
    if (name == "~q")
    {
        return;
    }

    set_this_player(who);

    if (!strlen(name))
    {    
        write("You must select a name. (~q to quit)\n: ");
    }
    else if (quest_info[name])
    {
        write("There is already a quest with that name.  Please select " +
            "another. (~q to quit)\n: ");
    }
    else
    {
        write("Select a quest group (0 - 4). (~q to quit)\n: ");
        input_to(&quest_add_collect_group(who, , ({ name })));
        return;
    }
        
    input_to(&quest_add_collect_name(who));
}

int _quest_add(string *args)
{
    if (sizeof(args))
    {
        return 0;
    }

   

    write("Please provide a name for this quest. (~q to quit)\n: ");
    input_to(&quest_add_collect_name(this_player()));
    return 1;
}

static void quest_remove_complete(string name)
{
    quest_info = m_delete(quest_info, name);
}

static void quest_remove_collect_name(object who, string name)
{
    if (name == "~q")
    {
        return;
    }

    set_this_player(who);

    if (!quest_info[name])
    {
        write("There is no quest registered with that name.  Please " +
            "select a valid quest name (~q to quit)\n: ");
    }
    else
    {
        quest_remove_complete(name);
        save();
        write("Ok.\n");
        return;
    }

    input_to(&quest_remove_collect_name(who));
}

int _quest_remove(string *args)
{
    if (sizeof(args))
    {
        return 0;
    }

    if (!admin_check(this_player()))
    {
        write("You do not have permission to do that.\n");
        return 1;
    }

    write("What is the name of the quest you wish to remove? (~q to quit) " +
        "\n: ");
    input_to(&quest_remove_collect_name(this_player()));
    return 1;
}

int _quest_activate(string *args)
{
    mixed *info;

    if (!sizeof(args))
    {
        return 0;
    }

    if (!admin_check(this_player()))
    {
        write("You do not have permission to do that.\n");
        return 1;
    }

    if (!pointerp(info = quest_info[args[0]]))
    {
        notify_fail("There is no such quest registered with that name.\n");
        return 0;
    }

    if (!info[DEACT])
    {
        write("That quest is not deactivated.\n");
    }
    else
    {
        info[DEACT] = 0;
        write("Ok.\n");
    }

    return 1;
}

int _quest_deactivate(string *args)
{
    mixed *info;

    if (!sizeof(args))
    {
        return 0;
    }

    if (!admin_check(this_player()))
    {
        write("You do not have permission to do that.\n");
        return 1;
    }

    if (!pointerp(info = quest_info[args[0]]))
    {
        notify_fail("There is no such quest registered with that name.\n");
        return 0;
    }

    info[DEACT] = 1;
    write("Ok.\n");

    return 1;
}

static int cmp(mixed val1, mixed val2, int index)
{
    mixed *info1 = quest_info[val1], *info2 = quest_info[val2];

    if (pointerp(info1))
    {
        val1 = info1[index];
    }
    else if (!pointerp(info2))
    {
        return 0;
    }
    else
    {
        return -1;
    }

    if (pointerp(info2))
    {
        val2 = info2[index];
    }
    else
    {
        return 1;
    }

    return ((val1 > val2) ? 1 : ((val1 == val2) ? 0 : -1));
}
    
int _quest_list(string *args)
{
    string *quests = m_indices(quest_info);
    mixed *info;
    int i;

    if (sizeof(args) > 1)
    {
        if (args[0] == "-sort")
        {
            switch (args[1])
            { 
                case "name":
                    quests = sort_array(quests);
                    break;
                case "bit":
                    quests = sort_array(quests, &cmp(, , BIT));
                    break;
                case "group":
                    quests = sort_array(quests, &cmp(, , GROUP));
                    break;
                case "xp":
                case "exp":
                    quests = sort_array(quests, &cmp(, , XP));
                    break;
                default:
                    return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    write("  Quest                             Group    Bit    Exp       \n" +
          "==============================================================\n");

    for (i = 0; i < sizeof(quests); i++)
    {
        if (!pointerp(info = quest_info[quests[i]]))
        {   
            continue;
        }

        write(sprintf("%s %-34s %2d      %2d     %-d\n", 
            (info[DEACT] ? "*" : " "), quests[i], info[GROUP],
             info[BIT], info[XP]));
    }

    write("\n* Deactivated quest\n");

    return 1;
}

int _quest_log(string *args)
{
    string log;

    if (!sizeof(args))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (file_size(log = QH_LOG_FILE(args[0])) < 1)
    {
        write("There is no log information for that quest.\n");
        return 1;
    }

    this_player()->more(log, 1);
    return 1;
}

int _quest_stats(string *args)
{
    mixed *info;
    mapping m;
    int i, t;
    string avg, times_completed, group, bit, exp, l, desc, act;

    if (!sizeof(args))
    {
        args = m_indices(quest_info);
    }

    setuid();
    seteuid(getuid());

    for (i = 0; i < sizeof(args); i++)
    {
    	info = quest_info[args[i]];
    	m = QH_RESTORE_DATA_FILE(args[i]);
    
    	if (pointerp(info))
    	{
    	    group = info[GROUP] + "";
    	    bit   = info[BIT] + "";
    	    exp   = info[XP] + "";
    	    act   = "The quest is " + 
                    (info[DEACT] ? "deactivated" : "activated") + ".\n";
    	    desc  = info[DESC];
    	}
    	else    
    	{
    	    if (!m_sizeof(m))
    	    {
    		write("No information on " + args[i] + ".\n");
    		continue;
    	    }
    
    	    group = bit = exp = "N/A";
    	    desc = "";
    	}
    
    	if (t = m["times_completed"])
    	{
    	    avg = (m["stat_sum"] / t) + "";
    	}
    	else
    	{
    	    avg = "N/A";
    	}
    
    	times_completed = t + "";
    
    	if (!(l = m["last_completed"]))
    	{
    	    l = "N/A";
    	}
    
    	write("\n" + "** " + args[i] + " **\n" + desc + "\n\n");
    	write(sprintf("Group Bit  Exp      Times Completed  Avg. Stat Avg. " +
    	      "   Last Completed\n" +
    	      "====================================================" +
    	      "=====================\n%|5s %|3s  %-8s %|15s  %|14s    %-s\n\n",
    	      group, bit, exp, times_completed, avg, l));
    
    	write(act);
    }

    return 1;
}

static string *find_info(string name, string file)
{
    string *lines, str, first_letter, first_letter2;

    str = QH_LOG_FILE(file);

    if (file_size(str) < 1)
    {
        return ({});
    }

    str = read_file(str);

    lines = explode(str, "\n");

    first_letter = name[0..0];
    if (first_letter == (first_letter2 = capitalize(first_letter)))
    {
        first_letter2 = lower_case(first_letter);
    }

    name = sprintf("^[%s%s]%s", first_letter, first_letter2, name[1..]);

    lines = regexp(lines, name);
    return lines;
}

int _quest_info(string *args)
{
   string name, *quests, *arr;
   int i;
   mixed *info;

   if (!sizeof(args))
   {
       return 0;
   }

   name = args[0];

   if (sizeof(args) > 1)
   {  
       quests = args[1..];
   }
   else
   {
       quests = m_indices(quest_info);
   }

   setuid();
   seteuid(getuid());

   for (i = 0; i < sizeof(quests); i++)
   {
       if (sizeof(arr = find_info(name, quests[i])))
       {
           if (pointerp(info = quest_info[quests[i]]))
           {
               write(sprintf("Quest: %-35s Group: %2d  Bit: %d  Exp: %d\n",
                   quests[i], info[GROUP], info[BIT], info[XP]));
           }
           else
           {
               write("Quest: " + quests[i]);
           }

           write("========================================================" +
                 "=====================\n");
           write(implode(arr, "\n") + "\n\n");
       }
   }

   return 1;
}

int _quest_tail(string *args)
{
    string log;

    if (!sizeof(args))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (file_size(log = QH_LOG_FILE(args[0])) < 1)
    {
        write("There is no log information for that quest.\n");
        return 1;
    }

    tail(log);
    return 1;
}

int _quest_save(string *args)
{
    string log, dest;

    if (sizeof(args) < 2)
    {
        return 0;
    }

    if (!sizeof(args))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (file_size(log = QH_LOG_FILE(args[0])) < 1)
    {
        write("There is no log information for that quest.\n");
        return 1;
    }

    dest = FTPATH(this_player()->query_path(), args[1]);

    switch (file_size(dest))
    {
        case -2:
            write(dest + " is a directory.\n");
            return 1;

        case -1:
            break;

        default:
            if (!rm(dest))
	    {
                write("Could not overwrite " + dest + ".\n");
                return 1;
	    }

            break;
    }

    log = read_file(log);

    if (write_file(dest, log))
    {
        write("Quest log saved in " + dest + ".\n");
    }
    else
    {
        write("Could not write to " + dest + ".\n");
    }

    return 1;
}

void init()
{
    ::init();
    add_action(quest, "quest");
}

static nomask void log(object who, string quest_name)
{
    mapping m;
    string str, log_msg, t, xp, name;
    int avg = who->query_average_stat();
    mixed *info;

    setuid();
    seteuid(getuid());

    m = QH_RESTORE_DATA_FILE(quest_name);

    t = ctime(time());

    if (!pointerp(info = quest_info[quest_name]))
    {
        xp = "???";
    }
    else
    {
        xp = info[XP] + "";
    }

    /*
     * This format can be changed, but it's important that the name be
     * the first thing on each line and that there is one entry per line.
     */
    log_msg = sprintf("%-12s (Stat Avg %-3d) %s xp %s\n", 
        capitalize(name = who->query_real_name()), avg, xp, t);

    write_file(QH_LOG_FILE(quest_name), log_msg);

    /* Don't bother altering quest statistics for non-interactives,
     * wizards, or jr's
     */
    if (interactive(who) && !SECURITY->query_wiz_level(name) &&
        !wildmatch("*jr", name))
    {
	m["times_completed"] = m["times_completed"] + 1;
	m["stat_sum"] = m["stat_sum"] + avg;
	m["last_completed"] = t;
    }

    QH_SAVE_DATA_FILE(quest_name, m);
}

int query_quest_completed(object who, string quest_name)
{
    mixed *info;

    if (!pointerp(info = quest_info[quest_name]))
    {
        return 0;
    }

    return who->test_bit(domain(this_object()), info[0], info[1]);
}

int quest_completed(object who, string quest_name)
{
    mixed *info;
    string euid, dom;

    /* Check to see if the quest has been completed already */
    if (query_quest_completed(who, quest_name))
    {
        return 0;
    }

    /* Is the quest registered? */
    if (!pointerp(info = quest_info[quest_name]))
    {
        return 0;
    }

    /* Check to see if the quest is deactivated */
    if (info[DEACT])
    {
        return 0;
    }

    /* Make sure it's secure to set the bit. */

    euid = geteuid(previous_object());
    dom = domain(this_object());

    if ((euid != dom) &&
        (SECURITY->query_wiz_dom(euid) != dom))
    {
        return 0;
    }

    /* set the bit */
    who->set_bit(info[0], info[1]);

    /* add the experience */
    who->add_exp(info[2]);

    /* log the quest completion */
    log(who, quest_name);

    return 1;
}
