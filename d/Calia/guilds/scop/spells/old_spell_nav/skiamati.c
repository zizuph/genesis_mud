
/*
 * skiamati.c
 *
 * Skiamati (Shadow Eyes) spell for the Spirit Circle of Psuchae
 * This will allow the player to see in the dark and see invisible
 * people (depending on skill)
 *
 * Copyright (C): Jaacar, July 31st, 2003
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
    
    object *gems = filter(deep_inventory(caster), &operator(==)("amethyst") @ 
        &->query_gem_name());

    if (!sizeof(gems))
    {
        caster->catch_tell("You need a purple amethyst in order to" +
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
        set_spell_name("skiamati");
        set_spell_desc("Shadow Eyes");
        set_spell_target(special_target_one_present_living);
        set_spell_time(4);
        set_spell_mana(70);
        set_spell_visual(0);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
        set_spell_element(SS_ELEMENT_SPIRIT, 55);
        set_spell_form(SS_FORM_DIVINATION, 50);
        set_spell_ingredients(({}));
        set_spell_resist(spell_resist_beneficial);
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "skiamati_obj");
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
        if (present("_skiamati_object_", targets[0]))
        {
            caster->catch_tell("The target already has enhanced vision.\n");
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
        caster->catch_tell("You complete the spell, but for some reason "+
            "it failed.");
        return;
    }
    
    old_val = caster->query_skill(SS_SPELLS_CASTED);
    new_val = MIN(CASTED_LIMIT, (old_val + 5));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    if (targets[0] == caster)
    {
        caster->catch_tell("You channel the energies of Psuchae into your "+
            "eyes, in the hope that you will be granted enhanced vision.\n");
        tell_room(environment(targets[0]),QCTPNAME(targets[0])+" eyes flash "+
            "brightly for a brief moment.\n",({targets[0]}));
        setuid();
        seteuid(getuid());
        make_spell_effect_object(query_spell_object(), caster, targets[0], 
            resist[0], result)->move(targets[0],1);
    }
    else
    {
        caster->catch_tell("You close your eyes, concentrating on "+
            targets[0]->query_the_name(caster)+".\n");
        targets[0]->catch_tell("Your eyes burn slightly for a moment.\n");
        tell_room(environment(targets[0]),QCTPNAME(targets[0]) + " eyes flash brightly for a brief moment.\n",
            ({targets[0]}));
        setuid();
        seteuid(getuid());
        make_spell_effect_object(query_spell_object(), caster, targets[0], 
            resist[0], result)->move(targets[0],1);
    }
    
    if (random(100) >= 60)
    {
            caster->catch_tell("You sacrificed a purple amethyst.\n");
            comp->set_heap_size(comp->num_heap() - 1);
    }          
}