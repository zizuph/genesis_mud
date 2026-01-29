#pragma no_clone
#pragma strict_types

#include "defs.h"
inherit "/cmd/std/command_driver";
inherit "/lib/skill_raise";
inherit LIB_DIR + "reanimate";
inherit LIB_DIR + "pathways";

static mapping skill_lookup = SS_SKILL_LOOKUP;

string
get_soul_id()
{
    return "Raumdor Tools";
}

nomask public int
query_tool_soul()
{
    return 1;
}

mapping
query_cmdlist()
{
    return ([
            "Autopath"  : "Autopath",
            "Bit"       : "Bit",
            "Darksight" : "Darksight",
            "Clock"     : "Clock",
            "Errors"    : "Errors",
            "Load"      : "Load",
            "Reanimate" : "Reanimate",
            "Raumdor"   : "Raumdor",
            "Runtime"   : "Runtime",
            "Skill"     : "Skill",
            "Undead"    : "Undead",
            "Who"       : "Who",
    ]);
}

int
Autopath(string str)
{
    object room = E(TP);
    string step, *waypoints = generate_waypoints(str);
    while (step = get_pathway_step(waypoints, E(TP)))
    {
        if (!stringp(step))
            break;
        TP->catch_msg("Stepping " + step + "...\n");
        TP->command("$" + step);
        if (E(TP) == room)
        {
            TP->catch_msg("Environment did not change. Aborting.\n");
            break;
        }
    }
    return 1;
}

int
Bit(string str)
{
    int bit, group;
    string end,
           *commands = ({"set", "clear", "test"});
    notify_fail("Syntax: " + query_verb() + " <set/clear/test> group bit\n");
    if (!str || !parse_command(str, ({}), "%p %s", commands, end))
        return 0;
    if (sscanf(end, "%d %d", group, bit) != 2)
        return 0;

    if (!seteuid(DOMAIN))
    {
        write("Failed to set euid to " + DOMAIN + ".\n");
        return 1;
    }

    if (commands[0] == "set")
    {
        write("Setting bit " + group + ":" + bit + " ...\n");
        if (TP->set_bit(group, bit))
            write("Success\n");
        else
            write("Failed!\n");
    }
    else if (commands[0] == "clear")
    {
        write("Clearing bit " + group + ":" + bit + " ...\n");
        if (TP->clear_bit(group, bit))
            write("Success\n");
        else
            write("Failed!\n");
    }
    else
    {
        write("Testing bit " + group + ":" + bit + " ...\n");
        if (TP->test_bit(DOMAIN, group, bit))
            write("set\n");
        else
            write("unset (or test failed)\n");
    }
    return 1;
}

int
Clock(string str)
{
    if (str == "tick")
        CLOCK->tick_tock();
    TP->catch_msg(CLOCK->query_time() + "\n");
    return 1;
}
    
int
Darksight(string str)
{
    if (str)
    {
        notify_fail("This takes no argument. It toggles darksight.\n");
        return 0;
    }

    TP->add_prop(LIVE_I_SEE_DARK, !TP->query_prop(LIVE_I_SEE_DARK));

    if (TP->query_prop(LIVE_I_SEE_DARK))
        write("Darksight on.\n");
    else
        write("Darksight off.\n");
    
    return 1;
}

int
Errors(string str)
{
    if (!strlen(str))
        str = "Raumdor";

    if (SECURITY->query_domain_number(str) > -1)
    {
        tail("/d/" + CAP(str) + "/log/errors");
        return 1;
    }
    notify_fail("Errors in which domain?\n");
    return 0;
}

int
Load(string str)
{
    string *files;
    if (!stringp(str))
        str = ".";
    string path = FTPATH((string)TP->query_path(), str);
    if (file_size(path) > 0)
        files = explode(path, "/")[-1..];
    else if(!wildmatch("*\\**", path))
    {
        if (!wildmatch("*/", path))
            path += "/";
        else
            path = "/";
    }
    
    if (!sizeof(files))
        files = get_dir(path);

    path = implode(explode(path + "/", "/")[..-2], "/") + "/";
    files = filter(files, &not() @ &wildmatch(".*", ));
    files = filter(files, &operator(!=)(-2, ) @ &file_size() @ &operator(+)(path, ));
    foreach (string file: files)
        TP->command("$load " + path + file);

    return 1;
}

int
Raumdor(string str)
{
    if (str)
    {
        notify_fail("No argument required.\n");
        return 0;
    }

    write("Commands:\n");
    foreach (string index: sort_array(m_indexes(query_cmdlist())))
    {
        write(index + "\n");
    }
    return 1;
}

int
Reanimate(string str)
{
    object target;

    if (strlen(str) && parse_command(str, E(TP), "%o", target))
    {
        if (!living(target))
        {
            notify_fail("It should be living.\n");
            return 0;
        }
        write("Reanimating...\n");
        target = FIX_TP(&reanimate_living(target));
        DUMP(target);
        target->move_living("X", E(TP));
        return 1;
    }
    notify_fail(CAP(query_verb()) + " what?\n");
    return 0;
}

int
Runtime(string str)
{
    if (!strlen(str))
        str = "Raumdor";

    if (SECURITY->query_domain_number(str) > -1)
    {
        tail("/d/" + CAP(str) + "/log/runtime");
        return 1;
    }
    notify_fail("Runtime in which domain?\n");
    return 0;
}

int
Skill(string str)
{
    string skill,
           syntax = "Syntax: " + query_verb() + " <skill name> <+/-/=> <amount>\n", 
           *mod = ({"+", "-", "="});
    int amount, skillnum, old;
   
    if (!str)
    {
        foreach (string key: sort_array(m_indexes(skill_lookup)))
           write(key + "\n");
        write(syntax);
        return 1;
    }

    notify_fail(syntax, 0);
    if (!parse_command(str, ({}), "%s %p %d", skill, mod, amount))
        return 0;

    if (!(skillnum = skill_lookup[skill]))
    {
        write("Skill not known: " + skill + "\n");
        return 1;
    }

    old = TP->query_skill(skillnum);

    if (mod[0] == "+")
        amount += old;
    else if (mod[0] == "-")
        amount = old - amount;
    
    TP->set_skill(skillnum, amount);
    write(skill + ": " + sk_rank(amount) + "\n");
    return 1;
}

int
Undead(string str)
{
    if (str)
    {
        notify_fail("This takes no argument. It toggles being undead.\n");
        return 0;
    }

    TP->add_prop(LIVE_I_UNDEAD, !TP->query_prop(LIVE_I_UNDEAD));
    
    if (TP->query_prop(LIVE_I_UNDEAD))
        write("You are now undead.\n");
    else
        write("You are no longer undead.\n");

    return 1;
}


int
Who(string str)
{
    object *list;

    if (!strlen(str))
        str = "Raumdor";

    if (SECURITY->query_domain_number(str) > -1)
    {
        list =  filter(users(),
            &operator(==)(CAP(str)) @ &->query_domain() @ environment);
        foreach(object player: list)
        {
            TP->catch_msg(CAP(player->query_real_name()) + ": " +
                MASTER_OB(E(player)) + "\n");
        }
        return 1;
    }
    notify_fail("Who in which domain?\n");
    return 0;
}
