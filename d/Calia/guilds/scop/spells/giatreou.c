/*
 * giatreou.c
 *
 * Giatreou (Neutralize Poison) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 1st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * August 27th 2006 by Navarre.
 *  - Changed to always use a component.
 *  - Changed to only cure max 1 poison per cast
 * Navarre, October 28th, 2007: Removed resistance check if the target = the caster.
 *                              As they kept failing when in their shadow form.
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <poison_types.h>

#include "defs.h"
#include SPIRIT_HEADER

object comp;

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
    set_spell_name("giatreou");
    set_spell_desc("Neutralize Poison");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(4);
    set_spell_mana(60);
    set_spell_vocal(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP)/2));
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_resist(spell_resist_beneficial);
    set_spell_ingredients(({"yellow_topaz_shard", "_leftover_kidney"}));
    set_spell_target_verify(spell_verify_present);
    add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);

    if (caster->query_intoxicated())
    {
        caster->catch_tell("You cannot use Psuchae's gifts " +
                           "while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_tell("You cannot use Psuchae's gifts " + 
                           "while you are not good aligned.\n");
        return 1;
    }
    return 0;
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
    caster->catch_tell("You summon the energies of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
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
    int strength, old_val, new_val, gstat, wis;
    int total_poisons, poisons_cured;
    object tar = targets[0];

    object* all;

    gstat = caster->query_stat(SS_LAYMAN);
    wis = caster->query_stat(SS_WIS);
    total_poisons = 0;
    poisons_cured = 0; 
   
    strength = caster->resolve_task(TASK_ROUTINE-(gstat/3),
                                   ({ SKILL_AVG, TS_INT, TS_WIS,
                                    SKILL_END, SKILL_WEIGHT, 20,
                                    SS_SPELLCRAFT, SKILL_END,
                                    SKILL_WEIGHT, 30, SS_ELEMENT_LIFE,
                                    SKILL_END,
                                    SKILL_WEIGHT, 50, SS_FORM_ABJURATION}));
    if (resist[0])
    {
        strength = strength - ((resist[0] * strength) / 100);
    }

    if (caster->query_wiz_level())
    {
        caster->catch_tell("Strength = "+strength+".\n");
    }
    all = all_inventory(tar);
    
    if (tar != caster && random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    if (tar == caster)
    {
        write("You attempt to neutralize the poison in your body.\n");


        caster->catch_tell("You close your eyes, concentrating on "+
            "your prayer.\nYou touch your forehead and attempt to "+
            "neutralize the poison flowing through your body.\n");
        say(QCTNAME(caster)+" closes "+HIS(caster)+ " eyes for a brief "+
            "moment. "+capitalize(HE(caster))+
            " touches "+HIS(caster)+ " forehead, but only for a "+
            "second.\n", caster);

        for (int i = 0; i < sizeof(all); i++) 
        {
            if (function_exists("cure_poison", all[i]) ==
                "/std/poison_effect") 
            {
              if(total_poisons == 0 &&
                 all[i]->cure_poison(({all[i]->query_poison_type(),
                                      POISON_CURE_FATIGUE,
                                      POISON_CURE_HP, 
                                      POISON_CURE_MANA,
                                      POISON_CURE_STAT}), strength))
              {
                poisons_cured++;
                total_poisons++;
                continue;
              }
              total_poisons++;
            }
        }
    }
    else
    {
        caster->catch_tell("You close your eyes, concentrating on " +
                           tar->query_the_name(caster)+". You touch " +
                           tar->query_possessive()+" shoulder and " +
                           "attempt to neutralize the poison " +
                           "flowing through "+ tar->query_possessive() +
                           " body.\n");
        tar->catch_tell(caster->query_The_name(tar)+" closes "+
                        caster->query_possessive()+" eyes for a brief " +
                        "moment. " + capitalize(caster->query_pronoun()) +
                        " touches your shoulder and tries to neutralize " +
                        "the poisons in your body.\n");
        say(QCTNAME(caster)+" closes "+caster->query_possessive()+
            " eyes for a brief moment. "+capitalize(caster->query_pronoun())+
            " touches "+QTNAME(tar)+"'s shoulder, but only for a "+
            "second.\n",({ caster, tar}));

        for (int i = 0; i<sizeof(all); i++) 
        {
            if (function_exists("cure_poison", all[i]) ==
                                "/std/poison_effect") 
            {
                if(total_poisons == 0 &&
                   all[i]->cure_poison(({all[i]->query_poison_type(),
                                        POISON_CURE_FATIGUE, POISON_CURE_HP, 
                                        POISON_CURE_MANA, POISON_CURE_STAT}),
                                        strength))
                {
                    poisons_cured++;
                    total_poisons++;
                    continue;
                }
                total_poisons++;
            }
        }
      
    }

    if (total_poisons == 0)
    {
        write("There were no poisons to cleanse!\n");
    }
    else 
    {
        if (poisons_cured == 0)
        {
            write("You were unable to cleanse any poisons. ");
        }
        else
        {
            if (poisons_cured == 1)
            {
                if(tar == caster)
                {
                  write("You manage to cleanse a poison from your body.");
                }
                else
                {
                  caster->catch_msg("You manage to cleanse a poison from " +
                                    QTNAME(tar)+"'s body.");
                }
            }
        }

        if (total_poisons <= poisons_cured)
        {
            write("\nYou sense that no poisons remain.\n");
        }
        else if (total_poisons > poisons_cured)
        {
            write("\nYou sense that more poisons remain.\n");
        }
   }
}
