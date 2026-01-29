#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>

public void dispel(object caster, object *targets, int *resist,
    int result);
public int create_spell_dispel(object caster, object *targets,
    string arguments);

public void
add_spell_dispel()
{
    this_object()->add_spell("dispel", "Dispel magical properties",
         create_spell_dispel, spell_target_one_present_living);
}

/*
 * Function name: create_spelL_dispel
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_dispel(object caster, object *targets, string argument)
{
    /* A very difficult spell.  Versions that work on specific spells
     * or elements would be easier.
     */
    set_spell_time(10);
    set_spell_mana(180);
    set_spell_task(TASK_ROUTINE + 100);
    set_spell_element(SS_ELEMENT_AIR, 80);
    set_spell_form(SS_FORM_ABJURATION, 90);
    set_spell_ingredients(({}));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(dispel);
    set_spell_peaceful(1);
    return 0;
}

/*
 * Function name: dispel
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
dispel(object caster, object *targets, int *resist, int result)
{
    object target = targets[0];
    object *effects;
    int dispelled = 0, i;

    result = min(100, result * (100 - resist[0]) / 100);

    effects = target->query_magic_effects();

    caster->catch_tell("You direct your power at " + 
        target->query_the_name(caster) + ", attempting to nullify the " +
        "magic around " + target->query_objective() + ".\n");
    
    target->catch_tell(caster->query_The_name() + " eyes you intensely " +
        "and you feel a pulse of magical energy rush through you.\n");

    for (i = 0; i < sizeof(effects); i++)
    {
        if (result > effects[i]->query_spell_effect_power())
        {
            effects[i]->dispel_spell_effect(caster);
	}
    }
}
