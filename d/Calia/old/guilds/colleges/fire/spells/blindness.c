/*
    Blindness spell for the Fire College.

    By Bishop of Calia, July 2003.
*/

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h"

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
    set_spell_name("blindness");
    set_spell_desc("Rob someone of their eyesight");
    set_spell_target(spell_target_one_present_living);
    set_spell_time(4);
    set_spell_mana(60);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_FIRE, 35);
    set_spell_form(SS_FORM_CONJURATION, 35);
    set_spell_ingredients(({ }));
    set_spell_target_verify(spell_verify_present);
    set_spell_object(FIRE_SPELLS + "blindness_ob");
    return 0;
}


public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You draw power from the Plane of Fire.\n");
    say(QCTNAME(caster) + " appears to focus, " + 
        caster->query_possessive() + " eyes flashing deep red.\n");
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
    if (present("_college_blindness_ob_", targets[0]))
    {
         caster->catch_tell("Your spell fails to have any effect as" +
             " your target is already blinded!\n");
         return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but your target is" +
            " unaffected.");
        return;
    }
    
    caster->catch_tell("You complete the spell, weaving Fire to deprive " +
        targets[0]->query_the_name(caster) + " of " + 
        targets[0]->query_possessive() + " eyesight. " +
        capitalize(targets[0]->query_pronoun()) + " yelps and claws" +
        " at " + targets[0]->query_possessive() + " eyes, totally" +
        " blinded!\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) + 
        " looks intently at you, deep in concentration. Suddenly" +
        " the world around you becomes impossibly bright, and you" +
        " claw at your eyes in pain. When you open them again, all" +
        " is darkness!\n");
    say(QCTNAME(caster) + " looks intently at " + QTNAME(targets[0]) +
        ", deep in concentration. The latter suddenly yelps and claws" +
        " at " + targets[0]->query_possessive() + " eyes, totally" +
        " blinded!\n", ({caster, targets[0]}));
    
    setuid();
    seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets[0], 
        resist[0], result)->move(targets[0]);
}