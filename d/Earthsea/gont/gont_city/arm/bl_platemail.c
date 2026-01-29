/* Coded by Ckrik December 1997
 * Updated by Ckrik June 1999
 *
 * Added extra checks just in case the previous shadow isn't removed
 * when someone else wears it - Ckrik January 2004
 *
 * There is a shadow that goes with this object, bl_platemail_shadow.c
 *
 * 4/8/2008 - Fixed shadow issue with removal of wrong shadow. Petros
 *
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define SPIKE_PEN 40

private int chunks_of_flesh = 0;

public void
create_armour()
{
    set_name("platemail");
    add_name("__es_black_spiked_platemail__");
    set_pname("platemails");
    set_adj("blackened");
    set_adj("spiked");
    add_adj("metal"); /* It is, isn't it? - Gorboth */
    set_short("blackened spiked platemail");
    set_pshort("blackened spiked platemails");
    set_long("A blackened platemail. Blackened to make it look " +
        "terrifying, this platemail offers quite a lot of " +
        "protection. Heavily reinforced and sturdily constructed, " +
        "it would take quite a lot to penetrate this armour. " +
        "The protruding spikes covering the entire armour are " +
        "long and sharp protecting the wearer like the porcupine " +
        "and his coat. These spikes must be longer than an arm. " +
        "They can probably really hurt someone.@@flesh_desc@@");
    set_af(this_object());
    set_ac(50);
    set_at(A_BODY);
    set_am(({-4, 0, 4}));
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 9600);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50) + random(100) + 1000);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "It appears some insane wizard has given this armour some sort " +
        "of enchantment, but you cannot imagine why!", 30 }));
}

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}

public int
wear()
{
    object tp = this_player();

    tp->remove_bl_platemail_shadow();

    if(tp->query_stat(SS_DIS) < 55)
    {
        write("An eerie presence glows from within the armour. " +
            "You decide it is better to not mess with it.\n");
        tp->command("$drop __es_black_spiked_platemail__");
        return 0;
    }

    if((tp->query_stat(SS_STR) < 80) ||
        (tp->query_stat(SS_CON) < 80))
    {
        write("A loud voice yells: Fool!  You are not worthy, " +
            "you weak pathetic flea!\n");
        return 0;
    }

    write("Despite having misgivings, you decide to wear the " +
        "armour over your shoulders.\nA presence within the " +
        "armour seems to have accepted you.\n");
    write("A servile voice: Master, we are now one!\n");

    setuid();
    seteuid(getuid());

    object bl_platemail_shadow = clone_object(
        "/d/Earthsea/gont/gont_city/arm/bl_platemail_shadow"
    );
    bl_platemail_shadow->set_platemail_shadow_owner(this_object());
    bl_platemail_shadow->shadow_me(tp);

    return 0;
}

public int
remove()
{
    if (objectp(query_worn()))
    {
        query_worn()->remove_bl_platemail_shadow();
    }

    return 0;
}

public varargs mixed
armour_hit_me(int wcpen, int dt, object attacker, int attack_id, 
    int target_hitloc = -1)
{
    object tp = query_worn();
    string location;
    mixed dam_lvl;
    int hit_id = -1;

    if(!attacker || !living(attacker) || !tp || !living(tp))
    {
        return;
    }

    if(attacker->query_humanoid())
    {
        switch(attack_id)
        {
            case W_RIGHT:
                location = "right arm";
                hit_id = TS_RARM;
            break;
            case W_LEFT:
                location = "left arm";
                hit_id = TS_LARM;
            break;
            case W_BOTH:
                /* Only hit one */
               if(random(2))
               {
                   location = "right arm";
                   hit_id = TS_RARM;
               } else {
                   location = "left arm";
                   hit_id = TS_LARM;
               }
            break;
            case W_FOOTR:
                location = "right leg";
                hit_id = TS_LEGS;
            break;
            case W_FOOTL:
                location = "left leg";
                hit_id = TS_LEGS;
            break;
            default:
                location = "body";
                hit_id = TS_TORSO;
            break;
        }
    }

    /* Strike back at the attacker */
    dam_lvl = attacker->hit_me(SPIKE_PEN, dt, tp, (W_IMPALE | W_BLUDGEON), hit_id);

    if(attacker->query_humanoid())
    {
        if(dam_lvl[0] <= 0)
        {
            return;
        } else if(dam_lvl[0] < 2) {
            attacker->catch_msg("Your " + location +
                " is not hurt at all by the long spikes on " +
                QTNAME(tp) + "'s blackened spiked platemail.\n");
            tp->catch_msg(QCTNAME(attacker) + "'s " + location +
                " is not hurt at all by the long spikes " +
                "on your blackened spiked platemail.\n");
            attacker->tell_watcher(QCTNAME(attacker) + "'s " +
                location + " is not hurt at all by the long spikes " +
                "on " + QTNAME(tp) + "'s " + "blackened spiked " +
                "platemail.\n", attacker, ({ tp }));
        } else if(dam_lvl[0] < 5) {
            attacker->catch_msg("You hurt your " + location +
                " slightly as you hit the spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail.\n");
            tp->catch_msg(QCTNAME(attacker) + " hurts " +
                attacker->query_possessive() + " " + location +
                " slightly as " + attacker->query_pronoun() +
                " hits the spikes of your blackened spiked " +
                "platemail.\n");
            attacker->tell_watcher(QCTNAME(attacker) + " hurts " +
                attacker->query_possessive() + " " + location +
                " slightly as " + attacker->query_pronoun() +
                " hits the spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail.\n", attacker,
                ({ tp }));
        } else if(dam_lvl[0] < 10) {
            attacker->catch_msg("Your " + location +
                " begin to trickle blood as the spikes of " +
                QTNAME(tp) + "'s blackened spiked platemail " +
                "pierce into you.\n");
            tp->catch_msg(QCTNAME(attacker) + "'s " + location +
                " begins to trickle blood as the spikes of your " +
                "blackened spiked platemail pierce into " +
                attacker->query_objective() + ".\n");
            attacker->tell_watcher(QCTNAME(attacker) + "'s " +
                location + " begins to trickle blood as the spikes " +
                "of " + QTNAME(tp) + "'s blackened spiked platemail " +
                "pierce into " + attacker->query_objective() + ".\n",
                attacker, ({ tp }));
        } else if(dam_lvl[0] < 25) {
            attacker->catch_msg("The spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail punch holes in your " +
                location + " as you strike the armour.\n");
            tp->catch_msg("The spikes of your blackened spiked " +
                "platemail punch holes in " + QTNAME(attacker) +
                "'s " + location + " as " + attacker->query_pronoun() +
                " strikes the armour.\n");
            attacker->tell_watcher("The spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail punche holes in " +
                QCTNAME(attacker) + "'s " + location + " as " +
                attacker->query_pronoun() + " strikes the armour.\n",
                attacker, ({ tp }));
        } else {
            chunks_of_flesh++;
            attacker->command("scream");
            attacker->catch_msg(QCTNAME(tp) + " grins at you " +
                "as a chunk of your flesh is ripped away from " +
                "your " + location + " by the spikes of " +
                tp->query_possessive() +
                " blackened spiked platemail.\n");
            tp->catch_msg("You grin at " + QTNAME(attacker) +
                " as a chunk of " + attacker->query_possessive() +
                " flesh is ripped away from " +
                attacker->query_possessive() + " " + location +
                " by the spikes of your blackened spiked " +
                "platemail.\n");
            attacker->tell_watcher(QCTNAME(tp) + " grins at " +
                QCTNAME(attacker) + " as a chunk of " +
                attacker->query_possessive() + " flesh is " +
                "ripped away from " + attacker->query_possessive() +
                " " + location + " by the spikes of " +
                QTNAME(tp) + "'s blackened spiked " +
                "platemail.\n", attacker, ({ tp }));
        }
    } else {
        if(dam_lvl[0] <= 0)
        {
            return;
        } else if(dam_lvl[0] < 2) {
            attacker->catch_msg("You are not hurt at all " +
                "by the long spikes on " + QTNAME(tp) +
                "'s blackened spiked platemail.\n");
            tp->catch_msg(QCTNAME(attacker) + " is not " +
                "hurt at all by the long spikes on your " +
                 "blackened spiked platemail.\n");
            attacker->tell_watcher(QCTNAME(attacker) +
                " is not hurt at all by the long spikes on " +
                QCTNAME(tp) + "'s blackened spiked platemail.\n", 
                attacker, ({ tp }));
        } else if(dam_lvl[0] < 5) {
            attacker->catch_msg("You hurt yourself slightly as " +
                "you hit the spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail.\n");
            tp->catch_msg(QCTNAME(attacker) + " hurts " +
                attacker->query_objective() + "self slightly as " +
                attacker->query_pronoun() + " hits the spikes of " +
                "your blackened spiked platemail.\n");
            attacker->tell_watcher(QCTNAME(attacker) + " hurts " +
                attacker->query_objective() + "self slightly as " +
                attacker->query_pronoun() + " hits the spikes of " +
                QTNAME(tp) + "'s blackened spiked platemail.\n",
                attacker, ({ tp }));
        } else if(dam_lvl[0] < 10) {
            attacker->catch_msg("You begin to trickle blood as " +
                "the spikes of " + QTNAME(tp) + "'s blackened " +
                "spiked platemail pierce into you.\n");
            tp->catch_msg(QCTNAME(attacker) + " begins to " +
                "trickle blood as the spikes of your blackened " +
                "spiked platemail pierce into " +
                attacker->query_objective() + ".\n");
            attacker->tell_watcher(QCTNAME(attacker) + "begins to " +
                "trickle blood as the spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail pierce into " +
                attacker->query_objective() + ".\n", attacker,
                ({ tp }));
        } else if(dam_lvl[0] < 25) {
            attacker->catch_msg("The spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail punch holes in " +
                "you as you strike the armour.\n");
            tp->catch_msg("The spikes of your blackened spiked " +
                "platemail punch holes in " + QTNAME(attacker) +
                " as " + attacker->query_pronoun() + " strikes " +
                "the armour.\n");
            attacker->tell_watcher("The spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail punch holes in " +
                QTNAME(attacker) + " as " + attacker->query_pronoun() +
                " strikes the armour.\n", attacker, ({ tp }));
        } else {
            chunks_of_flesh++;
            attacker->command("scream");
            attacker->catch_msg(QCTNAME(tp) + " grins at you as a " +
                "chunk of your flesh is ripped away by the spikes " +
                "of " + tp->query_possessive() + " blackened " +
                "spiked platemail.\n");
            tp->catch_msg("You grin at " + QTNAME(attacker) +
                " as a chunk of " + attacker->query_possessive() +
                " flesh is ripped away by the spikes of " +
                "your blackened spiked platemail.\n");
            attacker->tell_watcher(QCTNAME(tp) + " grins at " +
                QTNAME(attacker) + " as a chunk of " +
                attacker->query_possessive() + " flesh is ripped " +
                "away by the spikes of " + QTNAME(tp) +
                "'s blackened spiked platemail.\n", attacker,
                ({ tp }));
        }
    }

    if(!random(5)) // so it doesn't break constantly
    {
        hits++;

        if(F_ARMOUR_CONDITION_WORSE(hits, arm_ac, likely_cond))
        {
            hits = 0;
            set_condition(query_condition() + 1);
        }
    }
    
    return dam_lvl;
}

public string
flesh_desc()
{
    switch(chunks_of_flesh)
    {
      case 0:
            return "\n";
        break;
        case 1:
            return " A chunk of flesh is stuck on the spikes.\n";
        break;
        case 2..4:
            return " A couple chunks of flesh decorate the spikes.\n";
        break;
        case 5..10:
            return " The spikes are littered with chunks of flesh.\n";
        break;
        default:
            return " The entire armour is bloodied with chunks of flesh.\n";
    }
}


