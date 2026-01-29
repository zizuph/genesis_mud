/*
 * therapeaou.c
 *
 * Therapeaou (Cure Wounds) spell for the Spirit Circle of Psuchae
 * This is the heal spell for the guild.
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Various changes, Bishop April 2004.
 *
 * Removed insane changes done previous and rebalanced the spell
 * Changed spell to do damage on undeads.
 *    -- Navarre, August 26th 2006.
 * Changed spell to not do damage to self when turned into undead
 * by others.
 *    -- Petros, October 17, 2008.
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spells/heal.c";

#include <ss_types.h>
#include <options.h>
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <wa_types.h>

#include "defs.h"
#include SPIRIT_HEADER

string
query_spell_level()
{
    return "Master";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */

public varargs int
config_spell(object caster, object *targets, string argument)
{
    if(caster == 0)
    {
        set_spell_name("therapeaou");
        set_spell_desc("Cure Wounds");
        set_spell_time(4);
        set_spell_mana(63);
        set_spell_vocal(0);
        set_spell_visual(0);
        set_spell_stationary(0);
        set_spell_ingredients(({"pearl_shard", "_leftover_intestine"}));
        set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP)/2));
        set_spell_element(SS_ELEMENT_LIFE, 40);
        set_spell_form(SS_FORM_ENCHANTMENT, 40);
        add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
        set_spell_target(spell_target_one_present_living);
        set_spell_target_verify(spell_verify_present);
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                               "good aligned.\n");
            return 1;
        }

        if(targets[0]->query_prop(LIVE_I_UNDEAD) && environment(caster)->query_prop("_room_m_no_attack")
           && environment(caster)->query_prop("_room_m_no_magic_attack"))
        {
             caster->catch_tell("You can't seem to heal this soulless creature in this location.\n");
             return 1;
        }
     }
     ::config_spell(caster, targets, argument);
     return 0;
}

void ready_again(object me)
{
    me->catch_tell("You feel the mental strain from performing " +
                   "the Therapeaou prayer dispersing.\n");
}


/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{

    caster->catch_tell("You mentally call upon Psuchae for power.\n");
    say(QCTNAME(caster) + " appears to concentrate deeply.\n");
    if(targets[0]->query_prop(LIVE_I_UNDEAD))
    {
	caster->attack_object(targets[0]);
    }
}

/*
 * Function name: desc_heal
 * Description:   Describe the spell casting and effect.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object targets - the target
 *                int heal - Healing in hps for target
 */
public void
desc_heal(object caster, object target, int heal)
{
    int i, index;
    string who;

    if (caster == target)
    {
        who = "yourself";
        tell_room(environment(caster), QCTNAME(caster)+" prays to Psuchae "+
                  "to heal "+HIS(caster)+" wounds.\n", ({target, caster}));
    }
    else
    {
        who = QCTNAME(target);

        target->catch_msg(QCTNAME(caster)+" prays to Psuchae to tend to your "+
                          "wounds.\n");
        tell_room(environment(caster), QCTNAME(caster)+" prays to Psuchae "+
                  "to tend to the wounds of "+QTNAME(target)+".\n", ({target, caster}));
    }

    caster->catch_msg("You aid " + who + " with your healing powers.\n");

    if (heal < 1)
    {
        target->catch_tell("A pleasant warmth briefly overcomes " +
                           "you and quickly fades.\n");
	tell_room(environment(caster), QCTNAME(target)+" looks unaffected "+
                  "by the prayer.\n", target);
    }
    else
    {
        target->catch_tell("A pleasant warmth briefly overcomes " +
                           "you as you feel your injuries healing.\n");
	tell_room(environment(caster), QCTNAME(target)+" looks as if "+
                  HE(target)+" has been rejuvinated by the prayer.\n", target);

    }
}

/*
 * Function name: desc_undead_heal
 * Description:   Describe the spell casting and effect.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object targets - the target
 *                int heal - Damage in hps dealt to the undead target
 */
public void
desc_undead_heal(object caster, object target, int heal)
{
    int i, index;
    string who = QCTNAME(target);
    string how_much;

    switch(heal)
    {
      case 0:
        how_much = "no";
      case 1..200:
        how_much = "a little";
        break;
      case 201..349:
        how_much = "some";
        break;
      case 350..600:
        how_much = "great";
        break;
      default:
        how_much = "tremendous";
    }

    tell_room(environment(caster), QCTNAME(caster)+" prays to Psuchae to rid "+HIS(caster)+
                          " sight of "+QTNAME(target)+".\n", ({caster, target}));

    caster->catch_msg("You pray to Psuchae to rid your sight of "+QTNAME(target)+
                      ".\n");
    target->catch_msg(QCTNAME(caster)+" prays to Psuchae to rid you from "+HIS(caster)+
                      " sight.\n");

    caster->catch_msg("As the healing powers strike your soulless target, "+
                       "the effect reverts and cause " + who + " "+how_much+
                       " harm.\n");

    target->catch_msg("An unpleasant warmth overcomes you, it escalates to a "+
                       "burning pain as pure lifeforce strikes your undead form "+
                       "and causes "+how_much+" harm in you.\n");
    tell_room(environment(caster), QCTNAME(target)+" convulses and seems caught up "+
              "in a brief internal struggle of pain.\n", ({caster, target}));
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int i, guild_stat, wisdom, base, align, res;
    int heal;
    mixed heal_result;

    object tar = targets[0];    

    guild_stat = (3 * caster->query_stat(SS_OCCUP))/2;
    wisdom = (3 * caster->query_stat(SS_WIS)) /2;    
    align = caster->query_alignment();          
    res = MIN(100, result);                     
    base = guild_stat + wisdom + res + align/10; 

    base = (base * 3) /2; 
    base = base/4 + random(base/4) + random(base/4) + random(base/4);

    if (base > 500)
    {
	base = 500;
        // The Calculated Max value.
        set_heal_amount(500);
    }
    else
    {
        set_heal_amount(base);
    }
 
    if (caster->query_wiz_level())
    {
        caster->catch_tell("Amount = "+base+".\n");
    }    

    if (tar == caster)
    {
      //Don't resist your own spell:
      heal = query_heal_amount(caster, tar);
    }
    else
    {
        heal = (100 - resist[i]) *
               query_heal_amount(caster, tar) / 100;
    }

    if(tar != caster && tar->query_prop(LIVE_I_UNDEAD))
    {
      // Desired target is around 500 damage, thorough testing showed
      // an increase with about half the base value will yield that value
      base = base + base/3;
      heal_result = tar->hit_me(base, MAGIC_DT, caster, -1);
      desc_undead_heal(caster, tar, heal);
      if(tar->query_hp()< 1)
      {
        tar->do_die(caster);
      }
    }
    else
    {
	if(tar->query_hp() >= tar->query_max_hp())
	{
	    heal = 0;
	}
	tar->heal_hp(heal);
	
	desc_heal(caster, tar, heal);
    }
}
