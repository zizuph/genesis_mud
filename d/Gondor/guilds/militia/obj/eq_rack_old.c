/* 
 * /d/Gondor/guilds/militia/obj/eq_rack.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Saving Equipment Rack that keeps tallies of equipment left
 * to avoid over-selfish members.
 *
 * Adapted from code by Gwyneth from July 1999 
 * Auberon and Gwyneth, April 2001
 */
inherit "/std/container";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include "../militia.h"

static int recovering; 

void
create_container()
{
    set_name("rack");
    set_adj("pine");
    add_adj("wood");
    set_short("pine wood rack");
    set_long("This is a rack where members can place their equipment for " + 
        "use by other members. The word 'Sort' has been blackened into the " + 
        "side.\n");

    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The pine wood rack is impossible to carry.\n");
}

int
sort_inv(string arg)
{
    object *all_eq, nrack = present("non_glowing_rack", environment());
    string sall;
    int i, s, glowing, nonglowing;

/*
    if (!(ARMAGEDDON->shutdown_active()))
    {
        notify_fail("You can only sort things during armageddon.\n");
        return 0;
    }

*/
    if(!nrack)
    {
        setuid();
        seteuid(getuid());
        clone_object(MOBJ + "neq_rack")->move(environment());
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
          (!all_eq[i]->id("gem")) &&
          (!all_eq[i]->query_prop(OBJ_M_NO_SELL)) &&
          (!all_eq[i]->query_prop(OBJ_I_INVIS)) &&
          (!all_eq[i]->query_prop(OBJ_I_BROKEN)))
        {
            if(all_eq[i]->check_recoverable())
            {
                all_eq[i]->move(this_object());
                write("You place a " + sall + " in the pine wood rack.\n");
                say(QCTNAME(this_player()) + " places a " + sall + 
                    " in the pine wood rack.\n");
                glowing = 1;
            }
            else
            {
                all_eq[i]->move(nrack);
                write("You place a " + sall + " in the spruce wood rack.\n");
                say(QCTNAME(this_player()) + " places a " + sall + 
                    " in the spruce wood rack.\n");
                nonglowing = 1;
            }
        }
    }

    if (glowing)
    {
        write("You put the longest lasting equipment in the pine wood rack.\n");
        say(QCTNAME(this_player()) + " puts the longest lasting equipment " +
            "in the pine wood rack.\n");
    }
    if (nonglowing)
    {
        write("You put the equipment that won't last so long in " +
            "the spruce wood rack.\n");
        say(QCTNAME(this_player()) + " puts the equipment that won't last " +
            "so long in the spruce wood rack.\n");
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
    write("A young guard on duty nearby frowns at you as he checks his " +
        "list, and you replace the " + equip + ".\n");
    say("A young guard on duty nearby frowns at " + name + " as he checks " +
        "his list, and " + name + " replaces the " + equip + ".\n");
    ob->move(this_object());
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
        new_value = F_VALUE_WEAPON(ob->query_hit(), ob->query_pen());

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* Tally depending on what has been put into and taken out of the rack. */
    skill = to->query_skill(SS_MILITIA_RACK);
    
    /* If it's not armageddon, and the borrower doesn't have
       enough in his tally, he can't borrow anything. */
    if (!ARMAGEDDON->shutdown_active() && skill < new_value)
        set_alarm(0.1, 0.0, &rack_get(ob, name, equip));

    /* If it's not armageddon, decrease the tally by the calculated
       value of an object. */
    if (!(ARMAGEDDON->shutdown_active()))
        to->set_skill(SS_MILITIA_RACK, to->query_base_skill(SS_MILITIA_RACK) -
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
        new_value = F_VALUE_WEAPON(ob->query_hit(), ob->query_pen());

    /* Calculate values for armours depending on its ac. */
    if (function_exists("create_armour", ob))
        new_value = F_VALUE_ARMOUR(ob->query_ac());

    /* If it's not armageddon, raise the tally by the calculated value. */
    if (!ARMAGEDDON->shutdown_active()) 
    from->set_skill(SS_MILITIA_RACK, from->query_base_skill(SS_MILITIA_RACK) + 
        new_value);

    ::enter_inv(ob, from);
}

void
init()
{
    add_action(sort_inv, "sort");
    ::init();
}

