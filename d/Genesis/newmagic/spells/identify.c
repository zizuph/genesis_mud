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
    set_spell_name("identify");
    set_spell_desc("Identify magical properties.");
    set_spell_target(spell_target_one_present_non_living);

    set_spell_time(10);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 40);
    set_spell_form(SS_FORM_DIVINATION, 40);
    set_spell_ingredients(({ "copper coin", "copper coin", "horsetail" }));
    set_spell_resist(spell_resist_identify);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);

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
 * Function name: get_id_info
 * Description:   Return a string describing the magical properties
 *                of an item, up to a certain level.
 * Arguments:     object target - the item to identify
 *                int max_level - the level of info you want 
 *                (see MAGIC_AM_ID_INFO)
 * Returns:       the description
 */
public string
get_id_info(object target, int max_level)
{
    mixed *info;
    int level, i;
    string desc, msg = "";

    info = target->query_prop(MAGIC_AM_ID_INFO);

    for (i = 0; i < (sizeof(info) - 1); i += 2)
    {
        if (intp(info[i]))
	{
            level = info[i];
            desc  = info[i + 1];
	}
        else if (intp(info[i + 1]))
	{
            level = info[i + 1];
            desc  = info[i];
	}
        else
	{
            break;
	}

        if (level <= max_level)
	{
            msg += desc;
	}
    }
    
    return msg;
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
    string msg;
    object target = targets[0];

    result = result * (100 - resist[0]) / 100;

    msg = get_id_info(target, result);

    if (strlen(msg))
    {
        caster->catch_tell(msg);
    }
    else
    {
        caster->catch_tell("You fail to divine any magical properties.\n");
    }

    target->appraise_object(caster->query_skill(SS_APPR_OBJ) + result);
}
