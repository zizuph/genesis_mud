#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <tasks.h>
#include <ss_types.h>

public void
create_spell()
{
    set_spell_name("darkvision");
    set_spell_desc("See through darkness");
    set_spell_time(8);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_object("/d/Genesis/newmagic/spells/darkvision_obj");

    set_spell_target(spell_target_caster);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
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
    object target = targets[0];

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }

    make_spell_effect_object(query_spell_object(), caster, caster, 
        resist, result);

    caster->catch_tell("You feel a distinct tingle in your eyes as the " +
        "spell takes effect.\n");
}
