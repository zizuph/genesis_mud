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
 */
inherit "/std/container";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h"

#define RESET_TIME 900

static int recovering; 

/* example: ([ "gwyneth" : ({1014418296, 1, "silver-tipped ironwood hoopak",
 *             1014418362, 0, blue face mask,}), "kessie" : ({1014418447, 0
 *             "pair of silvery bracers"}) ])
 *             
 *             ([ name : ({ time, glowing/non, short desc }) ])
 */
mapping gCheckedOut = ([]);

void
create_container()
{
    set_name("rack");
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
}

void
init()
{
    add_action("sort_inv", "sort");
    add_action("list_checked_out", "list");
    ::init();
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
        clone_object(KGOBJ + "neq_rack")->move(environment());
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

    if (!parse_command(str, ({}),
      " 'checked' / 'borrowed' [out] 'items' / 'equipment' / 'things' "))
    {
        notify_fail("List borrowed equipment?\n");
	return 0;
    }

    restore_object(MASTER);

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
                glowing = (gCheckedOut[names[i]][j-1] ? "(glowing)" : "(non-glowing)");
		write("   " + gCheckedOut[names[i]][j] + glowing + " borrowed " +
                    "on " + extract(ctime(gCheckedOut[names[i]][j-2]), 4, 15) + ".\n");
	    }

	    write("\n");
	}
    }

    return 1;
}

void
add_checked_out(object kender, object equip)
{
    string name, ob_name;

    if (!objectp(kender) || !objectp(equip))
        return;

    restore_object(MASTER);

    name = kender->query_name();
    ob_name = equip->short();

    if (member_array(name, m_indexes(gCheckedOut)) != -1)
        gCheckedOut[name] += ({ time(), equip->check_recoverable(), ob_name });
    else
        gCheckedOut += ([ name : ({ time(), equip->check_recoverable(), 
            ob_name }) ]);

    save_object(MASTER);
}

varargs void
remove_checked_out(string name, string ob_name, int update = 1)
{
    int position, end, new_end;

    /* The calling function will restore otherwise */
    if (update)
        restore_object(MASTER);

    end = sizeof(gCheckedOut[name]);

    if (member_array(name, m_indexes(gCheckedOut)) == -1)
        return;
    else if (sizeof(gCheckedOut[name]) > 3)
    {
        position = member_array(ob_name, gCheckedOut[name]);

	switch(position)
	{
	case -1:
	    return;
	case 0:
        case 1:
	    /* Should never be 0 or 1, but just in case... */
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

	    gCheckedOut[name] = gCheckedOut[name][0..position - 3] +
		    gCheckedOut[name][position + 1..end];
	    break;
        }
    }
    else
        gCheckedOut = m_delete(gCheckedOut, name);

    /* The calling function will save otherwise */
    if (update)
        save_object(MASTER);
    return;
}

void
remove_non_glowing()
{
    int i, size, j, size2;
    string *names;

    restore_object(MASTER);

    names = m_indexes(gCheckedOut);
    for (i = 0, size = sizeof(names); i < size; i++)
    {
        for (j = sizeof(gCheckedOut[names[i]]) - 2; j > 0; j -= 3)
        {
            if (gCheckedOut[names[i]][j] == 0)
	    {
                remove_checked_out(names[i], gCheckedOut[names[i]][j+1]);
	    }
	    else if ((gCheckedOut[names[i]][j-1] + RESET_TIME) > time())
		    remove_checked_out(names[i], gCheckedOut[names[i]][j+1]);
	}
    }

    save_object(MASTER);
}

void
leave_inv(object ob, object to)
{
    int skill, new_value;

    /* Name of the borrower */
    string name = capitalize(to->query_real_name()); 

    /* Short desc of the object being borrowed. */
    string equip = ob->short(); 

    if (!interactive(to))
    {
        ::leave_inv(ob, to);
        return;
    }

    ::leave_inv(ob, to);

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
    {
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());

        if (new_value > 800)
            add_checked_out(to, ob);
    }

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
    {
        new_value = F_VALUE_ARMOUR(ob->query_ac());

        if (new_value > 200)
            add_checked_out(to, ob);
    }
    
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
}

void
enter_inv(object ob, object from)
{
    int new_value;
    string name = capitalize(from->query_real_name()); 
    string equip = ob->short(); 

    if (!interactive(from))
    {
        ::enter_inv(ob, from);
        return;
    }

    /* Calculate values for weapons depending on its hit and pen. */
    if (function_exists("create_weapon", ob))
    {
        new_value = F_VALUE_WEAPON(ob->query_hit(),ob->query_pen());

        if (new_value > 800)
            remove_checked_out(from->query_name(), ob->short());
    }

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
    {
        new_value = F_VALUE_ARMOUR(ob->query_ac());

        if (new_value > 200)
            remove_checked_out(from->query_name(), ob->short());
    }

    /* If it's armageddon, add a somewhat lowered number to the equipment
       tally to go along with the lowered number the tally is decreased
       by at armageddon when an object is removed.
    if ((ARMAGEDDON->shutdown_active()) && (ob->check_recoverable()))
        from->set_skill(SS_RACK_TALLY, from->query_base_skill(SS_RACK_TALLY) +
            new_value * 3 / 4);    

    /* If it's not armageddon, raise the tally by the calculated value. */
    if (!ARMAGEDDON->shutdown_active()) 
    from->set_skill(SS_RACK_TALLY, from->query_base_skill(SS_RACK_TALLY) + 
        new_value);

    ::enter_inv(ob, from);
}
