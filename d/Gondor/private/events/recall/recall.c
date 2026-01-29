/*
 * /d/Gondor/private/events/special_obj/recall.c
 *
 * Allows copying of relevant data to individual files to create
 * objects in the future, specifically for use with the event
 * tool to make event running easier.
 *
 * Coded by Gwyneth, October 22, 2000
 */

inherit "/std/object";

#include <cmdparse.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../events.h"

/* Global Variable */
string *temp_arr;

public void
create_object()
{
    set_name("charm");

    set_short("shiny charm");

    set_long("This can be used to imprint details of various " +
        "objects and npcs in existance, and to recall them later. " +
        "The words, \"help " +
        "recall\" have been etched into the charm.\n");
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
    else if (member_array(capitalize(dest->query_real_name()),
      AUTHORIZED) == -1)
    {
        remove_object();
    }
}

public void
imp_menu()
{
    write("To imprint the details of an item/npc for future use, " +
        "'imprint <item/npc> <identifier>', where identifier " +
        "is the name to store the item/npc under.\nTo recall " +
        "an item/npc use, 'recall <identifier>'.\n");
    return;
}

private void
imp_std(object obj)
{
    string *var_arr, *names, ldesc; 

    names = obj->query_names();
    names -= ({ OB_NAME(obj) });

    var_arr = ({ implode(names, ",") });
    var_arr += ({ obj->short() });

    names = obj->query_pnames();
    names -= ({ OB_NAME(obj) + "s" });

    var_arr += ({ implode(names, ",") });
    if (!strlen(obj->plural_short()))
    {
        var_arr += ({ "" });
    }
    else
    {
        var_arr += ({ obj->plural_short() });
    }
    ldesc = obj->query_long();
    if (stringp(ldesc))
    {
        ldesc = extract(ldesc, 0, strlen(ldesc) -2);
    }
    else
    {
        ldesc = obj->long();
    }

    var_arr += ({ ldesc });
    var_arr += ({ implode(obj->query_adjs(), ",") });

    temp_arr = var_arr;
    return;
}

private void
rec_std(object obj, string *var_arr)
{
    string *names;
    names = explode(var_arr[1], ",");
    obj->set_name(names);
    obj->set_short(var_arr[2]);
    names = explode(var_arr[3], ",");
    obj->set_pname(names);
    if (strlen(var_arr[4]))
    {
        obj->set_pshort(var_arr[4]);
    }
    else
    {
        obj->set_pshort(var_arr[2] + "s");
    }
    obj->set_long(var_arr[5] + "\n");
    names = explode(var_arr[6], ",");
    obj->set_adj(names);
    return;
}

private int
imp_arm(object obj, string ident)
{
    string *var_arr = ({"armour"});

    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }
    
    imp_std(obj);
    var_arr += temp_arr;
    var_arr += ({ (obj->query_prop(OBJ_I_VALUE) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_WEIGHT) + "") });
    var_arr += ({ (obj->query_ac() + "") });
    var_arr += ({ (obj->query_likely_break() + "") });
    var_arr += ({ (obj->query_at() + "") });

    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_arm(string *var_arr)
{
    object obj = clone_object(EVENTOBJ + "armour");

    rec_std(obj, var_arr);
    obj->add_prop(OBJ_I_VALUE, atoi(var_arr[7]));
    obj->add_prop(OBJ_I_VOLUME, atoi(var_arr[8]));
    obj->add_prop(OBJ_I_WEIGHT, atoi(var_arr[9]));
    obj->set_ac(atoi(var_arr[10]));
    obj->set_likely_break(atoi(var_arr[11]));
    obj->set_at(atoi(var_arr[12]));

    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(this_player(), 1);
    return;
}

private int
imp_drink(object obj, string ident)
{
    string *var_arr = ({"drink"});

    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }
    
    imp_std(obj);
    var_arr += temp_arr;
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_VALUE) + "") });
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_WEIGHT) + "") });
    var_arr += ({ (obj->query_alco_amount() + "") });
    var_arr += ({ (obj->query_soft_amount() + "") });
    var_arr += ({ obj->query_prop(HEAP_S_UNIQUE_ID) });

    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_drink(string *var_arr)
{
    object obj = clone_object(EVENTOBJ + "drink");

    rec_std(obj, var_arr);
    obj->add_prop(HEAP_I_UNIT_VALUE, atoi(var_arr[7]));
    obj->add_prop(HEAP_I_UNIT_VOLUME, atoi(var_arr[8]));
    obj->add_prop(HEAP_I_UNIT_WEIGHT, atoi(var_arr[9]));
    obj->set_alco_amount(atoi(var_arr[10]));
    obj->set_soft_amount(atoi(var_arr[11]));
    obj->add_prop(HEAP_S_UNIQUE_ID, var_arr[12]);

    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(this_player(), 1);
    return;
}

private int
imp_food(object obj, string ident)
{
    string *var_arr = ({"food"});

    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }

    imp_std(obj);
    var_arr += temp_arr;
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_VALUE) + "") });
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(HEAP_I_UNIT_WEIGHT) + "") });
    var_arr += ({ (obj->query_amount() + "") });
    var_arr += ({ obj->query_prop(HEAP_S_UNIQUE_ID) });

    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_food(string *var_arr)
{
    object obj = clone_object(EVENTOBJ + "food");

    rec_std(obj, var_arr);
    obj->add_prop(HEAP_I_UNIT_VALUE, atoi(var_arr[7]));
    obj->add_prop(HEAP_I_UNIT_VOLUME, atoi(var_arr[8]));
    obj->add_prop(HEAP_I_UNIT_WEIGHT, atoi(var_arr[9]));
    obj->set_amount(atoi(var_arr[10]));
    obj->add_prop(HEAP_S_UNIQUE_ID, var_arr[11]);

    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(this_player(), 1);
    return;
}

private int
imp_npc(object obj, string ident)
{
    string *var_arr = ({"npc"}), *names, ldesc;

    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }
    
    names = obj->query_names();
    names -= ({ OB_NAME(obj) });

    var_arr += ({ implode(names, ",") });

    names = obj->query_pnames();
    names -= ({ OB_NAME(obj) + "s" });

    var_arr += ({ implode(names, ",") });
    ldesc = obj->query_long();
    if (stringp(ldesc))
    {
        ldesc = extract(ldesc, 0, strlen(ldesc) -2);
    }
    else
    {
        ldesc = obj->long();
    }
    var_arr += ({ ldesc });
    var_arr += ({ implode(obj->query_adjs(), ",") });
    var_arr += ({ (obj->query_prop(CONT_I_HEIGHT) + "") });
    var_arr += ({ (obj->query_prop(CONT_I_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(CONT_I_WEIGHT) + "") });
    var_arr += ({ (obj->query_alignment() + "") });
    var_arr += ({ (obj->intro_status() + "") });
    var_arr += ({ (obj->query_gender() + "") });
    var_arr += ({ obj->query_race_name() });
    var_arr += ({ obj->query_title() });
    var_arr += ({ obj->query_name() });
    var_arr += ({ (obj->query_skill(SS_DEFENCE) + "") });
    var_arr += ({ (obj->query_skill(SS_SNEAK) + "") });
    var_arr += ({ (obj->query_skill(SS_SPELLCRAFT) + "") });
    var_arr += ({ (obj->query_skill(SS_SWIM) + "") });
    var_arr += ({ (obj->query_stat(SS_STR) + "") });
    var_arr += ({ (obj->query_stat(SS_DEX) + "") });
    var_arr += ({ (obj->query_stat(SS_CON) + "") });
    var_arr += ({ (obj->query_stat(SS_INT) + "") });
    var_arr += ({ (obj->query_stat(SS_WIS) + "") });
    var_arr += ({ (obj->query_stat(SS_DIS) + "") });
    
    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_npc(string *var_arr)
{
    int i, size, level, *stat_arr = ({});
    object obj = clone_object(EVENTOBJ + "npc");
    string *names;

    names = explode(var_arr[1], ",");
    obj->set_name(names);
    names = explode(var_arr[2], ",");
    obj->set_pname(names);
    obj->set_long(var_arr[3] + "\n");
    names = explode(var_arr[4], ",");
    obj->set_adj(names);
    obj->add_prop(CONT_I_HEIGHT, atoi(var_arr[5]));
    obj->add_prop(CONT_I_VOLUME, atoi(var_arr[6]));
    obj->add_prop(CONT_I_WEIGHT, atoi(var_arr[7]));
    obj->set_alignment(atoi(var_arr[8]));
    obj->set_intro(atoi(var_arr[9]));
    obj->set_gender(atoi(var_arr[10]));
    obj->set_race_name(var_arr[11]);
    obj->set_title(var_arr[12]);
    if (SECURITY->exist_player(capitalize(var_arr[13])))
    {
        write("WARNING! You have chosen a name that already " +
            "belongs to a player!\nProceeding anyways.\n");
    }
    if (SECURITY->query_banished(var_arr[13]))
    {
        write("WARNING! You have chosen a name that has been " +
            "banished by another wizard.\nProceeding anyways.\n");
    }
    obj->living_name(lower_case(var_arr[13]));
    i = -1;
    size = sizeof(FIGHTING);
    level = atoi(var_arr[14]);
    while(++i < size)
    {
        
        obj->set_skill(FIGHTING[i], level);
    }
    
    i = -1;
    size = sizeof(THIEF);
    level = atoi(var_arr[15]);
    while(++i < size)
    {
        obj->set_skill(THIEF[i], level);
    }
    
    i = -1;
    size = sizeof(MAGIC);
    level = atoi(var_arr[16]);
    while(++i < size)
    {
        obj->set_skill(MAGIC[i], level);
    }

    i = -1;
    size = sizeof(GENERAL);
    level = atoi(var_arr[17]);
    while(++i < size)
    {
        obj->set_skill(GENERAL[i], level);
    }

    for(i = 18; i < 24; i++)
    {
        stat_arr += ({ atoi(var_arr[i]) });
    }
    obj->set_stats(stat_arr);
    obj->refresh_living();
    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(environment(this_player()), 1);
    return;
}

private int
imp_wep(object obj, string ident)
{
    string *var_arr = ({"weapon"});

    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }

    imp_std(obj);
    var_arr += temp_arr;
    var_arr += ({ (obj->query_prop(OBJ_I_VALUE) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_WEIGHT) + "") });
    var_arr += ({ (obj->query_hit() + "") });
    var_arr += ({ (obj->query_pen() + "") });
    var_arr += ({ (obj->query_likely_break() + "") });
    var_arr += ({ (obj->query_wt() + "")});
    var_arr += ({ (obj->query_hands() + "")});
    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_wep(string *var_arr)
{
    object obj = clone_object(EVENTOBJ + "weapon");

    rec_std(obj, var_arr);
    obj->add_prop(OBJ_I_VALUE, atoi(var_arr[7]));
    obj->add_prop(OBJ_I_VOLUME, atoi(var_arr[8]));
    obj->add_prop(OBJ_I_WEIGHT, atoi(var_arr[9]));
    obj->set_hit(atoi(var_arr[10]));
    obj->set_pen(atoi(var_arr[11]));
    obj->set_likely_break(atoi(var_arr[12]));
    obj->set_wt(atoi(var_arr[13]));
    obj->set_hands(atoi(var_arr[14]));
    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(this_player(), 1);
    return;
}

private int
imp_obj(object obj, string ident)
{
    string *var_arr = ({"object"});
    
    if (!objectp(obj))
    {
        notify_fail("Unexpected loss of object. Aborting.\n");
        return 0;
    }

    imp_std(obj);
    var_arr += temp_arr;
    var_arr += ({ (obj->query_prop(OBJ_I_VALUE) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_VOLUME) + "") });
    var_arr += ({ (obj->query_prop(OBJ_I_WEIGHT) + "") });

    setuid();
    seteuid(getuid());
    write_file(EVENTREC + ident, implode(var_arr, "::"));  

    return 1;
}

private void
rec_obj(string *var_arr)
{
    object obj = clone_object(EVENTOBJ + "object");

    rec_std(obj, var_arr);
    obj->add_prop(OBJ_I_VALUE, atoi(var_arr[7]));
    obj->add_prop(OBJ_I_VOLUME, atoi(var_arr[8]));
    obj->add_prop(OBJ_I_WEIGHT, atoi(var_arr[9]));

    write("You recreate a " + obj->query_name() + ".\n");
    obj->move(this_player(), 1);
}

private int
imprint(string str)
{
    mixed *ob;
    object obj;
    string ident;

    str = lower_case(str);
    
    if (!strlen(str) || str == "help")
    {
        imp_menu();
        return 1;
    }

    if (!parse_command(str,
      environment(this_player()), "%i %s",
      ob, ident))
    {
        notify_fail("Imprint <object> <identifier>?\n");
        return 0;
    }

    if (!strlen(ident))
    {
        notify_fail("Please choose an identifier: Imprint <object>" +
            " <identifier>.\n");
        return 0;
    }

    if (file_size(EVENTREC + ident) > 0)
    {
        notify_fail("File " + EVENTREC + ident + " exists. Delete " +
            EVENTREC + ident + " or use a different identifier.\n");
        return 0;
    }
    
    ob = NORMAL_ACCESS(ob, 0, 0);

    if (sizeof(ob) > 1)
    {
        notify_fail("Select only one thing at a time to imprint.\n");
        return 0;
    }

    if (!sizeof(ob))
    {
        notify_fail("Imprint <object> <identifier>?\n");
        return 0;
    }

    obj = ob[0];

    if (IS_ARMOUR_OBJECT(obj))
    {
        write("Imprinting armour: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_arm(obj, ident);
        return 1;
    }
    else if (IS_DRINK_OBJECT(obj))
    {
        write("Imprinting drink: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_drink(obj, ident);
        return 1;
    }
    else if (IS_FOOD_OBJECT(obj))
    {
        write("Imprinting food: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_food(obj, ident);
        return 1;
    }
    else if (living(obj))
    {
        write("Imprinting living: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_npc(obj, ident);
        return 1;
    }
    else if (IS_WEAPON_OBJECT(obj))
    {
        write("Imprinting weapon: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_wep(obj, ident);
        return 1;
    }
    else
    {
        write("Imprinting object: " + obj->query_name() + " to " +
            EVENTREC + ident + ".\n");
        write("Use recall " + ident + " to recreate the item.\n");
        imp_obj(obj, ident);
        return 1;
    }
}

private int
recall(string str)
{
    string *var_arr;

    if (!strlen(str) || str == "help")
    {
        imp_menu();
        return 1;
    }

    str = lower_case(str);
    str = EVENTREC + str;

    if (file_size(str) < 1)
    {
        notify_fail("Non-existant file: " + str + ".\n");
        return 0;
    }

    var_arr = explode(read_file(str), "::");
    dump_array(var_arr);

    switch(var_arr[0])
    {
    case "armour":
        if (sizeof(var_arr) != 13)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_arm(var_arr);
        break;
    case "drink":
        if (sizeof(var_arr) != 13)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_drink(var_arr);
        break;
    case "food":
        if (sizeof(var_arr) != 12)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_food(var_arr);
        break;
    case "npc":
        if (sizeof(var_arr) != 24)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_npc(var_arr);
        break;
    case "weapon":
        if (sizeof(var_arr) != 15)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_wep(var_arr);
        break;
    default:
        if (sizeof(var_arr) != 10)
        {
            notify_fail("Wrong number of variables in " + str + 
                ", aborting.\n");
            return 0;
        }

        rec_obj(var_arr);
        break;
    }

    return 1;
}

private int
help(string str)
{
    if (str == "recall" || str == "imprint")
    {
        imp_menu();
        return 1;
    }
    else
    {
        return 0;
    }
}

public void
init()
{
    ::init();

    add_action(imprint, "imprint");
    add_action(recall, "recall");
    add_action(help, "help");
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
