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
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../events.h"

/* Global variables */
int add, counter;
object creation;
string type, prop, skill;

/* Prototypes */
private int event(string str);
private int event_create(string str);
private void event_switch();
private int event_std(string str);
private int event_armour(string str);
private int event_drink(string str);
private int event_food(string str);
private int event_npc(string str);
private int npc_skills(string str);
private int event_weapon(string str);
private int event_done();


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

    if (member_array(capitalize(dest->query_real_name()), 
      AUTHORIZED) == -1)
    {
        remove_object();
    }

    write_file(TOOLLOG, ctime(time()) + ": " +
        capitalize(dest->query_real_name()) +
        " aquired an event tool.\n");
}

private mapping
query_at_list()
{
    return ([
        "A_BODY"         : A_BODY,
        "A_TORSO"        : A_TORSO,
        "A_CHEST"        : A_CHEST,
        "A_HEAD"         : A_HEAD,
        "A_NECK"         : A_NECK,
        "A_WAIST"        : A_WAIST,
        "A_LEGS"         : A_LEGS,
        "A_R_ARM"        : A_R_ARM,
        "A_L_ARM"        : A_L_ARM,
        "A_ARMS"         : A_ARMS,
        "A_ANY_ARM"      : A_ANY_ARM,
        "A_R_HAND"       : A_R_HAND,
        "A_L_HAND"       : A_L_HAND,
        "A_HANDS"        : A_HANDS,
        "A_ANY_HAND"     : A_ANY_HAND,
        "A_R_FINGER"     : A_R_FINGER,
        "A_L_FINGER"     : A_L_FINGER,
        "A_FINGERS"      : A_FINGERS,
        "A_ANY_FINGER"   : A_ANY_FINGER,
        "A_R_FOOT"       : A_R_FOOT,
        "A_L_FOOT"       : A_L_FOOT,
        "A_FEET"         : A_FEET,
        "A_ANY_FOOT"     : A_ANY_FOOT,
        "A_R_WRIST"      : A_R_WRIST,
        "A_L_WRIST"      : A_L_WRIST,
        "A_WRISTS"       : A_WRISTS,
        "A_ANY_WRIST"    : A_ANY_WRIST,
        "A_R_ANKLE"      : A_R_ANKLE,
        "A_L_ANKLE"      : A_L_ANKLE,
        "A_ANKLES"       : A_ANKLES,
        "A_ANY_ANKLE"    : A_ANY_ANKLE,
        "A_R_EAR"        : A_R_EAR,
        "A_L_EAR"        : A_L_EAR,
        "A_EARS"         : A_EARS,
        "A_ANY_EAR"      : A_ANY_EAR,
        "A_R_HIP"        : A_R_HIP,
        "A_L_HIP"        : A_L_HIP,
        "A_HIPS"         : A_HIPS,
        "A_ANY_HIP"      : A_ANY_HIP,
        "A_R_SHOULDER"   : A_R_SHOULDER,
        "A_L_SHOULDER"   : A_L_SHOULDER,
        "A_SHOULDERS"    : A_SHOULDERS,
        "A_ANY_SHOULDER" : A_ANY_SHOULDER,
        "A_BROW"         : A_BROW,
        "A_EYES"         : A_EYES,
        "A_BACK"         : A_BACK,
        "A_ROBE"         : A_ROBE,
        "A_SHIELD"       : A_SHIELD,
        ]);
}

private void
menu()
{
    write("Create a temporary object or npc for an event:\n " +
          "\tevent\t\t\t\t- start creating\n" + 
          "\tevent armour\t\t\t- create a basic armour\n" +
          "\tevent drink\t\t\t- create a basic drink\n" +
          "\tevent food\t\t\t- create a basic food\n" +
          "\tevent npc\t\t\t- create a basic npc\n" +
          "\tevent object\t\t\t- create a basic object\n" +
          "\tevent weapon\t\t\t- create a basic weapon\n" +
          "\tTo quit at any time, type ~q.\n" + 
          "\tArguments are optional.\n\n");
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
    if (!strlen(str))
    {
        counter = 0;
        add = 0;
        write("Type ~q to quit at any time.\n\t" + 
            implode(EVENTLIST, "\n\t") + "\nEnter option: ");
        input_to(event_create);
        return 1;
    }
    if (str == "help")
    {
        menu();
        return 1;
    }
    else
    {
        counter = 0;
        add = 0;
        event_create(str);
        return 1;
    }
}

private int
event_create(string str)
{
    if (!strlen(str))
    {
        write("Invalid option. Type ~q to quit." +
            implode(EVENTLIST, "\n\t") + "\nEnter option: ");
        input_to(event_create);
        return 1;
    }

    str = lower_case(str);

    if (str == "~q")
    {
        write(ABORT);
        return 1;
    }
    if (member_array(str, EVENTLIST) != -1)
    {
        creation = clone_object(EVENTOBJ + str);
        creation->move(this_player(), 1);
        type = str;
        write("Enter the name: ");
        input_to(event_std);
        return 1;
    }
    else
    {
        write("Invalid option. Type ~q to quit." + 
            implode(EVENTLIST, "\n\t") + "\nEnter option: ");
        input_to(event_create);
        return 1;
    }
}

private string
event_parsing(string str)
{
    str = lower_case(str);

    if (!objectp(creation))
    {
        counter = 0;
        return ("Object not present, aborting.\n");
    }

    if (str == "~q")
    {
        counter = 0;
        creation->remove_object();
        return ("Aborting creation. Destructing object.\n");
    }
}

private int
event_std(string str)
{
    int val, num;
    string fail = event_parsing(str);

    if (strlen(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter short description or <return> if making an npc: ");
            break;
        }

        str = lower_case(str);

        if (!add)
        {
            creation->set_name(str, (type != "npc"));
            add = 1;
        }
        else
        {
            creation->add_name(str, (type != "npc"));
        }
        
        write("Enter additional name or <return> when done: ");
        input_to(event_std);
        return 1;
    case 1:
        if (strlen(str) && type != "npc")
        {
            creation->set_short(str);
        }
        write("Enter plural name or <return> to accept default: ");
        break;
    case 2:
        if (strlen(str) > 0)
        {
            creation->set_pname(str);
        }
                
        write("Enter plural short or <return> to use default or " +
            "if making an npc:");
        break;
    case 3:
        if (strlen(str) > 0 &&
          type != "npc")
        {
            creation->set_pshort(str);
        }
        write("Enter long description: ");
        break;
    case 4:
        if (!strlen(str))
        {
            write("Enter long description: ");
            input_to(event_std);
            return 1;
        }
        creation->set_long(str + "\n");
        write("Enter adjective to add or <return> when " +
            "done: ");
        break;
    case 5:
        if (!strlen(str))
        {
            write("Enter prop to add or <return> when " +
                "done. (_obj_i_value" +
                "/_heap_i_unit_weight): ");
            break;
        }
        creation->add_adj(str);
        write("Enter adjective to add or <return> when done: ");
        input_to(event_std);
        return 1;
    case 6:
        if (!strlen(str))
        {
            counter = 0;
            event_switch();
            return 1;
        }
        prop = str;
        counter++;
        write("Enter value for " + str + ": ");
        input_to(event_std);
        return 1;
    case 7:
        if (!strlen(str))
        {
            write("Enter prop value: ");
            input_to(event_std);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (val)
        {
            creation->add_prop(prop, num);
        }
        else
        {
            creation->add_prop(prop, str);
        }
        counter--;
        write("Enter prop to add or <return> when " +
            "done. (_obj_i_value/_heap_i_unit_weight): ");
        input_to(event_std);
        return 1;
    default:
        write("Invalid end of switch in event_std\n");
        return 1;
    }

    counter++;
    input_to(event_std);
}

private void
event_switch()
{
    switch(type)
    {
    case "armour":
        write("Enter armour class: ");
        input_to(event_armour);
        break;
    case "drink":
        write("Enter alcohol level: ");
        input_to(event_drink);
        break;
    case "food":
        write("Enter amount of food in grams: ");
        input_to(event_food);
        break;
    case "npc":
        write("Enter alignment: ");
        input_to(event_npc);
        break;
    case "object":
        event_done();
        break;
    case "weapon":
        write("Enter weapon to hit: ");
        input_to(event_weapon);
        break;
    }

    return;
}

private int
event_armour(string str)
{
    int num, val;
    mapping arm_spot = ([]);
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter amount of armour class: ");
            input_to(event_armour);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter numeric armour class: ");
            input_to(event_armour);
            return 1;
        }
        creation->set_ac(num);
        write("Enter difficulty to break (0, 20): ");
        break;
    case 1:
        if (!strlen(str))
        {
            write("Enter difficulty to break (0, 20): ");
            input_to(event_armour);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter difficulty to break (0, 20): ");
            input_to(event_armour);
            return 1;
        }
        creation->set_likely_break(num);
        write("Enter armour spot (A_ROBE): ");
        break;
    case 2:
        if (!strlen(str))
        {
            write("Enter armour spot (A_ROBE): ");
            input_to(event_armour);
            return 1;
        }
        arm_spot = query_at_list();
        if (member_array(str, m_indexes(arm_spot)) == -1)
        {
            write("Enter armour spot (A_ROBE): ");
            input_to(event_armour);
            return 1;
        }
        creation->set_at(arm_spot[str]);
        event_done();
        return 1;
    default:
        write("Invalid end of switch in event_std\n");
        return 1;
    }
    counter++;
    input_to(event_armour);
    return 1;
}

private int
event_drink(string str)
{
    int num, val;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter amount of alcohol: ");
            input_to(event_drink);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter numeric amount of alcohol: ");
            input_to(event_drink);
            return 1;
        }
        creation->set_alco_amount(num);
        write("Enter amount of liquid: ");
        break;
    case 1:
        if (!strlen(str))
        {
            write("Enter amount of liquid: ");
            input_to(event_drink);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter numeric amount of liquid: ");
            input_to(event_drink);
            return 1;
        }
        creation->set_soft_amount(num);
        write("Enter number of items: ");
        break;
    case 2:
        if (!strlen(str))
        {
            write("Enter number of items: ");
            input_to(event_drink);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter number of items: ");
            input_to(event_drink);
            return 1;
        }
        creation->set_heap_size(num);
        write("Enter unique heap id: ");
        break;
    case 3:
        if (!strlen(str))
        {
            write("Enter unique heap id: ");
            input_to(event_drink);
            return 1;
        }
        creation->add_prop(HEAP_S_UNIQUE_ID, str);
        event_done();
        return 1;
    }

    counter++;
    input_to(event_drink);
    return 1;
}

private int
event_food(string str)
{
    int num, val;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter amount of food in grams: ");
            input_to(event_food);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter amount of food in grams: ");
            input_to(event_food);
            return 1;
        }
        creation->set_amount(num);
        write("Enter number of items: ");
        break;
    case 1:
        if (!strlen(str))
        {
            write("Enter number of items: ");
            input_to(event_food);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter number of items: ");
            input_to(event_food);
            return 1;
        }
        creation->set_heap_size(num);
        write("Enter unique heap id: ");
        break;
    case 2:
        if (!strlen(str))
        {
            write("Enter unique heap id: ");
            input_to(event_food);
            return 1;
        }
        creation->add_prop(HEAP_S_UNIQUE_ID, str);
        event_done();
        return 1;
    }

    counter++;
    input_to(event_food);

}

private int
event_npc(string str)
{
    int num, val, stren, dex, con, intel, wis, dis, *stats;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter alignment: ");
            input_to(event_npc);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter alignment: ");
            input_to(event_npc);
            return 1;
        }
        creation->set_alignment(num);
        write("Enter custom stats (str dex con int wis dis) or " +
            "preset stats\n(big/medium/small/default): ");
        break;
    case 1:
        if (!strlen(str))
        {
            write("Enter custom stats (str dex con int wis dis) or " +
                "preset stats\n(big/medium/small/default): ");
            input_to(event_npc);
            return 1;
        }
        /* Input stats into 6 stat variables */
        val = sscanf(str, "%d %d %d %d %d %d", 
              stren, dex, con, intel, wis, dis);
        if (!val)
        {
            if (str == "big")
            {
                stats = BIG_STATS;
                creation->add_prop(CONT_I_WEIGHT, 120);
                creation->add_prop(CONT_I_VOLUME, 120);
            }
            else if (str == "medium")
            {
                stats = MED_STATS;
                creation->add_prop(CONT_I_WEIGHT, 85);
                creation->add_prop(CONT_I_VOLUME, 85);
            }
            else if (str == "small")
            {
                stats = SMALL_STATS;
                creation->add_prop(CONT_I_WEIGHT, 50);
                creation->add_prop(CONT_I_VOLUME, 50);
            }
            else
            {
                stats = DEF_STATS;
                creation->add_prop(CONT_I_WEIGHT, 50);
                creation->add_prop(CONT_I_VOLUME, 50);
            }
            creation->set_stats(stats, 10);
            write("Respond to introductions? (y/n): ");
            break;
        }
        else if (val != 6)
        {
            write("Enter all six stats " +
                "(str dex con int wis dis) or: " +
                "preset stats (big, medium, small, default): ");
            input_to(event_npc);
            return 1;
        }
        stats = (({stren, dex, con, intel, wis, dis}));
        creation->set_stats(stats);
        write("Respond to introductions? (y/n): ");
        break;
    case 2:
        if (!strlen(str))
        {
            write("Respond to introductions? (y/n): ");
            input_to(event_npc);
            return 1;
        }
        creation->intro_toggle(str);
        write("Enter gender(m/f/n): ");
        break;
    case 3:
        if (!strlen(str))
        {
            write("Enter gender: ");
            input_to(event_npc);
            return 1;
        }
        if (str == "m" || str == "male")
        {
            creation->set_gender(G_MALE);
        }
        if (str == "f" || str == "female")
        {
            creation->set_gender(G_FEMALE);
        }
        if (str == "n" || str == "neuter")
        {
            creation->set_gender(G_NEUTER);
        }
        write("Enter race(hobbit, elf, goblin, etc.): ");
        break;
    case 4:
        if (!strlen(str))
        {
            write("Enter race(hobbit, elf, goblin, etc.): ");
            input_to(event_npc);
            return 1;
        }
        creation->set_race_name(str);
        write("Enter title (the Great Champion of the Land): ");
        break;
    case 5:
        if (!strlen(str))
        {
            write("Enter title (the Great Champion " +
                "of the Land): ");
            input_to(event_npc);
            return 1;
        }
        creation->set_title(str);
        write("Enter living name to refer to this npc: ");
        break;
    case 6:
        if (!strlen(str))
        {
            write("Enter living name to refer to this npc: ");
            input_to(event_npc);
            return 1;
        }
        creation->living_name(str);
        write("Enter skillset to add to npc (all/thief/" +
            "fighting/general/magic)\n<return> when done: ");
        input_to(event_npc);
        break;
    case 7:
        if (!strlen(str))
        {
            event_done();
            return 1;
        }
        skill = str;
        write("Enter level to set " + skill + " skills at\n" +
            "(max, expert, high, moderate, low or a number) " +
            "<return> when done: ");
        input_to(event_npc);
        break;
    case 8:
        if (!strlen(str))
        {
            write("Enter level to set " + skill + " skills at\n" +
                "(max, expert, high, moderate, low or a " +
                "number): ");
            input_to(event_npc);
            return 1;
        }
        npc_skills(str);
        write("Enter skillset to add to npc (all/thief/" +
            "fighting/general/magic)\n<return> when done: ");
        input_to(event_npc);
        counter --;
        return 1;
    }

    counter++;
    input_to(event_npc);
    return 1;
}

private int
npc_skills(string str)
{
    int *skillset, level = 0, i, size;

    string fail = event_parsing(str);

    switch(skill)
    {
    case "general":
        skillset = GENERAL;
        break;
    case "thief":
        skillset = THIEF;
        break;
    case "magic":
        skillset = MAGIC;
        break;
    case "fighting":
        skillset = FIGHTING;
        break;
    default:
        skillset = GENERAL;
        skillset += THIEF;
        skillset += MAGIC;
        skillset += FIGHTING;
        break;
    }

    sscanf(str, "%d", level);
    
    if (level < 0 || level > 100)
    {
	write("Skill out of range. " + capitalize(skill) +
	    " not set.\n");
	return 1;
    }
    
    switch(str)
    {
    case "max":
        level = 100;
        break;
    case "expert":
        level = 90;
        break;
    case "high":
        level = 75;
        break;
    case "moderate":
        level = 50;
        break;
    case "low":
        level = 20;
        break;
    }

    i = -1;
    size = sizeof(skillset);
    while(++i < size)
    {
	creation->set_skill(skillset[i], level);
    }
    
    return 1;
}

private int
event_weapon(string str)
{
    int num, val;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
    case 0:
        if (!strlen(str))
        {
            write("Enter weapon to hit: ");
            input_to(event_weapon);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter weapon to hit: ");
            input_to(event_weapon);
            return 1;
        }
        creation->set_hit(num);
        write("Enter weapon penetration: ");
        break;
    case 1:
        if (!strlen(str))
        {
            write("Enter weapon penetration: ");
            input_to(event_weapon);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter weapon penetration: ");
            input_to(event_weapon);
            return 1;
        }
        creation->set_pen(num);
        write("Enter difficulty to break (0-20): ");
        break;
    case 2:
        if (!strlen(str))
        {
            write("Enter difficulty to break: ");
            input_to(event_weapon);
            return 1;
        }
        val = sscanf(str, "%d", num);
        if (!val)
        {
            write("Enter difficulty to break: ");
            input_to(event_weapon);
            return 1;
        }
        creation->set_likely_break(num);
        event_done();
        return 1;
    }

    counter++;
    input_to(event_weapon);
    return 1;
}

private int
event_done()
{
    counter = 0;

    if (!objectp(creation))
    {
        notify_fail("Object doesn't exist, aborting creation.\n");
        return 0;
    }

    write_file(CREATELOG, ctime(time()) + ": " +
        capitalize(this_interactive()->query_real_name()) +
        " created " + LANG_ADDART(type) + ": " + creation->short() +
        " in " + file_name(environment(this_interactive())) + ".\n");

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
