/*
 * /d/Gondor/events/special_obj/emaster.c
 *
 * Gives commands to run an event to a wizard. Ability to preset
 * variables such as multiple groups kept track of by the leader's
 * name, experience, additional leader experience, multiple tells,
 * multiple echos. Options will include preseting, seeing the
 * location of each group member, tell, group tell, echo, group
 * echo, reward, group reward, display the presets, clear the
 * presets, query the team setup of group members and withdraw
 * and place an event npc.
 *
 * Originally coded by Gwyneth on October 2, 2000
 */

inherit "/std/object";

#include <composite.h>
#include <const.h>
#include <files.h>
#include <flags.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include "../events.h"

/* Global vars */
int general = 0, combat = 0, quest = 0, ex_gen = 0,
    ex_com, ex_qst;
mapping group_map = ([]), tell_map = ([]), echo_map = ([]);
object temp_obj;
string *temp_arr = ({}), temp_str;

/* Prototypes */
private int clear_map(string str);
private int display(string str);
private int distrib_item(string str);
private int echo_out(string str);
private int group_fol(string str);
private int npc_place(string str);
private int preset_echo(string str);
private int preset_exp(string str);
private int preset_extra(string str);
private int preset_tell(string str);
private int reward_exp(string str);
private varargs int reward_out(int c, int g, int q, string silent);
private int tell_out(string str);
private int won_out(string str);

public void
create_object()    
{
    set_name("ball");
    add_name("event_master");
    add_name("emaster");
    add_name("master");

    set_adj("crystal");
    add_adj("event");

    set_short("crystal ball");

    set_long("Pure magic, meant for the mighty wizards in the sky, " +
        "this crystal ball can be used for running events. " +
        "The words, 'master help' have been etched into the " +
        "handle.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    setuid();
    seteuid(getuid());
}

/*
 * Function name: enter_env
 * Description  : Tests to see if the holder is authorized to have
 *                this item. Self destructs if not. Logs aquisitions.
 *                Runs previous enter_env() function.
 * Arguments    : object dest - destination, object old - previous
 *                environment
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!interactive(dest))
    {
        remove_object();
    }

    if (member_array(capitalize(dest->query_real_name()), AUTHORIZED) == -1)
    {
        remove_object();
    }

    write_file(MASTERLOG, ctime(time()) + ": " +
        capitalize(dest->query_real_name()) +
        " aquired a master tool.\n");
}

/*
 * Function name: menu
 * Description  : Prints out a menu of the command options.
 */
private void
menu()
{
        write("Organize and run events, options are:\n" +
            "\tmaster\t\t\t\t- start creating\n" + 
            "\tmaster clear\t\t\t- clear the presets\n" +
            "\tmaster display\t\t\t- display the presets\n" +
            "\tmaster distribute\t\t- distribute an item by domain\n" +
            "\tmaster echo\t\t\t- send an echo to a player's room\n" +
            "\tmaster gecho\t\t\t- send an echo to a group's room\n" +
            "\tmaster group\t\t\t- edit group setups\n" +
            "\tmaster help\t\t\t- options and their descriptions\n" +
            "\tmaster tell\t\t\t- send a tell to a player\n" +
            "\tmaster gtell\t\t\t- send a tell to a group\n" +
            "\tmaster npc\t\t\t- place or remove npc\n" +
            "\tmaster preset\t\t\t- preset variables\n" +
            "\tmaster reward\t\t\t- reward an individual\n" +
            "\tmaster greward\t\t\t- reward a group\n" +
            "\tmaster team\t\t\t- view teams\n" +
            "\tmaster where\t\t\t- display location of group\n" +
            "\tmaster won\t\t\t- end the game, reward and notify\n" +
            "\tTo quit at any time, type ~q.\n" +
            "\tArguments are optional.\n");
}

/*
 * Function name: clear
 * Description  : Clear preset variables
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
clear(string str)
{
    if (!strlen(str))
    {
        str = "all";
    }

    switch(str)
    {
        /* Escape out. */
        case "~q":
            write(ABORT);
            return 1;
        case "all":
            general = 0;
            quest = 0;
            combat = 0;
            ex_com = 0;
            ex_gen = 0;
            ex_qst = 0;
            tell_map = ([]);
            echo_map = ([]);
            group_map = ([]);
            display("all");
            return 1;
        case "exp":
        case "experience":
            general = 0;
            quest = 0;
            combat = 0;
            ex_gen = 0;
            ex_com = 0;
            ex_qst = 0;
            display("all");
            return 1;
        case "general":
            general = 0;
            display("all");
            return 1;
        case "quest":
            quest = 0;
            display("all");
            return 1;
        case "combat":
            combat = 0;
            display("all");
            return 1;
        case "extra":
        case "extra exp":
        case "extra experience":
            ex_gen = 0;
            ex_com = 0;
            ex_qst = 0;
            display("all");
            return 1;
        case "extra general":
        case "extra gen":
            ex_gen = 0;
            display("all");
            return 1;
        case "extra quest":
            ex_qst = 0;
            display("all");
            return 1;
        case "extra com":
        case "extra combat":
            ex_com = 0;
            display("all");
            return 1;
        case "tell":
        case "tells":
            if (!sizeof(m_indexes(tell_map)))
            {
                write("No tells preset.\n");
                return 1;
            }
            display("tell");
            temp_str = "tell";
            write(CLEARMAP);
            input_to(clear_map);
            return 1;
        case "echo":
        case "echos":
            if (!sizeof(m_indexes(echo_map)))
            {
                write("No echos preset.\n");
                return 1;
            }
            temp_str = "echo";
            display("echo");
            write(CLEARMAP);
            input_to(clear_map);
            return 1;
        case "group":
        case "groups":
            if (!sizeof(m_indexes(group_map)))
            {
                write("No groups preset yet.\n");
                return 1;
            }
            temp_str = "group";
            display("group");
            write(CLEARMAP);
            input_to(clear_map);
            return 1;
        default:
            write("Invalid option. " + CLEAR);
            input_to(clear);
            return 1;
    }
}

private int
clear_map(string str)
{
    if (!strlen(str))
    {
        write(CLEARMAP);
        input_to(clear_map);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    switch(temp_str)
    {
        case "tell":
            if (str == "all")
            {
                tell_map = ([]);
                write("Tells cleared.\n");
                return 1;
            }
            if (member_array(str, m_indexes(tell_map)) == -1)
            {
                write("No such tell name. " + CLEARMAP);
                input_to(clear_map);
                return 1;
            }
            else
            {
                tell_map = m_delete(tell_map, str);
                write("Remaining tells:\n");
                display("tell");
            }

            temp_str = "";
            return 1;
        case "echo":
            if (str == "all")
            {
                echo_map = ([]);
                write("Echos cleared.\n");
                return 1;
            }
            if (member_array(str, m_indexes(echo_map)) == -1)
            {
                write("No such echo name. " + CLEARMAP);
                input_to(clear_map);
                return 1;
            }
            else
            {
                echo_map = m_delete(echo_map, str);
                write("Remaining echos:\n");
                display("echo");
            }

            temp_str = "";
            return 1;
        case "group":
            str = lower_case(str);
            if (str == "all")
            {
                group_map = ([]);
                write("Groups cleared.\n");
                return 1;
            }
            if (member_array(str, m_indexes(group_map)) == -1)
            {
                write("No such group name. " + CLEARMAP);
                input_to(clear_map);
                return 1;
            }
            else
            {
                group_map = m_delete(group_map, str);
                write("Remaining groups:\n");
                display("group");
            }

            temp_str = "";
            return 1;
        default:
            write("Clear error." + ABORT);
            return 1;
    }
}

/*
 * Function name: display
 * Description  : Display presets
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
display(string str)
{
    int index, size, index2, size2;
    string *domain, val, *arr;

    if (!strlen(str))
    {
        str = "default";
    }
    switch(str)
    {
        case "~q":
            write(ABORT);
            return 1;
        case "exp":
        case "experience":
            write("Combat exp preset at:\t" + combat + "\n" +
                  "General exp preset at:\t" + general + "\n" +
                  "Quest exp preset at:\t" + quest + "\n" +
                  "Extra combat preset at:\t" + ex_com + "\n" +
                  "Extra quest preset at:\t" + ex_qst + "\n" +
                  "Extra gen preset at:\t" + ex_gen + "\n");
            return 1;
        case "tell":
        case "tells":
            domain = m_indexes(tell_map);
            size = sizeof(domain);
            if (!size)
            {
                write("No preset tells.\n");
                return 1;
            }
            for (index = 0; index < size; index++)
            {
                write("Tell preset " + domain[index] + ":\t" +
                      tell_map[domain[index]] + "\n");
            }
            return 1;
        case "echo":
        case "echos":
            domain = m_indexes(echo_map);
            size = sizeof(domain);
            if (!size)
            {
                write("No preset echos.\n");
                return 1;
            }
            for (index = 0; index < size; index++)
            {
                write("Echo preset " + domain[index] + ":\t" +
                    echo_map[domain[index]] + "\n");
            }
            return 1;
        case "group":
        case "groups":
            domain = m_indexes(group_map);
            if (!sizeof(domain))
            {
                write("No groups preset yet.\n");
                return 1;
            }
            
            for (index = 0, size = sizeof(domain); index < size; index++)
            {
                val = "";
                arr = group_map[domain[index]];
                size2 = sizeof(arr);
                for (index2 = 0; index2 < size2; index2++)
                {
                    val += "\t" + capitalize(arr[index2]) + "\n";
                }

                write("Group name and leader: ");
                write(domain[index] + "\nMembers:\n" + val);
            }
            return 1;
        default:
            display("exp");
            display("tell");
            display("echo");
            display("group");
            return 1;
    }

    return 1;

}

/*
 * Function name: distribute
 * Description  : Distribute an item to players in a domain or
 *                all of Genesis.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
distribute(string str)
{
    int index, size;
    object who;
    string *grps = ({}), *memb = ({});

    if (!strlen(str))
    {
        write(DISTRIBUTE);
        input_to(distribute);
        return 1;
    }
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (lower_case(str) == "comment")
    {
        index = -1;
        grps = m_indexes(group_map);
        size = sizeof(grps);
        while(++index < size)
        {
            memb += group_map[grps[index]];
        }

        size = sizeof(memb);
        if (!size)
        {
            write("No groups to distribute commenter to.\n");
            return 1;
        }
        index = -1;
        while(++index < size)
        {
            who = find_player(memb[index]);
            if (objectp(who))
            {
                clone_object(COMMENTER)->move(who, 1);
                who->catch_tell(COMMENTS);
                write("Commenter moved to " + capitalize(memb[index]) +
                    ".\n");
            }
            else
            {
                write(capitalize(memb[index]) + " not found.\n");
            }
        }
        return 1;
    }

    if (member_array(str, m_indexes(echo_map)) == -1)
    {
        temp_str = str;
    }
    else
    {
        temp_str = echo_map[str];
    }

    write("Echo is: " + temp_str + "\n" + DISTRIB2);
    input_to(distrib_item);
    return 1;
}

/*
 * Function name: distrib_item
 * Description  :
 * Arguments    : string str - domain and pathname of object
 * Returns      : 1
 */
private int
distrib_item(string str)
{
    int num, index, size;
    object *oblist, person;
    string path, domain, *groups_arr;

    if (!strlen(str))
    {
        write(DISTRIB2);
        input_to(distrib_item);
        return 1;
    }
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    num = sscanf(str, "%s %s", domain, path);

    if (num != 2)
    {
        write(DISTRIB2);
        input_to(distrib_item);
        return 1;
    }

    if (file_size(path) < 1)
    {
        write("File non-existant or empty.\n" + DISTRIB2);
        input_to(distrib_item);
        return 1;
    }

    domain = capitalize(domain);

    if (member_array(domain, SECURITY->query_domain_list()) == -1 &&
        domain != "All" &&
        domain != "Groups" &&
        member_array(lower_case(domain), m_indexes(group_map)) == -1)
    {
        write("Non-existant domain or group(s).\n" + DISTRIB2);
        input_to(distrib_item);
        return 1;
    }
    if (member_array(lower_case(domain), m_indexes(group_map)) != -1)
    {
        groups_arr = group_map[lower_case(domain)];
        for (index = 0, size = sizeof(groups_arr); index < size; index++)
        {
            person = find_living(groups_arr[index]);
            if (objectp(person))
            {
                clone_object(path)->move(person, 1);
                person->catch_tell(temp_str + "\n");
                write("Object " + path + " moved to " +
                    capitalize(groups_arr[index]) + ".\n");
            }
            else
            {
                write("Player " + capitalize(groups_arr[index]) +
                    " not present.\n");
            }
        }
        write("Tell sent: " + temp_str + "\n");
        return 1;
    }
    if (domain == "Groups")
    {
        groups_arr = m_indexes(group_map);
        for (index = 0, size = sizeof(groups_arr); index < size; index++)
        {
            temp_arr += group_map[groups_arr[index]];
        }
        for (index = 0, size = sizeof(temp_arr); index < size; index++)
        {
            person = find_living(temp_arr[index]);
            
            if (objectp(person))
            {
                clone_object(path)->move(person, 1);
                person->catch_tell(temp_str + "\n");
                write("Object " + path + " moved to " +
                    capitalize(temp_arr[index]) + ".\n");
            }
            else
            {
                write("Player " + capitalize(temp_arr[index]) +
                    " not present.\n");
            }
        }
        write("Tell sent: " + temp_str + "\n");
        return 1;
    }

    oblist = users();
    size = sizeof(oblist);
    index = -1;

    while(++index < size)
    {
        if (environment(oblist[index])->query_domain() == domain ||
            domain == "All")
        {
            if (oblist[index]->query_wiz_level())
            {
                write("Object not distributed to the wizard, " +
                    oblist[index]->query_name() + ".\n");
            }
            else
            {
                clone_object(path)->move(oblist[index], 1);
                oblist[index]->catch_tell(temp_str + "\n");
                write("Object " + path + " moved to " +
                    oblist[index]->query_name() + " in the domain of " +
                    domain + ".\n");
            }
        }
    }

    write("Tell message: " + temp_str + "\n");
    return 1;

}

/*
 * Function name: echo
 * Description  : Send an echo to the environments of an individual(s)
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
echo(string str)
{
    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(ECHO);
            input_to(echo);
            return 1;
        }
        else
        {  
            write(ECHO2);
            input_to(echo_out);
            return 1;
        }
    }

    str = lower_case(str);
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }
    
    temp_arr += ({str});

    write(ECHO);
    input_to(echo);
    return 1;
}

private int
echo_out(string str)
{
    int index, size, num;
    object who, *env = ({});
    string *pecho;

    if (!strlen(str))
    {
        write("You must provide a message.\n" + ECHO2);
        input_to(echo_out);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }

    if (member_array(str, m_indexes(echo_map)) != -1)
    {
        str = echo_map[str];
    }

    if (lower_case(str) == "y" || lower_case(str) == "yes")
    {
        index = -1;
        size = sizeof(temp_arr);
        while(++index < size)
        {
            who = find_player(temp_arr[index]);
            if (objectp(who) &&
                interactive(who) &&
                (member_array(environment(who), env) == -1))
            {
                env += ({ environment(who) });
            }
            else if (!objectp(who) || !interactive(who))
            {
                write("No such player in the realms, or player is " +
                    "linkdead: " + capitalize(temp_arr[index]) + ".\n");
            }
        }

        index = -1;
        size = sizeof(env);
        if (!size)
        {
            write("No message sent.\n");
    
        }
        else
        {
            while(++index < size)
            {
                tell_room(env[index], temp_str + "\n");
                write("Message '" + temp_str + "' sent to room: " +
                    file_name(env[index]) + ".\n");
            }
        }

        temp_str = "";
        temp_arr = ({});
        return 1;
    }
    else if (lower_case(str) == "n" || lower_case(str) == "no")
    {
        write(ECHO2);
        input_to(echo_out);
        return 1;
    }
    else
    {
        temp_str = str;
        write("Test: ");
        write("Are you sure you want to echo '" + str + "' to " +
            implode(temp_arr, ", ") + "? (y/n): ");
        input_to(echo_out);
        return 1;
    }
    
    return 1;
}

/*
 * Function name: gecho
 * Description  : Send an echo to the environments of a group(s)
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
gecho(string str)
{
    int index, size;
    object *oblist;
    string *groups_arr;

    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(GECHO);
            input_to(gecho);
            return 1;
        }
        else
        {  
            write(ECHO2);
            input_to(echo_out);
            return 1;
        }
    }

    str = lower_case(str);
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }

    if (str == "groups")
    {
        groups_arr = m_indexes(group_map);

        for (index = 0,
          size = sizeof(groups_arr); index < size; index++)
        {
            temp_arr += group_map[groups_arr[index]];
        }
        
        write(ECHO2);
        input_to(echo_out);
        return 1;        
    }
    else if (str == "all")
    {
        oblist = users();
        size = sizeof(oblist);
        for (index = size - 1; index >= 0; index--)
        {
            if (oblist[index]->query_wiz_level())
            {
                oblist -= ({ oblist[index] });
            }
        }

        temp_arr = oblist->query_real_name();
        dump_array(temp_arr);
        write(ECHO2);
        input_to(echo_out);
        return 1;        

    }
    else if (member_array(str, m_indexes(group_map)) == -1)
    {
        write("Not a valid group, " + str + " " + GECHO);
        input_to(gecho);
        return 1;
    }
    else
    {
        temp_arr += group_map[str];
    }

    write(GECHO);
    input_to(gecho);
    return 1;
}

/*
 * Function name: group
 * Description  : Manage groups - create groups, add/remove members
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
group(string str)
{
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (!strlen(str))
    {
        write(GROUP);
        input_to(group);
        return 1;
    }

    str = lower_case(str);

    if (objectp(find_player(str)))
    {
        temp_str = str;
        temp_arr = ({ str });
        write(GROUP2);
        input_to(group_fol);
        return 1;
    }
    else
    {
        write("Player not found.\n" + GROUP);
        input_to(group);
        return 1;
    }
    return 1;
}

private int
group_fol(string str)
{
    if (!strlen(str))
    {
        group_map += ([ temp_str : temp_arr ]);
        display("group");
        temp_str = "";
        temp_arr = ({});
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    str = lower_case(str);

    if (objectp(find_player(str)))
    {
        if (member_array(str, temp_arr) == -1)
        {
            temp_arr += ({ str });
        }
        else
        {
            write(capitalize(str) + " is already a member.\n");
        }

        write(GROUP2);
        input_to(group_fol);
        return 1;
    }
    else
    {
        write("Player not found.\n" + GROUP2);
        input_to(group_fol);
        return 1;
    }

}

/*
 * Function name: tell
 * Description  : Send an anonymous tell to an individual(s).
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
tell(string str)
{
    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(TELL);
            input_to(tell);
            return 1;
        }
        else
        {  
            write(TELL2);
            input_to(tell_out);
            return 1;
        }
    }

    str = lower_case(str);
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }
    
    temp_arr += ({str});

    write(TELL);
    input_to(tell);
    return 1;
}

private int
tell_out(string str)
{
    int index, size, num;
    object who;
    string *ptell;

    if (!strlen(str))
    {
        write("You must provide a message.\n" + TELL2);
        input_to(tell_out);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }

    ptell = m_indexes(tell_map);
    num = member_array(str, ptell);

    if (num != -1)
    {
        str = tell_map[str];
    }

    if (lower_case(str) == "y" || lower_case(str) == "yes")
    {

        index = -1;
        size = sizeof(temp_arr);
        while(++index < size)
        {
            who = find_player(temp_arr[index]);
            if (objectp(who))
            {
                who->catch_tell("A tiny voice in your head whispers:\n" +
                    temp_str + "\n");
                write("Message '" + temp_str + "' sent to " +
                    who->query_name() + ".\n");
            }
            else
            {
                write("No such player in the realms.\n");
            }

            if (!interactive(who))
            {
                write("Player is linkdead or an npc: " +
                    capitalize(temp_arr[index]) + ".\n");
            }
        }

        temp_str = "";
        temp_arr = ({});
    }
    else if (lower_case(str) == "n" || lower_case(str) == "no")
    {
        write(TELL2);
        input_to(tell_out);
        return 1;
    }
    else
    {
        temp_str = str;
        write("Are you sure you want to send the tell '" + str +
            "' to " + implode(temp_arr, ", ") + "? (y/n): ");
        input_to(tell_out);
        return 1;
    }
}

/*
 * Function name: gtell
 * Description  : Send an anonymous tell to a group(s).
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
gtell(string str)
{
    int index, size;
    object *oblist;
    string *groups_arr;

    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(GTELL);
            input_to(gtell);
            return 1;
        }
        else
        {  
            write(TELL2);
            input_to(tell_out);
            return 1;
        }
    }

    str = lower_case(str);
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        temp_arr = ({});
        return 1;
    }

    if (str == "all")
    {
        oblist = users();
        size = sizeof(oblist);
        for (index = size - 1; index >= 0; index--)
        {
            if (oblist[index]->query_wiz_level())
            {
                oblist -= ({ oblist[index] });
            }
        }

        temp_arr = users()->query_real_name();

        write(TELL2);
        input_to(tell_out);
        return 1;
    }
    else if (str == "groups")
    {
        groups_arr = m_indexes(group_map);
        for (index = 0,
          size = sizeof(groups_arr); index < size; index++)
        {
            temp_arr += group_map[groups_arr[index]];
        }
        write(TELL2);
        input_to(tell_out);
        return 1;
    }
    else if (member_array(str, m_indexes(group_map)) == -1)
    {
        write(GTELL);
        input_to(gtell);
        return 1;
    }

    temp_arr += group_map[str];

    write(GTELL);
    input_to(gtell);
    return 1;

}

/*
 * Function name: npc
 * Description  : Place or remove an event npc.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
npc(string str)
{
    int num;
    object mobile;
    string name, action;

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (!strlen(str))
    {
        write(NPC);
        input_to(npc);
        return 1;
    }

    num = sscanf(str, "%s %s", action, name);

    if (num != 2)
    {
        write("Wrong number of arguments. " + NPC);
        input_to(npc);
        return 1;
    }

    action = lower_case(action);
    name = lower_case(name);

    mobile = find_living(name);

    if (!objectp(mobile) || objectp(find_player(name)))
    {
        write("No such npc found. " + NPC);
        input_to(npc);
        return 1;
    }

    switch(action)
    {
    case "remove":
        mobile->command("emote leaves the area.");
        mobile->remove_object();
        write(capitalize(name) + " removed.\n");
        return 1;
    case "place":
        temp_obj = mobile;
        write(NPC2);
        input_to(npc_place);
        return 1;
    default:
        write("Invalid option. " + NPC);
        input_to(npc);
        return 1;
    }
}

private int
npc_place(string str)
{
    object room;

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (!strlen(str))
    {
        write(NPC2);
        input_to(npc_place);
        return 1;
    }

    room = find_object(str);

    if (!objectp(room) || !IS_ROOM_OBJECT(room))
    {
        write("Not a valid destination. " + NPC2);
        input_to(npc_place);
        return 1;
    }
    else
    {
        temp_obj->move_living("M", room);
        temp_obj->command("emote arrives.");
        write("Npc placed in " + str + ".\n");
        return 1;
    }
}

/*
 * Function name: preset
 * Description  : Preset values - experience, messages, additional exp
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
preset(string str)
{
    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    /* No argument given, re-prompt and direct back to same function. */
    if (!strlen(str))
    {
        write(PRESET);
        input_to(preset);
        return 1;
    }

    /* Non-case sensitive */
    str = lower_case(str);

    switch(str)
    {
        /* Preset experience variables. */
        case "exp":
        case "experience":
            write(PRESETEXP);
            input_to(preset_exp);
            return 1;
        /* Preset tell message */
        case "extra":
        case "extra exp":
        case "extra experience":
            write(PRESETEX);
            input_to(preset_extra);
            return 1;
        case "tell":
            write(PRESET_T2);
            input_to(preset_tell);
            return 1;
        /* Preset echo message */
        case "echo":
            write(PRESET_E2);
            input_to(preset_echo);
            return 1;
        /* Invalid option, re-prompt and re-direct back into this func */
        default:
            write("Invalid option. " + PRESET);
            input_to(preset);
            return 1;
    }
}

private int
preset_exp(string str)
{
    int num, com, gen, qst;

    if (!strlen(str))
    {
        write(PRESETEXP);
        input_to(preset_exp);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    num = sscanf(str, "%d %d %d", com, gen, qst);
    if (num != 3)
    {
        write("Wrong number or type of arguments. " + PRESETEXP);
        input_to(preset);
        return 1;
    }
    else
    {
        combat = com;
        general = gen;
        quest = qst;
        display("exp");
        return 1;
    }
}

private int
preset_extra(string str)
{
    int num, com, gen, qst;

    if (!strlen(str))
    {
        write(PRESETEX);
        input_to(preset_extra);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    num = sscanf(str, "%d %d %d", com, gen, qst);
    if (num != 3)
    {
        write("Wrong number or type of arguments. " + PRESETEX);
        input_to(preset);
        return 1;
    }
    else
    {
        ex_com = com;
        ex_gen = gen;
        ex_qst = qst;
        display("exp");
        return 1;
    }

}

private int
echo_name(string str)
{
    if (!strlen(str))
    {
        write(PRESET_ECHO);
        input_to(echo_name);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    echo_map += ([ str : temp_str ]);
    write("Preset echo '" + str + "' added under the name " + str + ".\n");
    display("echo");
    temp_str = "";
    return 1;
}

private int
preset_echo(string str)
{
    if (!strlen(str))
    {
        write(PRESET_E2);
        input_to(preset_echo);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    temp_str = str;
    write(PRESET_ECHO);
    input_to(echo_name);
    return 1;
}

private int
tell_name(string str)
{
    if (!strlen(str))
    {
        write(PRESET_TELL);
        input_to(tell_name);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    tell_map += ([ str : temp_str ]);
    write("Preset tell '" + str + "' added under the name " + str + ".\n");
    display("tell");
    return 1;
}

private int
preset_tell(string str)
{
    if (!strlen(str))
    {
        write(PRESET_T2);
        input_to(preset_tell);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    temp_str = str;
    write(PRESET_TELL);
    input_to(tell_name);
    return 1;
}

/*
 * Function name: reward
 * Description  : Give a reward to an individual(s) anonymously.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
reward(string str)
{
    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(REWARD);
            input_to(reward);
            return 1;
        }
        else
        {
            write(EXP);
            input_to(reward_exp);
            return 1;
        }
    }

    str = lower_case(str);

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (!objectp(find_player(str)))
    {
        write("No such player. " + REWARD);
        input_to(reward);
        return 1;
    }
    else
    {
        temp_arr += ({ str });
    }

    write(REWARD);
    input_to(reward);
    return 1;
}

private int
reward_exp(string str)
{
    int num, com, gen, qst;
    string loud;

    if (!strlen(str))
    {
        write(EXP);
        input_to(reward_exp);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (lower_case(str) == "y" ||
      lower_case(str) == "yes")
    {
        if (temp_str == "exp")
        {
            reward_out(combat, general, quest);
            return 1;
        }
        if (temp_str == "exp silent")
        {
            reward_out(combat, general, quest, "silent");
            return 1;
        }
        if (temp_str == "extra silent")
        {
            reward_out(ex_com, ex_gen, ex_qst);
            return 1;
        }
        if (temp_str == "extra")
        {
            reward_out(ex_com, ex_gen, ex_qst);
            return 1;
        }

        num = sscanf(temp_str, "%d %d %d %s", com, gen, qst, loud);

        if (num == 3)
        {
            reward_out(com, gen, qst);
            return 1;
        }
        if (num == 4)
        {
            reward_out(com, gen, qst, loud);
            return 1;
        }
        else
        {
            write("Invalid number of arguments. " + EXP);
            input_to(reward_exp);
            return 1;
        }

    }
    else if (lower_case(str) == "n" ||
      lower_case(str) == "no")
    {
        write(EXP);
        input_to(reward_exp);
        return 1;
    }
    else
    {
        temp_str = str;
        write("Are you sure you want to reward ");
        switch(str)
        {
        case "extra":
            write(ex_com + " combat, " + ex_gen + " general and " +
                ex_qst + " quest");
            break;
        case "extra silent":
            write(ex_com + " combat, " + ex_gen + " general and " +
                ex_qst + " quest as silent");
            break;
        case "exp":
            write(combat + " combat, " + general + " general and " +
                quest + " quest");
            break;
        case "exp silent":
            write(combat + " combat, " + general + " general and " +
                quest + " quest as silent");
            break;
        default:
            write(str);
            break;
        }
        write(" experience to " + implode(temp_arr, ", ") + "? (y/n): ");
        input_to(reward_exp);
        return 1;
    }
}

private varargs int
reward_out(int com, int gen, int qst, string silent)
{
    int index, size;
    object who;
    string message;

    index = -1;
    size = sizeof(temp_arr);

    while(++index < size)
    {
        who = find_player(temp_arr[index]);
        if (!interactive(who))
        {
            write(capitalize(temp_arr[index]) + " is linkdead.\n");
        }

        if (com != 0)
        {
            who->add_exp_combat(com);
        }
        if (gen != 0)
        {
            who->add_exp_general(gen);
        }
        if (qst != 0)
        {
            who->add_exp_quest(qst);
        }

        message = (ctime(time()) + ": " +
            this_player()->query_name() + " rewarded " +
            capitalize(temp_arr[index]) + " with " +
            ((com != 0) ? ("combat: " + com + " ") : "") +
            ((gen != 0) ? ("general: " + gen + " ") : "") +
            ((qst != 0) ? ("quest: " + qst + " ") : "") +
            ((!strlen(silent) ? "non-silent" : "silent")));

        if (qst != 0 ||
          com != 0 ||
          gen != 0)
        {
            write_file(REWARDLOG, message + "\n");
            write(message + " experience.\n");
            if (!strlen(silent))
            {
                tell_object(who, "You feel more experienced!\n");
                clone_object(COMMENTER)->move(who, 1);
                tell_object(who, COMMENTS);
            }
        }
        else
        {
            write("No experience given.\n");
        }
    }

    temp_arr = ({});
    return 1;
}

/*
 * Function name: greward
 * Description  : Give a reward to a group(s) anonymously.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
greward(string str)
{
    if (!strlen(str))
    {
        if (!sizeof(temp_arr))
        {
            write(GREWARD);
            input_to(greward);
            return 1;
        }
        else
        {
            write(EXP);
            input_to(reward_exp);
            return 1;
        }
    }

    str = lower_case(str);

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (member_array(str, m_indexes(group_map)) == -1)
    {
        write("No such group. " + GREWARD);
        input_to(greward);
        return 1;
    }
    else
    {
        temp_arr += group_map[str];
    }

    write(GREWARD);
    input_to(greward);
    return 1;

}

/*
 * Function name: team
 * Description  : This routine prints the teams that are presently in the
 *                realms. After the name of each team captain, the number
 *                of members is listed (apart from the captain), and then
 *                the members are named.
 */
void
team()
{
    object *players;
    object *teams;
    int index;
    int size;
    int size2;

    /* Loop over all players in the realms. */
    players = users();
    index = -1;
    size = sizeof(players);
    while(++index < size)
    {
        /* See if they are leading a tm. */
        teams = players[index]->query_team();
        size2 = sizeof(teams);
        if (size2)
        {
            /* A nice compact little statement that will use a hanging
             * indent when there is a large team. Also, it pritns the
             * number of members in the team and a sorted list of the
             * names of the members.
             */
            write(HANGING_INDENT(sprintf("%-11s (%2d) %s",
                capitalize(players[index]->query_real_name()),
                size2, COMPOSITE_WORDS(sort_array(map(teams,
                &capitalize() @ &->query_real_name())))), 17, 0));
        }
    }
}

/*
 * Function name: where
 * Description  : Display the location of all group members.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
where()
{
    int index, size;
    object env, person;
    string *players = ({}), *mem = ({});

    if (!sizeof(m_indexes(group_map)))
    {
        write("No groups setup.\n");
        return 1;
    }
    else
    {
        players = m_indexes(group_map);
        index = -1;
        size = sizeof(players);
        while(++index < size)
        {
            mem += group_map[players[index]];
        }

        index = -1;
        size = sizeof(mem);
        while(++index < size)
        {
            person = find_player(mem[index]);
            if (objectp(person))
            {
                env = environment(person);
                write(capitalize(mem[index]) + " is in " +
                    file_name(env) + ".\n");
            }
            else
            {
                write(capitalize(mem[index]) + " not found.\n");
            }
        }

        return 1;
    }

    return 1;
}

/*
 * Function name: won
 * Description  : Declare the winner(s), reward the winner(s),
 *                and send a message to participants that the
 *                game is over.
 * Arguments    : string str - User input
 * Returns      : 1
 */
private int
won(string str)
{
    /* Prompt again for an argument if not given. */
    if (!strlen(str))
    {
        write(WON);
        input_to(won);
        return 1;
    }

    /* Escape out. */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (member_array(str, m_indexes(group_map)) == -1)
    {
        write("Not a group name. " + WON);
        input_to(won);
        return 1;
    }
    else
    {
        temp_str = str;
        temp_arr = group_map[str];

        write(capitalize(str) + " will be rewarded with an extra ");
        if (!combat &&
          !general &&
          !quest)
        {
            write("0 experience, ");
        }
        else
        {
            write(((combat != 0) ? ("combat: " + combat + " ") : "") +
                ((general != 0) ? ("general: " + general + " ") : "") +
                ((quest != 0) ? ("quest: " + quest + " ") : ""));
        }

        write(" and all group members will be rewarded with ");

        if (!ex_com &&
          !ex_gen &&
          !ex_qst)
        {
            write("0 experience");
        }
        else
        {
            write(((ex_com != 0) ? ("combat: " + ex_com + " ") : "") +
                ((ex_gen != 0) ? ("general: " + ex_gen + " ") : "") +
                ((ex_qst != 0) ? ("quest: " + ex_qst + " ") : ""));
        }
        write(" as soon as the message is entered.\n\n");
        write(WON2);
        input_to(won_out);
        return 1;
    }
}

private int
won_out(string str)
{
    int num, index, size;
    string type, message, leader;

    /* Prompt again for an argument if not given. */
    if (!strlen(str))
    {
        write(WON2);
        input_to(won);
        return 1;
    }

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    num = sscanf(str, "%s %s", type, message);

    if (num != 2)
    {
        write("Invalid number of arguments." + WON2);
        input_to(won_out);
        return 1;
    }

    /* Reward the group with preset experience. */
    reward_out(combat, general, quest);
 
    /* Reward leader with preset extra. */
    if (ex_com != 0 ||
      ex_gen != 0 ||
      ex_qst != 0)
    {
        temp_arr = ({ temp_str });
        reward_out(ex_com, ex_gen, ex_qst, "silent");
    }

    type = lower_case(type);

    temp_arr = ({});

    index = -1;
    size = sizeof(m_indexes(group_map));
    while(++index < size)
    {
        leader = m_indexes(group_map)[index];
        temp_arr += group_map[leader];
    }

    switch(type)
    {
        case "tell":
            if (member_array(message, m_indexes(tell_map)) != -1)
            {
                message = tell_map[message];
            }
            tell_out(message);
            break;
        case "echo":
            if (member_array(message, m_indexes(echo_map)) != -1)
            {
                message = echo_map[message];
            }
            echo_out(message);
            break;
        default:
            write("That is not an option. No message sent.\n");
            return 1;
    }
}

/*
 * Function name: master_create
 * Description  : All arguments to this function will
 *                be one of the commands in the MASTERLIST.
 *                This parses them and sends them off to
 *                their right functions.
 * Arguments    : string str - user input
 * Returns      : 1
 */
private int
master_create(string str)
{
    str = lower_case(str);

    /* Escape out */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }

    if (str == "group")
    {
        display("group");
    }

    /* Prompt user for arguments for indicated option command. */
    write(MESSAGES[str]);

    if (str == "where")
    {
        where();
        return 1;
    }
    if (str == "team")
    {
        team();
        return 1;
    }
    /* Send user's input on to pre-defined functions corresponding
       to the option desired. */
    input_to(FUNCS[str]);
    return 1;
}

/*
 * Function name: master
 * Description  : Handles initial parsing of the arguments
 *                received from the user, or prompts for
 *                arguments if none received. Sends input
 *                to master_create().
 * Arguments    : string str - user input
 * Returns      : 1 or 0
 */
private int
master(string str)
{
    /* Only allow pre-authorized people to use these commands. */
    if (member_array(capitalize(this_interactive()->query_real_name()),
        AUTHORIZED) == -1)
    {
        notify_fail("You are not authorized to do that.\n");
        return 0;
    }
    /* If no argument given, prompt for one and send received argument
       back through this function. */
    else if (!strlen(str))
    {
        menu();
        write("\nEnter option: ");
        input_to(master);
        return 1;
    }

    /* Reset the holding variables to null values. */
    temp_str = "";
    temp_arr = ({});
    temp_obj = 0;

    /* Non-case sensitive */
    str = lower_case(str);

    /* Escape out. */
    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }
    /* Print the menu to show the user the options. */
    else if (str == "help")
    {
        menu();
        return 1;
    }
    /* If argument is not an option, prompt for new
       argument and send back through the function. */
    else if (member_array(str, MASTERLIST) == -1)
    {
        write("Invalid option. ");
        menu();
        write("Enter option: ");
        input_to(master);
    }
    /* Checks passed, send the argument on to the next function. */
    else
    {
        master_create(str);
        return 1;
    }
}

object
redirect(object person)
{
    int i, size;
    object *oblist;

    oblist = users();

    i = -1;
    size = sizeof(oblist);
    while(++i < size)
    {
        if (oblist[i]->query_possessed() == person->query_real_name())
        {
            return oblist[i];
        }
    }
    return 0;
}

int
etell(string str)
{
    int idle;
    string name, message;
    object person, new_person, who = environment();

    if (!strlen(str))
    {
        notify_fail("Who do you want to tell what?\n");
        return 0;
    }
    sscanf(str, "%s %s", name, message);
    person = find_living(lower_case(name));
    name = capitalize(name);

    if (!objectp(person))
    {
        notify_fail("That player is not in the game.\n");
        return 0;
    }
    else if (person->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_F)
    {
        write(name + " seems to be busy at the moment. " +
            "If you want to be contacted when " + person->query_pronoun() +
            " is available again, use the 'audience' command.\n");
        return 1;
    }
    else if (!interactive(person))
    {
        new_person = redirect(person);
        if (objectp(new_person))
        {
            new_person->catch_tell(who->query_name() +
                (strlen(who->query_possessed()) ?
                ("(" + capitalize(who->query_possessed()) + ")") : ("")) +
                " tells you: " + message + "\n");
            if ((idle = query_idle(new_person)) > 300)
            {
                write(name + " is idle for " +
                    CONVTIME(idle) + " and may not react instantly.\n");
            }
            write("You tell " + name + "(" +
                new_person->query_name() + "): " + message + ".\n");
            return 1;
        }
        else
        {
            notify_fail(name + " is linkdead.\n");
            return 0;
        }
    }
    else
    {
        person->catch_tell(who->query_name() +
            (strlen(who->query_possessed()) ?
            ("(" + capitalize(who->query_possessed()) + ")") : ("")) +
            " tells you: " + message + "\n");
        if ((idle = query_idle(person)) > 300)
        {
            write(name + " is idle for " +
                CONVTIME(idle) + " and may not react instantly.\n");
        }
        write("You tell " + name + ": " + message + ".\n");
        return 1;
    }
}

/*
 * Function name: init
 * Description  : Adds the master command in addition to running
 *                the previous init() function.
 */
public void
init()
{
    ::init();

    add_action(master, "master");
    add_action(etell, "etell");
    add_action(etell, "et");
}

/*
 * Function name: query_auto_load
 * Description  : Allows object to be auto-loaded
 * Returns      : The filename.
 */
public string
query_auto_load()
{
    return MASTER;
}
