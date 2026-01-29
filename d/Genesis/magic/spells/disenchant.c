#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

public void disenchant(object caster, object *targets, int *resist,
    int result);
public void disenchant_conc_msg(object caster, object *targets, string arg);
public int create_spell_disenchant(object caster, object *targets,
    string argument);

public void
add_spell_disenchant()
{
    this_object()->add_spell("disenchant", "Disenchant magical items",
         create_spell_disenchant, spell_target_one_present_non_living);
}

/*
 * Function name: create_spelL_disenchant
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public int
create_spell_disenchant(object caster, object *targets, string argument)
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
    set_spell_effect(disenchant);
    set_spell_peaceful(1);
    set_spell_conc_message(disenchant_conc_msg);
    return 0;
}

public void
disenchant_conc_msg(object caster, object *targets, string arg)
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
 * Function name: disenchant
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
disenchant(object caster, object *targets, int *resist, int result)
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
