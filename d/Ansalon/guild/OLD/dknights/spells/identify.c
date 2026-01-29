#pragma strict_types

inherit "/d/Genesis/newmagic/spell";

#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>

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
    set_spell_name("identify");
    set_spell_desc("Detect the magical properties of an item.");
    set_spell_target(spell_target_one_present_non_living);

    set_spell_time(7);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_form(SS_FORM_CONJURATION, 0);
    set_spell_resist(spell_resist_identify);
    set_spell_target_verify(spell_verify_present);
    set_spell_peaceful(1);
    return 0;
}

public void
concentrate_msg(object caster, object *targets, string arg)
{
    string str;
    object *who;

    caster->catch_tell("You chant an incantation in ancient solamnian: "+
                       "Tsaran korilath ith hakon.\n"+
                       "You place your hands on the "+
                       FO_COMPOSITE_ALL_DEAD(targets, caster)+ ".\n");

    who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " chants an incantation in ancient solamnian: "+
                       "Tsaran korilath ith hakon.\n"+
                       QCTNAME(caster)+ " places "+HIS(caster)+" hands on "+HIS(caster)+
                       " "+QCOMPDEAD+ ".\n", caster);

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
