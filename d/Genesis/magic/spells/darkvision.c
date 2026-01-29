#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <tasks.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

public void darkvision(object caster, object *targets, int *resist,
    int result);
public int create_spell_darkvision(object caster, object *targets,
    string argument);

public void
add_spell_darkvision()
{
    this_object()->add_spell("darkvision", "See in dark rooms",
         create_spell_darkvision, spell_target_caster);
}

/*
 * Function name: create_spelL_darkvision
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_darkvision(object caster, object *targets, string argument)
{
    set_spell_time(8);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(darkvision);
    set_spell_object("/d/Genesis/magic/spells/darkvision_obj");
    return 0;
}

/*
 * Function name: darkvision
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
darkvision(object caster, object *targets, int *resist, int result)
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
