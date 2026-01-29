#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

public void
create_spell()
{
    /* This is a very intensive spell */
    set_spell_time(25);
    set_spell_mana(150);
    set_spell_task(TASK_ROUTINE + 100);
    set_spell_element(SS_ELEMENT_EARTH, 80);
    set_spell_form(SS_FORM_TRANSMUTATION, 80);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);

    set_spell_target(spell_target_one_present_non_living);

    // This is done for backward compatibility issues.  You shouldn't
    // need to do this in your own spells.
    ::create_spell();
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    string str;
    object *who;

    caster->catch_tell("You touch " + 
        FO_COMPOSITE_ALL_DEAD(targets, caster) + ".\n");

    who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " touches " + QCOMPDEAD + ".\n");
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
    mixed *prop, level;
    object target = targets[0];

    result = result * (100 - resist[0]) / 100;

    prop = target->query_prop(MAGIC_AM_MAGIC);

    if ((sizeof(prop) < 2) || 
        !(intp(level = prop[0]) || intp(level = prop[1])) ||
        (result < level) ||
        !target->disenchant_object(caster))
    {
        caster->catch_tell("Nothing seems to happen to the " +
            target->short(caster) + ".\n");
    }
}
