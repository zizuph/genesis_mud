/*
 * General Identify Spell
 * 
 * This is a generic identify spell that should be used as the basis for all
 * identify spells under the Genesis Magic system created in 2009.
 *
 * Created by Petros, May 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <flags.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"


// Prototypes
public void     resolve_identify_spell(object caster, mixed * targets, int * resist, int result);
public int      is_valid_identify_target(object target);
public string * query_identify_ingredients(object caster);
public void     hook_identify_describe_cast(object caster, object target);
public void     hook_identify_success(object caster, object target, string id_message, int result);
public void     hook_identify_failure(object caster, object target);

/*
 * Function:    config_identify_spell
 * Description: Config function for identify spells. Redefine this in your
 *              own identify spells to override the defaults.
 */
public void
config_identify_spell()
{
   
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
    set_ability_skills(({ SKILL_AVG,
        query_spell_element_skill(),
        query_spell_form_skill(),
        SKILL_END }));
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("identify");
    set_spell_desc("Discern magical properties");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0); 

    set_spell_mana(30);
    
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_spell_target(spell_target_one_present_non_living);
    set_ability_target_verify(spell_verify_present);
    set_spell_ingredients(query_identify_ingredients);
    
    // This one does not make sense to be affected by spell enhancers.
    set_spell_tohit_based(1);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_WATER, 20);
    set_spell_form(SS_FORM_DIVINATION, 20);
        
    // Call the specific configuration that is to be masked.
    config_identify_spell();
    
    // Call this after the config_identify_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    get_id_info
 * Description: Return a string describing the magical properties
 *              of an item, up to a certain level.
 * Arguments:   object target - the item to identify
 *              int max_level - the level of info you want 
 *              (see MAGIC_AM_ID_INFO)
 * Returns:     the description
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
 * Function:    query_identify_skill
 * Description: Returns the skill that will be used in the calculation
 *              for appraise object. Normal appraise uses SS_APPR_OBJ.
 *              For the identify spell, we will use the person's element
 *              ability.
 */
public int
query_identify_skill()
{
    return query_spell_element_skill();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_identify_spell(caster, targets, resist, result);

    object target = targets[0];    
    string msg = get_id_info(target, result);
    hook_identify_describe_cast(caster, target);

    if (strlen(msg))
    {
        hook_identify_success(caster, target, msg, result);
    }
    else
    {
        hook_identify_failure(caster, target);
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_identify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_identify_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    is_valid_identify_target
 * Description: Called from target_identify_spell, a customized spell should
 *              mask this and add any restrictions (such as guild members)
 *              on top of the base restrictions in targetting.
 * Returns:     0/1 - not valid/valid target
 */
public int
is_valid_identify_target(object target)
{
    return 1;
}

/*
 * Function:    hook_identify_describe_cast
 * Description: Mask this function to display messages for the preparation
 *              for the identification. This is different from the
 *              concentration message because it happens right before the
 *              player actually sees the identify message.
 */
public void
hook_identify_describe_cast(object caster, object target)
{    
    caster->catch_tell("You touch " + 
        FO_COMPOSITE_ALL_DEAD(({ target }), caster) + ".\n");

    object * who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster,
        all_inventory(environment(caster)) - ({ caster })));

    who->catch_msg(QCTNAME(caster) + " touches " + QCOMPDEAD +
                   " while trying to read its secrets.\n");

}

/*
 * Function:    hook_identify_sucess
 * Description: Mask this function to change the description of when
 *              the object is successfully identified.
 */
public void
hook_identify_success(object caster, object target, string id_message, int result)
{
    if (!objectp(caster) || !objectp(target))
    {
        return;
    }
    caster->catch_tell(id_message);
    target->appraise_object(caster->query_skill(query_identify_skill()) + result);
}

/*
 * Function:    hook_identify_failure
 * Description: Describes the failure to actually magically identify the
 *              object.
 */
public void
hook_identify_failure(object caster, object target)
{
    caster->catch_tell("You fail to divine any magical properties.\n");
}

/*
 * Function:    query_identify_ingredients
 * Description: This function defines what components are required for
 *              this identify spell.
 */
public string *
query_identify_ingredients(object caster)
{
    return ({ });
}
