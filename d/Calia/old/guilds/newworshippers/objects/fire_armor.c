/*
  Fire armour for the Worshippers. Comes as a result of a player
  sacrificing his elemental to become an armour.

  Coded by Bishop of Calia, 03/07/03.

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

int damage;

void 
create_armour()
{
    set_name("wor_elem_arm");
    set_short("wor_elem_arm");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_S_WIZINFO, "This is an armour that is summoned by" +
        " a member of the Elemental Worshippers of Calia. They get" +
        " it by sacrificing a summoned fire elemental. Inquire with" +
        " guildmaster if you need access to the code.\n");     

    set_ac(0);
    set_at(A_MAGIC);
    set_af(this_object());

    set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (dest == spell_caster)
    {
        set_this_player(spell_caster);
        wear_me();
        set_this_player(this_player());
    }
}

public int
start()
{

    set_spell_effect_desc("flaming armor");
    
    spell_target->add_subloc("_wor_fire_armor", this_object());
    
    damage = min(30 + random(spell_caster->query_stat(SS_LAYMAN))/3, 60);
    
    set_ac(min(6 + random(spell_caster->query_stat(SS_LAYMAN))/20, 10));

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_tell("Shield AC is: " + this_object()->query_ac()
            + ".\n");
    }     

    set_alarm(600.0, 0.0, &dispel_spell_effect(spell_caster));

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

    // Need to call this in order to reset the light for the player after
    // the shield is gone.
    remove_prop(OBJ_I_LIGHT);
    spell_target->update_light();

    remove_me();
    remove_spell_effect_object();
    
    return 1;
}

public string
show_subloc(string subloc, object me, object observer)
{
    if (subloc != "_wor_fire_armor")
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
    wearer = spell_caster;
    thisdam = damage;

    thisdam -= att->query_magic_res(MAGIC_I_RES_FIRE) * (damage/100);
    thisdam -= att->query_magic_res(MAGIC_I_RES_MAGIC) * (damage/100);

    if (!sizeof(weapons))
    {
        task = TASK_ROUTINE + 100;
    }
    else
    if (weapons[0]->query_hands() == 2)
    {
        task = TASK_ROUTINE - 100;
    }
    else
    {
        task = TASK_ROUTINE;
    }

    if (dam > 0 && att->resolve_task(task, ({SKILL_AVG, TS_DEX, TS_WIS,
        SKILL_END, SKILL_AVG, SS_DEFENCE, SS_ACROBAT,
        SKILL_END}), spell_caster, ({TS_LAYMAN})) < 0)
    {
        att->heal_hp(-thisdam);
        att->catch_msg("You are burnt by the flaming shield surrounding " +
            QTNAME(wearer) + "!\n");
        wearer->catch_msg(QCTNAME(att) + " is burnt by the flaming" +
            " shield that surrounds you.\n");
        wearer->tell_watcher(QCTNAME(att) + " is burnt by the flaming" +
            " shield that surrounds " + QTNAME(wearer) + ".\n", ({att}));

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
