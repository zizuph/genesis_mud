/*
 * pIdentify
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h>

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 7;
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
        caster->catch_msg(msg + "\n");
    }
    else
    {
        caster->catch_tell("You fail to divine any magical properties.\n");
    }

    target->appraise_object(caster->query_skill(SS_APPR_OBJ) + result);
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
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("pidentify");
    set_spell_desc("Identify a magic item");

    set_spell_resist(spell_resist_identify);
    set_spell_target(spell_target_one_present_non_living);
//    set_spell_target(spell_target_one_present_living);
    set_spell_target_verify(spell_verify_present);
	
    set_spell_element(SS_ELEMENT_LIFE, 14);
    set_spell_form(SS_FORM_DIVINATION, 24);
    set_spell_stationary(1);

    set_spell_time(10);
    set_spell_mana(20);

    set_spell_task(TASK_SIMPLE);

    set_spell_ingredients(({"pearl"}));

    set_spell_peaceful(1);

    return 0;
}
