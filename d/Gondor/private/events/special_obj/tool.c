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

int add, counter, silent = 1;
mapping skill = ([]);
object creation, *person = ({});
string type, prop, *group = ({});

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

private mapping
query_sk_list()
{
    return ([
        "SS_2H_COMBAT" : SS_2H_COMBAT,
        "SS_UNARM_COMBAT"       : SS_UNARM_COMBAT,
        "SS_BLIND_COMBAT"       : SS_BLIND_COMBAT,
        "SS_PARRY"              : SS_PARRY,
        "SS_DEFENCE"            : SS_DEFENCE,
        "SS_SPELLCRAFT"         : SS_SPELLCRAFT,
        "SS_HERBALISM"          : SS_HERBALISM,
        "SS_ALCHEMY"            : SS_ALCHEMY,
        "SS_FORM_TRANSMUTATION" : SS_FORM_TRANSMUTATION,
        "SS_FORM_ILLUSION"      : SS_FORM_ILLUSION,
        "SS_FORM_DIVINATION"    : SS_FORM_DIVINATION,
        "SS_FORM_ENCHANTMENT"   : SS_FORM_ENCHANTMENT,
        "SS_FORM_CONJURATION"   : SS_FORM_CONJURATION,
        "SS_FORM_ABJURATION"    : SS_FORM_ABJURATION,
        "SS_ELEMENT_FIRE"       : SS_ELEMENT_FIRE,
        "SS_ELEMENT_AIR"        : SS_ELEMENT_AIR,
        "SS_ELEMENT_EARTH"      : SS_ELEMENT_EARTH,
        "SS_ELEMENT_WATER"      : SS_ELEMENT_WATER,
        "SS_ELEMENT_LIFE"       : SS_ELEMENT_LIFE,
        "SS_ELEMENT_DEATH" : SS_ELEMENT_DEATH,
        "SS_OPEN_LOCK" : SS_OPEN_LOCK,
        "SS_PICK_POCKET" : SS_PICK_POCKET,
        "SS_ACROBAT" : SS_ACROBAT,
        "SS_FR_TRAP" : SS_FR_TRAP,
        "SS_SNEAK" : SS_SNEAK,
        "SS_HIDE"  : SS_HIDE,
        "SS_BACKSTAB" : SS_BACKSTAB,
        "SS_LANGUAGE" : SS_LANGUAGE,
        "SS_APPR_MON" : SS_APPR_MON,
        "SS_APPR_OBJ" : SS_APPR_OBJ,
        "SS_SWIM" : SS_SWIM,
        "SS_CLIMB" : SS_CLIMB,
        "SS_ANI_HANDL" : SS_ANI_HANDL,
        "SS_LOC_SENSE" : SS_LOC_SENSE,
        "SS_TRACKING" : SS_TRACKING,
        "SS_HUNTING" : SS_HUNTING,
        "SS_AWARENESS" : SS_AWARENESS,
        "SS_TRADING" : SS_TRADING,
        "SS_RIDING" : SS_RIDING
        ]);

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

private string
event_parsing(string str)
{
    str = lower_case(str);

    if (!objectp(creation))
    {
        return ("Object not present, aborting.\n");
    }

    if (str == "~q")
    {
        creation->remove_object();
        return ("Aborting creation. Destructing object.\n");
    }
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
    int num, val, s0, s1, s2, s3, s4, s5, *stats;
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
                "preset stats (big/medium/small/default): ");
            break;
        case 1:
            if (!strlen(str))
            {
                write("Enter stats (str dex con int wis dis): or " +
                    "preset stats (big/medium/small/default): ");
                input_to(event_npc);
                return 1;
            }
            val = sscanf(str, "%d %d %d %d %d %d", s0, s1, s2, s3, s4, s5);
            if (!val)
            {
                if (str == "big")
                {
                    stats = BIG_STATS;
                }
                else if (str == "medium")
                {
                    stats = MED_STATS;
                }
                else if (str == "small")
                {
                    stats = SMALL_STATS;
                }
                else
                {
                    stats = DEF_STATS;
                }
                creation->set_stats(stats, 10);
                write("Enter skill name to set or type done (SS_HIDE): ");
                break;
            }
            else if (val != 6)
            {
                write("Enter all six stats (str dex con int wis dis) or: " +
                    "preset stats (big, medium, small, default): ");
                input_to(event_npc);
                return 1;
            }
            stats = (({s0, s1, s2, s3, s4, s5}));
            creation->set_stats(stats);
            write("Enter skill name to set or type done: ");
            break;
        case 2:
            if (str == "done" || !strlen(str))
            {
                counter++;
                write("Enter gender(m/f/n): ");
                break;
            }
            skill = query_sk_list();
            if (member_array(str, m_indexes(skill)) == -1)
            {
                write("Invalid skill. Enter skill name to set " +
                    "or type done: ");
                input_to(event_npc);
                return 1;
            }
            write("Enter value for that skill(1-100): ");
            break;
        case 3:
            if (!strlen(str))
            {
                write("Enter value for that skill(1-100): ");
                input_to(event_npc);
                return 1;
            }
            val = sscanf(str, "%d", num);
            if (!val)
            {
                write("Enter value for that skill(1-100): ");
                input_to(event_npc);
                return 1;
            }
            creation->set_skill(skill, num);
            counter--;
            write("Enter numeric skill to set or type done: ");
            input_to(event_npc);
            return 1;
        case 4:
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
        case 5:
            if (!strlen(str))
            {
                write("Enter race(hobbit, elf, goblin, etc.): ");
                input_to(event_npc);
                return 1;
            }
            creation->set_race_name(str);
            write("Enter title (the Great Champion of the Land): ");
            break;
        case 6:
            if (!strlen(str))
            {
                write("Enter title (the Great Champion of the Land): ");
                input_to(event_npc);
                return 1;
            }
            creation->set_title(str);
            event_done();
            return 1;
    }

    counter++;
    input_to(event_npc);
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
event_std(string str)
{
    int val, num;
    string fail = event_parsing(str);

    if (stringp(fail))
    {
        notify_fail(fail);
        return 0;
    }

    switch(counter)
    {
        case 0:
            if (str == "done" || !strlen(str))
            {
                write("Enter short description: ");
                break;
            }
            str = lower_case(str);
            creation->add_name(str);
            write("Enter additional name or type done: ");
            input_to(event_std);
            return 1;
        case 1:
            if (!strlen(str))
            {
                write("Enter short description: ");
                input_to(event_std);
                return 1;
            }
            creation->set_short(str);
            write("Enter plural name, or hit return to use default: ");
            break;
        case 2:
            if (stringp(str))
            {
                creation->set_pname(str);
            }
            write("Enter plural short, or hit return to use default: ");
            break;
        case 3:
            if (stringp(str))
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
            write("Enter adjective to add or type done: ");
            break;
        case 5:
            if (str == "done" || !strlen(str))
            {
                write("Enter prop to add or type done. (_obj_i_value" +
                    "//_heap_i_unit_weight): ");
                break;
            }

            creation->add_adj(str);
            write("Enter adjective to add or type done: ");
            input_to(event_std);
            return 1;
        case 6:
            if (str == "done" || !strlen(str))
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
            write("Enter prop to add or type done. (_obj_i_value" +
                "//_heap_i_unit_weight): ");
            input_to(event_std);
            return 1;
    }

    counter++;
    input_to(event_std);
}

private int
event_echo(string str)
{
    int i, sz;
    object player, *env = ({});

    if (!strlen(str))
    {
        write("Enter string to tell: " + implode(group, ", ") + " or " +
            "type ~q: ");
        input_to(event_echo);
        return 1;
    }
    if (str == "~q")
    {
        write("Aborting tell.\n");
        return 1;
    }
    if (!sizeof(group))
    {
        write("Group is empty. Aborting tell.\n");
        return 1;
    }

    i = -1;
    sz = sizeof(group);
    while(++i < sz)
    {
        player = find_player(group[i]);
        if (!objectp(player) || !interactive(player))
        {
            write(capitalize(group[i]) + " is either gone or linkdead.\n");
        }
        else if (member_array(environment(player), env) == -1)
        {
            env += ({ environment(player) });
        }
    }

    i = -1;
    sz = sizeof(env);
    while(++i < sz)
    {
        write("Echo " + str + " sent to " + file_name(env[i]) + ".\n");
        tell_room(env[i], str + "\n");
    }

    return 1;

}

private int
event_tell(string str)
{
    int i, sz;
    object player;

    if (!strlen(str))
    {
        write("Enter string to tell: " + implode(group, ", ") + " or " +
            "type ~q: ");
        input_to(event_tell);
        return 1;
    }
    if (str == "~q")
    {
        write("Aborting tell.\n");
        return 1;
    }
    if (!sizeof(group))
    {
        write("Group is empty. Aborting tell.\n");
        return 1;
    }

    i = -1;
    sz = sizeof(group);
    while(++i < sz)
    {
        player = find_player(group[i]);
        if (!objectp(player) || !interactive(player))
        {
            write(capitalize(group[i]) + " is either gone or linkdead.\n");
        }
        else
        {
            write("Message sent to: " + group[i] + "\n");
            tell_object(player, "A little voice in your head whispers:\n" +
                str + "\n");
        }
    }

    return 1;
}

private int
event_group(string str)
{
    int i, sz;
    object player;
    string str0, str1, str2;

    if (!strlen(str))
    {
        if (!sizeof(group))
        {
            write("Group is currently empty.\n");
            return 1;
        }
        else
        {
            write("Group consists of:\n" + implode(group, "\n") + "\n");
            return 1;
        }
    }

    str = lower_case(str);

    sscanf(str, "%s", str0);
    i = sscanf(str0, "%s %s", str1, str2);
    if (i > 2)
    {
        if (i < 1)
        {
            write("Wrong number of arguments.\nEnter '<name>' to add, " +
                "'remove <name>' or hit return to finish: ");
            input_to(event_group);
            return 1;
        }
    }

    if (str1 == "remove")
    {
        if (member_array(str2, group))
        {
            write(capitalize(str2) + " is not in the group.\n" +
            "Enter '<name>' to add, 'remove <name>' or hit return to finish: ");
            input_to(event_group);
            return 1;
        }

        group -= ({ str2 });

        write(capitalize(str2) + " removed, another name?\nEnter 'add " +
            "<name>', 'remove <name>' or hit return to finish: ");
        input_to(event_group);
        return 1;
    }
    else
    {
        player = find_player(str0);
        if (!objectp(player))
        {
            write("Player not present.\nEnter '<name>' to add, " +
                "'remove <name>' or hit return to finish: ");
            input_to(event_group);
            return 1;
        }
        if (member_array(str0, group) != -1)
        {
            write("Player already in the group.\nEnter '<name>' to add, " +
                "'remove <name>' or hit return to finish: ");
                input_to(event_group);
                return 1;
        }
        group += ({ str0 });
        
        write(capitalize(str0) + " added, another name?\nEnter 'add " +
            "<name>', 'remove <name>' or hit return to finish: ");
        input_to(event_group);
        return 1;
    }
}

private int
event_exp(string str)
{
    int x, com, gen, quest, i, sz;

    if (!strlen(str))
    {
        notify_fail("Enter experience to reward (combat general quest):");
        input_to(event_exp);
        return 1;
    }

    if (str == "~q")
    {
        write("Aborting reward. No experience given.\n");
        return 1;
    }

    x = sscanf(str, "%d %d %d", com, gen, quest);

    if (x != 3)
    {
        write("Enter reward (combat general quest) 0 values are valid: ");
        input_to(event_exp);
        return 1;
    }

    if (com > 0)
    {
        i = -1;
        sz = sizeof(person);
        while(++i < sz)
        {
            person[i]->add_exp_combat(com);
        }
    }
    if (gen > 0)
    {
        i = -1;
        sz = sizeof(person);
        while(++i < sz)
        {
            person[i]->add_exp_general(gen);
        }
    }
    if (quest > 0)
    {
        i = -1;
        sz = sizeof(person);
        while(++i < sz)
        {
            person[i]->add_exp_quest(quest);
        }
    }

    if (silent)
    {
        i = -1;
        sz = sizeof(person);
        while(++i < sz)
        {
            tell_object(person[i], "You feel more experienced.\n");
        }
    }
    else
    {
        i = -1;
        sz = sizeof(person);
        while(++i < sz)
        {
            tell_room(environment(this_player()), QCTNAME(this_player()) +
                " waves " + this_player()->query_possessive() +
                " magic wand at " + QTNAME(person[i]) + ".\n",
                ({person[i], this_player()}));
            tell_object(person[i], this_player()->query_The_name(person[i]) +
                " waves " + this_player()->query_possessive() + " magic " +
                "wand at you.\nYou feel more experienced.\n");
        }
    }

    i = -1;
    sz = sizeof(person);
    while(++i < sz)
    {
        write("You wave your magic wand and reward " +
            person[i]->query_name() + " with " +
            com + " combat experience, " + gen + " general experience and " +
            quest + " quest experience.\n");

        write_file(REWARDLOG, ctime(time()) + ": " +
            this_interactive()->query_name() + " awarded " +
            com + " combat, " + gen + " general and " + quest + " quest " +
            "experience to " + person[i]->query_name() + ".\n");
    }
    return 1;
}

private int
event_reward(string str)
{
    int i, sz;
    object player;

    if (!strlen(str) && !sizeof(person))
    {
        write("Enter player to reward or ~q to abort: ");
        input_to(event_reward);
        return 1;
    }
    if (!strlen(str))
    {
        write("Enter experience to reward (combat general quest): ");
        input_to(event_exp);
        return 1;
    }

    if (str == "~q")
    {
        write("Aborting reward.\n");
        return 1;
    }

    if (str == "group" && sizeof(group) > 0)
    {
        sz = sizeof(group);
        i = -1;

        while(++i < sz)
        {
            write(group[i] + "\n");
            player = find_player(group[i]);
            if (objectp(player))
            {
                person += ({ player });
                write(capitalize(group[i]) + " present.\n");
            }
            else
            {
                write(capitalize(group[i]) + " not present.\n");
            }
        }

        write("Enter additional players to reward or hit return: ");
        input_to(event_reward);
        return 1;
    }

    str = lower_case(str);
    player = find_player(str);

    if (!objectp(player))
    {
        write("No such player in the realms. Enter player name or " +
            "~q to abort: ");
        input_to(event_reward);
        return 1;
    }

    person += ({ player });
    
    write("Enter the name of the next player to reward or hit return: ");
    input_to(event_reward);
    return 1;
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

    switch(str)
    {
        case "~q":
            write("Aborting creation.\n");
            return 1;
        case "silent reward":
            silent = 1;
            person = ({});
            write("Enter the name of the first player to reward or 'group' " +
                "to reward previously set group: ");
            input_to(event_reward);
            return 1;
        case "reward":
            silent = 0;
            person = ({});
            write("Enter the name of the first player to reward or 'group' " +
                "to reward previously set group: ");
            input_to(event_reward);
            return 1;
        case "group":
            write("Enter '<name>' to add, 'remove <name>' or hit return to " +
                "finish: ");
            input_to(event_group);
            return 1;
        case "tell":
            write("Enter string to tell " + implode(group, ", ") + ": ");
            input_to(event_tell);
            return 1;
        case "echo":
            write("Enter string to echo to " + implode(group, ", ") + ": ");
            input_to(event_echo);
            return 1;
        case "default":
            break;
    }

    if (member_array(str, EVENTLIST) != -1)
    {
        creation = clone_object(EVENTOBJ + str);
        type = str;
        write("Enter the name: ");
        input_to(event_std);
        return 1;
    }

    write("Invalid option. Type ~q to quit." + implode(EVENTLIST, "\n\t") +
        "\nEnter option: ");
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
        write("Create a temporary object or npc for an event, " +
            "give a reward, modify a group, or send messages to a " +
            "group:\n\n" +
            "    event               - start creating\n" + 
            "    event armour        - create a basic armour\n" +
            "    event drink         - create a basic drink\n" +
            "    event echo          - send an echo to the group's room\n" +
            "    event food          - create a basic food\n" +
            "    event group         - add/remove group members\n" +
            "    event npc           - create a basic npc\n" +
            "    event object        - create a basic object\n" +
            "    event reward        - reward a player with experience\n" +
            "    event silent reward - reward a player silently\n" +
            "    event tell          - tell the event group something\n" +
            "    event weapon        - create a basic weapon\n" +
            "    To quit at any time, type ~q.\n" + 
            "    Arguments are optional.\n\n");
        return 1;
    }

    if (!strlen(str))
    {
        write("Type ~q to quit at any time " + implode(EVENTLIST, "\n\t") +
            "Enter option: ");
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
