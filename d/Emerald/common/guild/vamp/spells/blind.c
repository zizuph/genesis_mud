#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0 - configuration successful
 *                1 - configuration unsuccessful, abort spell
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("blind");
    set_spell_desc("Blind the target");
    set_spell_time(4);
    set_spell_mana(180);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 50);
    set_spell_form(SS_FORM_ENCHANTMENT, 50);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(0);

    set_spell_target(spell_target_one_present_living);
    return 0;
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
    make_spell_effect_object("/d/Emerald/vamp/spells/obj/blind_obj",
        caster, targets[0], resist, result);
    caster->catch_tell("You blind " + targets[0]->query_the_name(caster) +
		       ".\n");
    targets[0]->catch_tell("You are blinded.\n");
}
