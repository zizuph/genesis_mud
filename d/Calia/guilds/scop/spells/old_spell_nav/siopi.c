
/*
 * siopi.c
 *
 * Siopi (Silence) spell for the Spirit Circle of Psuchae
 * This is the silence spell for the guild.
 *
 * Copyright (C): Jaacar, July 30th, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

#ifndef LIVE_M_NO_SILENCE
#define LIVE_M_NO_SILENCE "_live_m_no_silence"
#endif

object comp;

string
query_spell_level()
{
    return "Apprentice";
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
    
    object *gems = filter(deep_inventory(caster), &operator(==)("lapis") @ 
        &->query_gem_name());

    if (!sizeof(gems))
    {
        caster->catch_tell("You need a blue lapiz lazuli in order to" +
            " successfully cast this spell!\n");
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
    if (caster == 0)
    {
        set_spell_name("siopi");
        set_spell_desc("Silence");
        set_spell_target(special_target_one_present_living);
        set_spell_time(3);
        set_spell_mana(45);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
        set_spell_element(SS_ELEMENT_SPIRIT, 35);
        set_spell_form(SS_FORM_ENCHANTMENT, 35);
        set_spell_ingredients(({}));
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "siopi_obj");
        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
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
    else
    {
        if (present("_siopi_object_", targets[0]))
        {
            caster->catch_tell("Your have already silenced your target!\n");
            targets[0]->catch_tell(caster->query_The_name(targets[0])+
                " attempts to silence you again, but you have already been "+
                "muted so it does not work.\n");
            return 1;
        }

        if (targets[0]->query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            caster->catch_tell("That target already cannot speak.\n");
            return 1;
        }

        if (targets[0]->query_prop(LIVE_M_NO_SILENCE))
        {
            caster->catch_tell("That target cannot be silenced.\n");
            return 1;
        }
        return 0;
    }
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
    int old_val, new_val;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
            " unaffected.");
        return;
    }
    
    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 2));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    caster->catch_tell("You point at "+targets[0]->query_the_name(caster)+
        ", removing "+targets[0]->query_possessive() + " ability to "+
        "speak.\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) + 
        " points at you, glaring into your eyes as "+
        caster->query_pronoun()+" does so. You feel your mouth "+
        "tightening up. You cannot speak!\n");
    say(QCTNAME(caster) + " points at " + QTNAME(targets[0]) +
        ".\n", ({caster, targets[0]}));

    if (random(100) >= 70)
    {
            caster->catch_tell("You sacrificed a blue lapis lazuli.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }       
    
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist[0], result)->move(targets[0],1);
}