/*
    Energia - Life and mana link spell for the Spirit Circle of Psuchae.

    Coded by Bishop of Calia, 04. aug. 2004.
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

string
query_spell_level()
{
    return "Elder";
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
        set_spell_name("energia");
        set_spell_desc("Spiritual link");
        set_spell_target(spell_target_one_other_present_living);
        set_spell_time(6);
        set_spell_mana(100);
        set_spell_vocal(0);
        set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
        set_spell_element(SS_ELEMENT_SPIRIT, 80);
        set_spell_form(SS_FORM_CONJURATION, 60);
        set_spell_ingredients(({"_energia_component_"}));
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "energia_obj");
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
        if (objectp(targets[0]->has_syndesi_shadow()))
        {
            caster->catch_tell("The target is already linked to someone!\n");
            return 1;
        }
        if (objectp(caster->has_syndesi_shadow()))
        {
            caster->catch_tell("You are already linked to someone!\n");
            return 1;
        }        
        if (targets[0]->query_prop(LIVE_I_UNDEAD))
        {
            caster->catch_tell("Energia does not work on the undead!\n");
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
    new_val = MIN(CASTED_LIMIT, (old_val + 7));
    caster->set_skill(SS_SPELLS_CASTED, new_val);

    caster->catch_msg("Completing the Energia prayer, you focus on " + 
        targets[0]->query_the_name(caster) + ", willing your souls to" +
        " become linked together. You extend your hand in " + 
        targets[0]->query_possessive() + " direction, and a thin, shadowy" +
        " tendril shoots out from your finger! The tendril snakes towards " +
        targets[0]->query_objective() + " and connects, snapping taut. You" +
        " suddenly feel intensely aware of " + 
        targets[0]->query_the_name(caster) + ".\n");
    targets[0]->catch_msg(caster->query_The_name(targets[0]) + " completes " +
        caster->query_possessive() + " prayer, extending " + 
        caster->query_possessive() + " hand towards you. A thin, shadowy " +
        " tendril shoots out from " + caster->query_possessive() + 
        " finger, snaking" +
        " towards you! The tendril connects and snaps taut. You suddenly feel"+
        " intensely aware of " + caster->query_the_name(targets[0]) + ".\n");
    tell_room(environment(caster), QCTNAME(caster) + " completes " + 
        caster->query_possessive() + " prayer, extending " + 
        caster->query_possessive() + " hand towards " + QTNAME(targets[0]) +
        ". Nothing special seems to happen though.\n", ({caster, targets[0]}));        
  
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, caster, resist, 
        result);
    caster->set_linked(targets[0]);
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist, result);
    targets[0]->set_linked(caster);          
}