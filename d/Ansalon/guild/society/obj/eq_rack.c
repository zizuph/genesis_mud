/* 
 * /d/Ansalon/guild/society/obj/eq_rack.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Saving Equipment Rack that keeps tallies of equipment left
 * to avoid over-selfish members.
 *
 * Gwyneth, July 1999 
 *
 * Modified 2021-06-03 by Carnak:
 *  - Made broken items free to remove from the racks.
 */
inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h"

#define RESET_TIME  1209600
#define NON_GLOWING (KGOBJ + "neq_rack.c")

static int recovering; 
static int gAlarm = 0;
static int gShdwnAlarm = 0;

/* example: ([ "gwyneth" : ({1014418296, 1, "silver-tipped ironwood hoopak",
 *             1014418362, 0, blue face mask,}), "kessie" : ({1014418447, 0
 *             "pair of silvery bracers"}) ])
 *             
 *             ([ name : ({ time, glowing/non, short desc }) ])
 */
mapping gCheckedOut = ([]);

void rack_alarm();
void save_rack();

void
create_container()
{
    set_name("rack");
    add_name("glowing_rack");
    set_adj("cherry");
    add_adj("wood");
    set_short("cherry wood rack");
    set_long("This is a rack where members can place their equipment for " + 
        "use by other members. You can 'list borrowed things' to see who " +
	"hasn't returned their equipment and when. The word 'Sort' has " +
	"been carved into the side.\nIt glows with a faint gold aura.\n");

    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The cherry wood rack is bolted to the floor.\n");

    seteuid(getuid());
    restore_object(MASTER);

    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());    
}

int
sort_inv(string arg)
{
    object *all_eq, nrack = present("non_glowing_rack", environment());
    string sall;
    int i, s, glowing, nonglowing;

    if(!nrack)
    {
        setuid();
        seteuid(getuid());
        clone_object(NON_GLOWING)->move(environment());
        nrack = present("non_glowing_rack", environment());
    }

    if (!strlen(arg))
    {
        notify_fail("Sort what?\n"); 
        return 0;  
    }

    arg = lower_case(arg); 

    if (!parse_command(arg, all_inventory(this_player()), "[the] %i", all_eq))
    {
        notify_fail("Sort what?\n"); 
        return 0; 
    }

    all_eq = NORMAL_ACCESS(all_eq, 0, 0);
    s = sizeof(all_eq);

    if (!s)
    {
        notify_fail("Sort what?\n"); 
        return 0;
    }

    for (i = 0; i < s; i++)
    {
        sall = all_eq[i]->short();

        if ((!all_eq[i]->query_prop(OBJ_M_NO_DROP)) && 
          (!all_eq[i]->id("coin")) &&
          (!all_eq[i]->query_prop(OBJ_M_NO_SELL)) &&
          (!all_eq[i]->query_prop(OBJ_I_INVIS)) &&
          (!all_eq[i]->query_prop(OBJ_I_BROKEN)))
        {
            if(all_eq[i]->check_recoverable())
            {
                all_eq[i]->move(this_object());
                write("You place a " + sall + " in the cherry rack.\n");
                say(QCTNAME(this_player()) + " places a " + sall + 
                    " in the cherry rack.\n");
                glowing = 1;
            }
            else
            {
                all_eq[i]->move(nrack);
                write("You place a " + sall + " in the pecan rack.\n");
                say(QCTNAME(this_player()) + " places a " + sall + 
                    " in the pecan rack.\n");
                nonglowing = 1;
            }
        }
    }

    if (glowing)
    {
        write("You put the longest lasting equipment in the cherry rack.\n");
        say(QCTNAME(this_player()) + " puts the longest lasting equipment " +
            "in the cherry rack.\n");
    }
    if (nonglowing)
    {
        write("You put the equipment that won't last so long in " +
            "the pecan rack.\n");
        say(QCTNAME(this_player()) + " puts the equipment that won't last " +
            "so long in the pecan rack.\n");
    }
    if (!glowing && !nonglowing)
    {
        notify_fail("You can't sort those items\n");
        return 0;
    }

    return 1;
}

/* Function name: rack_alarm
 * Description  : save_object is a big bottleneck in the game, let's
 *                not save_object every time a piece of equipment comes
 *                in. A 10 minute alarm is sufficient.
 */
void
rack_alarm()
{
    int delay;

    if (SECURITY->query_uptime_limit() > 600 && 
      !ARMAGEDDON->shutdown_active())
    {
        /* It's not armageddon and there are more than 10 minutes in
           the game left. There is no alarm set, set an alarm to save
           the racks in 10 minutes. */
        if (!gAlarm)
            gAlarm = set_alarm(600.0, 0.0, &save_rack());

        /* Alarm is already set, don't worry about it. */
        return;
    }

    remove_alarm(gAlarm);

    /* How much longer until shutdown? */
    delay = ARMAGEDDON->query_delay();

    /* There is no shutdown alarm and there is more than 3 seconds left.
       Set an alarm to save the racks 3 seconds before shutdown. */
    if (!gShdwnAlarm && delay > 3)
        gShdwnAlarm = set_alarm(itof(delay) - 3.0, 0.0, &save_rack());
    /* Shutdown is 3 seconds or less. Don't bother with an alarm. */
    else if (delay <= 3)
        save_object(MASTER);
}

/* Function name: save_rack
 * Description  : called by alarm to write to the file.
 */
void
save_rack()
{
    save_object(MASTER);
    gAlarm = 0;
}

void
rack_get(object ob, string name, string equip)
{
    write("You hear a gnomish voice in the air around you say, " +
        "'" + name + ", you sticky fingered kender! I won't let you borrow " + 
        "more than you've left!'\n" +
        "The " + equip + " is taken ahold of by invisible hands and " +
        "placed back into the rack.\n");
    say("You hear a gnomish voice in the air around you say, " +
        "'" + name + ", you sticky-fingered kender! I won't let you borrow " + 
        "more than you've left'!\n" +
        "The " + equip + " is taken ahold of by invisible hands and " +
        "placed back into the rack.\n");
    ob->move(this_object());
}

int
list_checked_out(string str)
{
    int i, j, size, size2;
    string *names, glowing;

    if (!strlen(str))
    {
        notify_fail("List borrowed equipment?\n");
	return 0;
    }

    if (!parse_command(str, ({}),
      " 'checked' / 'borrowed' [out] 'items' / 'equipment' / 'things' "))
    {
        notify_fail("List borrowed equipment?\n");
	return 0;
    }

    if (sizeof(m_indexes(gCheckedOut)) < 1)
        write("There is nothing borrowed right now.\n");
    else
    {
	names = m_indexes(gCheckedOut);
        write("Here is a list of the more valuable items borrowed:\n");

	for (i = 0, size = sizeof(names); i < size; i++)
	{
	    write(names[i] + " has borrowed these items:\n");
	    for (j = 2, size2 = sizeof(gCheckedOut[names[i]]); j < size2; j +=3) 
	    {
                glowing = (gCheckedOut[names[i]][j-1] ? "(glowing)" : 
                    "(non-glowing)");
		write("   " + gCheckedOut[names[i]][j] + glowing + 
                    " borrowed on " + 
                    extract(ctime(gCheckedOut[names[i]][j-2]), 4, 15) + ".\n");
	    }

	    write("\n");
	}
    }

    return 1;
}

void
add_checked_out(string name, string ob_name, int recover)
{
    string *equip_array;

    if (!strlen(name) || !strlen(ob_name))
        return;

    equip_array = explode(ob_name, " ");
    if (equip_array[0] == "gold" && equip_array[1] == "coated")
    {
        equip_array = equip_array[2..sizeof(equip_array) - 1];
        ob_name = implode(equip_array, " ");
    }

    if (member_array(name, m_indexes(gCheckedOut)) != -1)
        gCheckedOut[name] += ({ time(), recover, ob_name });
    else
        gCheckedOut += ([ name : ({ time(), recover, ob_name }) ]);

    rack_alarm();
    return;
}

varargs void
remove_checked_out(string name, string ob_name, int glowing = 1)
{
    int i, size, position = -1, end, new_end;

    if (!strlen(name) || !strlen(ob_name))
        return;

    if (!m_sizeof(gCheckedOut))
        return;

    if (!sizeof(gCheckedOut[name]))
        return;

    end = sizeof(gCheckedOut[name]) - 1;

    if (glowing)
    {
        for (i = 2, size = sizeof(gCheckedOut[name]); i < size; i += 3)
        {
            if (gCheckedOut[name][i] == ob_name && gCheckedOut[name][i-1] == 1)
            {
                position = i;
                break;
            }
        }
    }

    if (sizeof(gCheckedOut[name]) > 3)
    {
        /* Has a glowing object been found? If not, find the non-glowing */
        if (position == -1)
            position = member_array(ob_name, gCheckedOut[name]);

	switch(position)
	{
	case -1:
            /* Still no object found. */
	    return;
	case 0:
        case 1:
	    /* Should never be 0 or 1, but just in case...Otherwise, it'd
               mess up the arrays even more. */
            return;
	case 2:
	    gCheckedOut[name] = gCheckedOut[name][3..end];
	    break;
        default:
            if (position > end || position < 0)
		return;

	    if (position == end)
            {
                new_end = end - 3;
                gCheckedOut[name] = gCheckedOut[name][0..new_end];
                break;
            }
            else
            {
                gCheckedOut[name] = gCheckedOut[name][0..position - 3] +
		    gCheckedOut[name][position + 1..end];
            }
	    break;
        }
    }
    else
        gCheckedOut = m_delete(gCheckedOut, name);

    rack_alarm();
    return;
}

void
remove_non_glowing()
{
    int i, size, j, size2;
    string *names;

    names = m_indexes(gCheckedOut);
    for (i = 0, size = sizeof(names); i < size; i++)
    {
        for (j = sizeof(gCheckedOut[names[i]]) - 2; j > 0; j -= 3)
        {
            if (gCheckedOut[names[i]][j] == 0)
	    {
                remove_checked_out(names[i], gCheckedOut[names[i]][j+1], 0);
	    }
	    else if ((gCheckedOut[names[i]][j-1] + RESET_TIME) < time())
		    remove_checked_out(names[i], gCheckedOut[names[i]][j+1]);
	}
    }

    rack_alarm();
    return;
}

void
leave_racks(object ob, object to)
{
    int new_value;
    string name, equip;

    name = capitalize(to->query_real_name()); 
    equip = ob->short(); 

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
    {
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());

        if (ob->query_std_hoopak())
            equip = "altered hoopak(" + ob->query_former_short() + ")";

        if (new_value > 800 || ob->id("hoopak") ||
          ob->query_prop(MAGIC_AM_MAGIC))
            add_checked_out(name, equip, ob->check_recoverable());
    }
    /* Calculate values for armours depending on its ac. */
    else if (function_exists("create_armour", ob))
    {
        new_value = F_VALUE_ARMOUR(ob->query_ac());

        if (new_value > 200 || ob->query_prop(MAGIC_AM_MAGIC))
            add_checked_out(name, equip, ob->check_recoverable());
    }
    /* Not a weapon or armour, but it's magic. */
    else if (ob->query_prop(MAGIC_AM_MAGIC))
    {
        add_checked_out(name, equip, ob->check_recoverable());
    }
}

void
leave_inv(object ob, object to)
{
    int skill, new_value = 0;
    string name, equip;

    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);

    if (!interactive(to) || ob->query_prop(OBJ_I_BROKEN))
        return;

    leave_racks(ob, to);

    name = capitalize(to->query_real_name()); 
    equip = ob->short(); 

    if (function_exists("create_weapon", ob))
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());
    else if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* Tally depending on what has been put into and taken out of the rack. */
    skill = to->query_skill(SS_RACK_TALLY);
    
    /* If it's not armageddon, and the borrower doesn't have
       enough in his tally, he can't borrow anything. */
    if (!ARMAGEDDON->shutdown_active() && skill < new_value)
        set_alarm(0.1, 0.0, &rack_get(ob, name, equip));

    /* If it's not armageddon, decrease the tally by the calculated
       value of an object. */
    if (!(ARMAGEDDON->shutdown_active()))
        to->set_skill(SS_RACK_TALLY, to->query_base_skill(SS_RACK_TALLY) -
            new_value);

    return;
}

void
enter_racks(object ob, string name)
{
    string *equip_array, equip = ob->short(); 

    name = capitalize(name); 

    equip_array = explode(equip, " ");
    if (equip_array[0] == "gold" && equip_array[1] == "coated")
    {
        equip_array = equip_array[2..sizeof(equip_array) - 1];
        equip = implode(equip_array, " ");
    }

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
    {
        if (ob->query_std_hoopak())
            equip = "altered hoopak(" + ob->query_former_short() + ")";

        remove_checked_out(name, equip);
    }
    /* Calculate values for armours depending on its ac. */
    else if (function_exists("create_armour", ob))
        remove_checked_out(name, equip);
    /* Not a weapon or armour, but it's magic. */
    else if (ob->query_prop(MAGIC_AM_MAGIC))
        remove_checked_out(name, equip, ob->check_recoverable());

    return;
}

void
enter_inv(object ob, object from)
{
    int new_value;

    ::enter_inv(ob, from);

    if (from == this_object())
    {
        return;
    }
    
    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);

    if (!interactive(from))
        return;

    if (query_verb() == "return")
        return;

    enter_racks(ob, from->query_real_name());

    if (function_exists("create_weapon", ob))
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());
    else if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* If it's not armageddon, raise the tally by the calculated value. */
    if (!ARMAGEDDON->shutdown_active()) 
    from->set_skill(SS_RACK_TALLY, from->query_base_skill(SS_RACK_TALLY) + 
        new_value);
}

public int
return_item(string str)
{
    int i, size;
    object *equip;
    string name;

    if (!strlen(str) ||
      !parse_command(str, all_inventory(this_player()), "%i 'for' %w", equip, 
      name))
    {
        notify_fail("Return which item for whom?\n");
        return 0;
    }

    equip = NORMAL_ACCESS(equip, 0, 0);

    if (!sizeof(equip))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    name = capitalize(name);
    if (name == capitalize(this_player()->query_real_name()))
    {
        notify_fail("Return an item for yourself? Just sort it the " +
            "normal way!\n");
        return 0;
    }

    if (member_array(name, m_indexes(gCheckedOut)) == -1)
    {
        notify_fail(name + " has no borrowed items out.\n");
        return 0;
    }

    for (i = 0, size = sizeof(equip); i < size; i++)
    {
        if (sort_inv(equip[i]->query_name()))
        {
            enter_racks(equip[i], name);
            write("You return " + LANG_ADDART(equip[i]->short()) + " for " + 
                name + ".\n");
        }
    }
    return 1;
}

void
init()
{
    add_action(sort_inv, "sort");
    add_action(list_checked_out, "list");
    add_action(return_item, "return");
    ::init();
}
