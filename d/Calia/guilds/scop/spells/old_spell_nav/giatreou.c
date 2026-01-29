
/*
 * giatreou.c
 *
 * Giatreou (Neutralize Poison) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 1st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
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

#include "defs.h"
#include SPIRIT_HEADER

object comp;

string
query_spell_level()
{
    return "Master";
}

/*
    Use the custom targeting function here to introduce the gem possibly
    surviving a casting of the spell. Otherwise this is identical to 
    spell_target_one_present_living from newmagic/targeting.c.
    
*/
public object *
special_target_one_present_living(object caster, string str)
{
    object *oblist;
    
    object *gems = filter(deep_inventory(caster), &operator(==)("topaz_yellow") @ 
        &->query_gem_name());

    if (!sizeof(gems))
    {
        caster->catch_tell("You need a yellow topaz in order to successfully" +
            " cast this spell!\n");
        return ({ });
    }
    
    comp = gems[0];
        
    if (!strlen(str))
    {
        return ({ caster });
    }

    parse_command(str, ({}), "[at] / [on] [the] %s", str);
    oblist = PARSE_THIS(str, "%l");

    if (!sizeof(oblist))
    {
	if ((str == "me") || (str == "myself") || 
            (str == caster->query_real_name()))
	{
	    return ({ caster });
	}

	caster->catch_tell("There is no " + str + " here.\n");
	return ({});
    }

    if (sizeof(oblist) > 1)
    {
        caster->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }
        
    return oblist;
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
    set_spell_target(special_target_one_present_living);
    set_spell_time(6);
    set_spell_mana(100);
    set_spell_vocal(0);
    set_spell_stationary(1);
    set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
    set_spell_element(SS_ELEMENT_LIFE, 45);
    set_spell_form(SS_FORM_ENCHANTMENT, 45);
    set_spell_resist(spell_resist_beneficial);
    set_spell_ingredients(({}));
    set_spell_target_verify(spell_verify_present);
    add_element_resistance(SS_ELEMENT_LIFE, MAGIC_I_RES_LIFE);
    if (caster->query_intoxicated())
    {
        caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
        return 1;
    }
    if (caster->query_alignment() < 0)
    {
        caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
            "good aligned.\n");
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
    int i, strength, old_val, new_val, gstat, wis;
    int total_poisons, poisons_cured;
    object *all;
 
    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 4));
    gstat = caster->query_stat(SS_LAYMAN);
    wis = caster->query_stat(SS_WIS);
    total_poisons = 0;
    poisons_cured = 0; 
   
    strength = (gstat + wis) / 4 + caster->query_casting_bonus()/2; 
    
    strength = strength + random(strength)/2 + random(strength)/2;

    if (caster->query_wiz_level())
    {
        caster->catch_tell("Strength = "+strength+".\n");
    }

    all = all_inventory(targets[0]);
    
    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
            " unaffected.");
        return;
    }
    
    caster->set_skill(SS_SPELLS_CASTED, new_val);
    if (targets[0] == caster)
    {
        write("You attempt to neutralize the poison in your system.\n");
        for (i=0; i<sizeof(all); i++) 
        {
            if (function_exists("cure_poison", all[i]) ==
                "/std/poison_effect") 
            {
                total_poisons++;
                
                if (all[i]->cure_poison(({"all"}), strength))
                {
                    poisons_cured++;
                }
                
            }
        }
        return;
    }
    
    else
    {
        for (i=0; i<sizeof(all); i++) 
        {
            if (function_exists("cure_poison", all[i]) ==
                "/std/poison_effect") 
            {
                total_poisons++;
            
                if (all[i]->cure_poison(({"all"}), strength))
                {
                    poisons_cured++;
                }
            }
        }
        
        caster->catch_tell("You close your eyes, concentrating on "+
            targets[0]->query_the_name(caster)+". You touch "+
            targets[0]->query_possessive()+" shoulder and attempt to "+
            "neutralize the poison flowing through "+
            targets[0]->query_possessive()+" body.\n");

        targets[0]->catch_tell(caster->query_The_name(targets[0])+" closes "+
            caster->query_possessive()+" eyes for a brief moment. "+
            capitalize(caster->query_pronoun())+" touches your shoulder "+
            "and tries to neutralize the poisons in your body.\n");
    
        say(QCTNAME(caster)+" closes "+caster->query_possessive()+
            " eyes for a brief moment. "+capitalize(caster->query_pronoun())+
            " touches "+QTNAME(targets[0])+"'s shoulder, but only for a "+
            "second.\n",({ caster, targets[0]}));
    }
    
    if (total_poisons == 0)
    {
        write("There were no poisons there to cleanse!\n");
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
                write("You cleansed one poison. ");
            }
            else
            {
                write("You cleansed " + poisons_cured + " poisons. ");
            }
        }
    
        if (total_poisons - poisons_cured == 0)
        {
            write("No poisons remain.\n");
        }
        else if (total_poisons - poisons_cured == 1)
        {
            write("One poison remains.\n");
        }
        else
        {
            write((total_poisons - poisons_cured) + " poisons remain.\n");
        }
    }
    
    if (random(100) >= 70)
    {
            caster->catch_tell("You sacrificed a yellow topaz.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }           
    
    return;
}