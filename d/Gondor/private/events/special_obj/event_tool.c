/*
 * /d/Gondor/events/event_tool.c
 *
 * Gives commands to an event runner to create and customize
 * npcs and objects. Gives event runner command to reward
 * experience to a mortal.
 *
 * Originally coded by Gwyneth on September 27, 2000
 */

inherit "/std/object";

#include <const.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "../events.h"

int silent = 1, skill;
object creation, person;
string type, prop;

private int event_skill(string str);
private int event_props(string str);
private int event_number(string str);

public void
create_object()    
{
    set_name("wand");
    add_name("tool");

    set_adj("magic");
    add_adj("event");

    set_short("magic wand");

    set_long("Pure magic, meant for the mighty wizards in the sky, " +
        "this magic wand can be used for running events. One can " +
        "create life, and pull matter from thin air.\n\n" +
        "The words, \"event help\" have been etched into the " +
        "handle.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_GIVE, "@@wiz_check");
    add_prop(OBJ_M_NO_DROP, 1);

    setuid();
    seteuid(getuid());
}

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

    write_file(TOOLLOG, ctime(time()) + ": " +
        capitalize(dest->query_real_name()) +
        " aquired an event tool.\n");
}

private int
event_done()
{
    if (!objectp(creation))
    {
        notify_fail("Object doesn't exist, aborting creation.\n");
        return 0;
    }

    write_file(CREATELOG, ctime(time()) + ": " +
        capitalize(this_interactive()->query_real_name()) +
        " created " + LANG_ADDART(type) + " in " +
        file_name(environment(this_interactive())) + ".\n");

    if (type != "npc")
    {
        write("You wave your magic wand and pull forth " +
            LANG_ADDART(type) + " from another dimension.\n");
        creation->move(this_interactive(), 1);
        return 1;
    }
    else
    {
        write("You wave your magic wand and pull forth a " +
            "being from another dimension.\n");
        creation->refresh_living();
        creation->move(environment(this_interactive()), 1);
        return 1;
    }
}

private string
event_parsing(string str)
{
    str = lower_case(str);

    if (!objectp(creation))
    {
        return ("Object not present, aborting.\n");
    }

    if (!strlen(str))
    {
        creation->remove_object();
        return ("You must provide a value.\n");
    }

    if (str == "~q")
    {
        creation->remove_object();
        return ("Aborting creation. Destructing object.\n");
    }
}

private int
event_break(string str)
{
    int brk;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", brk);
    creation->set_likely_break(brk);
    event_done();
    return 1;
}

private int
event_ac(string str)
{
    int ac;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", ac);
    creation->set_ac(ac);
    write("Enter difficulty to break ([0, 20] recommended): ");
    input_to(event_break);
    return 1;
}

private int
event_dr_amt(string str)
{
    int amt;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", amt);
    creation->set_soft_amount(amt);
    write("Enter number of items: ");
    input_to(event_number);
    return 1;
}

private int
event_alco(string str)
{
    int alco;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", alco);
    creation->set_alco_amount(alco);
    write("Enter amount of liquid: ");
    input_to(event_dr_amt);
    return 1;
}

private int
event_unique(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }
    creation->add_prop(HEAP_S_UNIQUE_ID, str);
    event_done();
    return 1;
}

private int
event_number(string str)
{
    int num;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", num);

    creation->set_heap_size(num);
    write("Enter unique heap id: ");
    input_to(event_unique);
    return 1;
}

private int
event_fill(string str)
{
    int fill;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", fill);
    creation->set_amount(fill);
    write("Enter number of items: ");
    input_to(event_number);

    return 1;
}

private int
event_title(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    creation->set_title(str);
    event_done();
    return 1;
}

private int
event_race(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    creation->set_race_name(str);
    write("Enter title (the Great Champion of the Land): ");
    input_to(event_title);
    return 1;
}

private int
event_gender(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    str = lower_case(str);

    switch(str)
    {
        case "f":
        case "female":
            creation->set_gender(G_FEMALE);
            break;
        case "m":
        case "male":
            creation->set_gender(G_MALE);
            break;
        default:
            creation->set_gender(G_NEUTER);
            break;
     }

     write("Enter race(hobbit, elf, goblin, etc.): ");
     input_to(event_race);
     return 1;


}

private int
event_sk_val(string str)
{
    int val;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", val);
    creation->set_skill(skill, val);
    write("Enter numeric skill to set. Type done to finish skill setting: ");
    input_to(event_skill);
    return 1;
}

private int
event_skill(string str)
{
    if (!objectp(creation))
    {
        notify_fail("Object not present, aborting.\n");
        return 0;
    }
    if (str == "~q")
    {
        creation->remove_object();
        notify_fail("Aborting creation. Destructing object.\n");
        return 0;
    }

    if (str == "done" || !strlen(str))
    {
        write("Enter gender(m/f/n): ");
        input_to(event_gender);
        return 1;
    }

    sscanf(str, "%d", skill);
    write("Enter value for that skill(1-100): ");
    input_to(event_sk_val);
    return 1;
}

private int
event_stats(string str)
{
    int *stats, s0, s1, s2, s3, s4, s5;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d %d %d %d %d %d", s0, s1, s2, s3, s4, s5);
    stats = ({s0, s1, s2, s3, s4, s5});
    creation->set_stats(stats);
    write("Enter numeric skill to set " +
        "(Type 'done' to finish skill setting.): ");
    input_to(event_skill);
    return 1;
}

private int
event_align(string str)
{
    int align;

    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", align);
    creation->set_alignment(align);
    write("Enter stats (str dex con int wis dis): ");
    input_to(event_stats);
    return 1;
}

private int
event_pen(string str)
{
    int pen;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", pen);
    creation->set_pen(pen);
    write("Enter difficulty to break (0-20): ");
    input_to(event_break);
    return 1;
}

private int
event_hit(string str)
{
    int hit;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    sscanf(str, "%d", hit);
    creation->set_hit(hit);
    write("Enter weapon penetration: ");
    input_to(event_pen);
    return 1;
}

private int
event_prop_val(string str)
{
    int val, num;
    
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    val = sscanf(str, "%d", num);

    if (!val)
    {
        creation->add_prop(prop, str);
    }
    else
    {
        creation->add_prop(prop, num);
    }

    write("Enter prop to add or type done. Remember food and drink " +
        "are heap items (_obj_i_value): ");
    input_to(event_props);
    return 1;
}

private int
event_props(string str)
{
    if (!objectp(creation))
    {
        notify_fail("Object not present, aborting.\n");
        return 0;
    }
    if (str == "~q")
    {
        creation->remove_object();
        notify_fail("Aborting creation. Destructing object.\n");
        return 0;
    }

    if (str == "done" || !strlen(str))
    {
        switch(type)
        {
            case "armour":
                write("Enter armour class: ");
                input_to(event_ac);
                break;
            case "drink":
                write("Enter alcohol level: ");
                input_to(event_alco);
                break;
            case "food":
                write("Enter amount of food in grams: ");
                input_to(event_fill);
                break;
            case "npc":
                write("Enter alignment: ");
                input_to(event_align);
                break;
            case "object":
                event_done();
                break;
            case "weapon":
                write("Enter weapon to hit: ");
                input_to(event_hit);
                break;
        }

        return 1;
    }

    prop = str;

    write("Enter value for " + str + ": ");
    input_to(event_prop_val);
    return 1;
}


private int
event_adjs(string str)
{
    if (!objectp(creation))
    {
        notify_fail("Object not present, aborting.\n");
        return 0;
    }
    if (str == "~q")
    {
        creation->remove_object();
        notify_fail("Aborting creation. Destructing object.\n");
        return 0;
    }

    if (str == "done" || !strlen(str))
    {
        write("Enter prop to add or type done. Remember food and " +
            "drinks are heap items. (_obj_i_value): ");
        input_to(event_props);
        return 1;
    }

    creation->add_adj(({str}));
    write("Enter adjective to add. Type done to finish adjective " +
        "setting.: ");
    input_to(event_adjs);
    return 1;
}

private int
event_long(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    creation->set_long(str + "\n");
    write("Enter adjective to add. Type done to finish adjective " +
        "setting.: ");
    input_to(event_adjs);
    return 1;
}

private int
event_short(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    creation->set_short(str);
    write("Enter long description: ");
    input_to(event_long);
    return 1;
}

private int
event_name(string str)
{
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    str = lower_case(str);

    creation->set_name(str);
    write("Enter short description: ");
    input_to(event_short);
    return 1;
}

private int
give_exp(string str)
{
    int x, com, gen, quest;

    if (!strlen(str))
    {
        notify_fail("You must provide a value.\n");
        return 0;
    }

    if (str == "~q")
    {
        write("Aborting reward. No experience given.\n");
        return 1;
    }

    x = sscanf(str, "%d %d %d", com, gen, quest);

    if (com > 0)
    {
        person->add_exp_combat(com);
    }
    if (gen > 0)
    {
        person->add_exp_general(gen);
    }
    if (quest > 0)
    {
        person->add_exp_quest(quest);
    }

    if (silent)
    {
        tell_object(person, "You feel more experienced.\n");
    }
    else
    {
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " waves " + this_player()->query_possessive() +
            " magic wand at " + QTNAME(person) + ".\n",
            ({person, this_player()}));
        tell_object(person, this_player()->query_The_name(person) +
            " waves " + this_player()->query_possessive() + " magic " +
            "wand at you.\nYou feel more experienced.\n");
    }

    write("You wave your magic wand and reward " +
        person->query_name() + " with " +
        com + " combat experience, " + gen + " general experience and " +
        quest + " quest experience.\n");

    write_file(REWARDLOG, ctime(time()) + ": " +
        this_interactive()->query_name() + " awarded " +
        com + " combat, " + gen + " general and " + quest + " quest " +
        "experience to " + person->query_name() + ".\n");
    return 1;
}

private int
event_reward(string str)
{
    if (!strlen(str))
    {
        notify_fail("You must provide a value. Aborting reward.\n");
        return 0;
    }

    if (str == "~q")
    {
        write("Aborting reward.\n");
        return 1;
    }

    str = lower_case(str);

    person = find_player(str);
    if (!objectp(person))
    {
        notify_fail("No such player in the realms.\n");
        return 0;
    }

    write("Enter experience to reward (combat general quest): ");
    input_to(give_exp);
    return 1;
}

private int
event_create(string str)
{
    if (!strlen(str))
    {
        notify_fail("You must provide a value.\n");
        return 0;
    }

    str = lower_case(str);

    if (str == "~q")
    {
        write("Aborting creation.\n");
        return 1;
    }

    if (str == "silent reward")
    {
        silent = 1;
        write("Enter name of player to reward: ");
        input_to(event_reward);
        return 1;
    }

    if (str == "reward")
    {
        silent = 0;
        write("Enter the name of the player to reward: ");
        input_to(event_reward);
        return 1;
    }
    else if (member_array(str, EVENTLIST) != -1)
    {
        type = str;
        setuid();
        seteuid(getuid());
        creation = clone_object(EVENTOBJ + str);
        write("Enter the name: ");
        input_to(event_name);
        return 1;
    }

    write("Invalid option. Type ~q to quit. What do you want to " +
        "create?\n(armour, drink, food, npc, object, reward, silent " +
        "reward or weapon): ");
    input_to(event_create);
    return 1;

}

private int
event(string str)
{
    if (member_array(capitalize(this_interactive()->query_real_name()),
        AUTHORIZED) == -1)
    {
        notify_fail("You are not authorized to do that.\n");
        return 0;
    }

    if (str == "help")
    {
        write("Create a temporary object or npc for an event or " +
            "give a reward:\n\n" +
            "    event               - start creating\n" + 
            "    event armour        - create a basic armour\n" +
            "    event drink         - create a basic drink\n" +
            "    event food          - create a basic food\n" +
            "    event npc           - create a basic npc\n" +
            "    event object        - create a basic object\n" +
            "    event reward        - reward a player with experience\n" +
            "    event silent reward - reward a player silently\n" +
            "    event weapon        - create a basic weapon\n" +
            "    To quit at any time, type ~q.\n" + 
            "    Arguments are optional.\n\n");
        return 1;
    }

    if (!strlen(str))
    {
        write("What do you want to create? Type ~q to quit at " +
            "any time.\n(armour, drink, food, npc, object, reward, " +
            "silent reward or weapon): ");
        input_to(event_create);
        return 1;
    }
    else
    {
        event_create(str);
        return 1;
    }
}

public void
init()
{
    ::init();

    add_action(event, "event");
}

string
query_auto_load()
{
    return MASTER;
}
