
/* Aspida (Flame Shield) Armour

   Conjured by the Aspida spell of the Firewalkers.

   Coded by Jaacar 

   Modified by Bishop, June 1st 1999. 

   This is the shield that is made by the Aspida spell. There's a chance,
   with every damaging hit the attacker makes, that he'll be burnt by the
   shield. The shield provides a level of light, as well.
*/

#pragma strict_types

inherit "/std/armour";
inherit "/d/Genesis/magic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER

varargs public int dispel_spell_effect(object dispeller);

int damage;

void 
create_armour()
{
    set_name("flame_arm");
    add_name(ASPIDA_OBJ);
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 

    set_ac(0);
    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

}

void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
    set_this_player(spell_target);
    wear_me();
    set_this_player(TP);
}

public int
start()
{
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    damage = 60;

    spell_target->add_subloc(ASPIDA_OBJ, this_object());

    damage += spell_caster->resolve_task(TASK_ROUTINE, ({SKILL_WEIGHT, 25,
        TS_WIS, SKILL_END, SKILL_WEIGHT, 75, TS_OCC, SKILL_END, SKILL_AVG, 
        SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SKILL_END}));
    damage = max(damage, 20);

    set_alarm(600.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("The shimmering shield of liquid fire "+
        "consumes itself leaving no trace behind.\n");
    tell_room(environment(spell_target),"The shimmering shield of liquid "+
        "fire surrounding "+ QNAME(spell_target)+" consumes "+
        "itself leaving no trace behind.\n",({ spell_target }));

    remove_me();
    remove_spell_effect_object();

    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
    if (subloc != ASPIDA_OBJ)
        return me->show_subloc(subloc, me, observer);

    if ((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || query_worn() != me))
            return "";

    return "A shimmering shield of liquid fire "+
        "surrounds " + ( observer == me ? "you" :
        me->query_objective() ) + ".\n";
}

/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 *                
 *                My redefinition of got_hit implements the damaging
 *                shield. For each hit that deals damage, the attacker
 *                has to succeed in a task, or get burned. The task is
 *                easier if you're wielding a two handed weapon, a bit 
 *                harder if you have a one-handed weapon and harder still
 *                if you're unarmed. 
 * 
 *
 *
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    object *weapons, wearer;
    int task, thisdam;

    weapons = att->query_weapon(-1);
    wearer = environment(TO);
    thisdam = damage;

    thisdam -= att->query_magic_res(MAGIC_I_RES_FIRE) * (damage/100);
    thisdam -= att->query_magic_res(MAGIC_I_RES_MAGIC) * (damage/100);

    if (!sizeof(weapons))
    {
        task = TASK_ROUTINE + 200;
    }
    else
    if (weapons[0]->query_hands() == 2)
    {
        task = TASK_ROUTINE;
    }
    else
    {
        task = TASK_ROUTINE + 100;
    }

    if (dam > 0 && att->resolve_task(task, ({SKILL_AVG, TS_DEX, TS_WIS,
        SKILL_END, SKILL_AVG, SS_ELEMENT_FIRE, SS_FORM_ABJURATION,
        SKILL_END})) < 0)
    {
        att->heal_hp(-thisdam);
        att->catch_msg("You are burnt by the flaming shield surrounding" +
            QTNAME(wearer) + "!\n");
        wearer->catch_msg(QCTNAME(att) + " is burnt by the flaming" +
            " shield that surrounds you.\n");
        tell_room(environment(att), QCTNAME(att) + " is burnt by the flaming" +
            " shield that surrounds " + QTNAME(wearer) + ".\n", 
            ({wearer, att}));

        if (wearer->query_wiz_level())
        {
            wearer->catch_msg("Enemy was dealt " + thisdam + " hp.\n");
        }

        if (att->query_hp() <= 0)
        {
            att->do_die(wearer);
        }
    }
    ::got_hit(hid, ph, att, dt, dam);
}

/*
 * called from the set_at - we want to be able to wear
 * the armour without printing messages
 */
public mixed
wear(object obj)
{
  return 1;
}

public mixed
remove(object obj)
{
  return 1;
}

int
query_recover()
{
    return 0;
}

void 
set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

int 
set_condition(int i)
{
    i=0;
    ::set_condition(i);
}

varargs void
remove_broken(int silent = 0)
{
    return;
}
