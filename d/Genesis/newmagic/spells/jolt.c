/*
 * jolt.c
 * This spell breaks another spellcaster's concentration
 */

#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>

public void
create_spell()
{
    set_spell_time(2); // it has to be very fast to be useful
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    set_spell_form(SS_FORM_ABJURATION, 50);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(1);
    set_spell_offensive(1);

    set_spell_target(spell_target_one_other_present_living);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
}

/*
 * Function name: config_spell
 * Description:   reconfigure this spell for a particular casting attempt
 * Returns:       0 - configuration successful
 *                1 - configuration not successful, abort spellcasting
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    // Give a bit of randomness to the casting time each time the spell is used
    set_spell_time(random(2) + 1);
    return 0;
}

public void
desc_casting(object caster, object *targets)
{
    string msg;

    caster->catch_tell("You channel your power into " + 
        FO_COMPOSITE_ALL_LIVE(targets, caster) + ".\n");

    msg = " extends " + caster->query_possessive() + 
        " clenched fist toward you.\n";
    targets->catch_tell(({
        caster->query_Met_name() +  msg,
        capitalize(caster->query_nonmet_name()) + msg,
        "" }));
                           
    targets->catch_tell("You feel a charge of magical energy surge " +
        "through your body.\n");

    caster->tell_watcher(QCTNAME(caster) + " extends " + 
        caster->query_possessive() + " clenched fist toward " +
        QCOMPLIVE + ".\n", targets);
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
    int i;

    desc_casting(caster, targets);

    for (i = 0; i < sizeof(targets); i++)
    {
        if (random(100) < resist[i])
	{
            continue;
	}

        targets[i]->break_spell("", caster);
    }
}
