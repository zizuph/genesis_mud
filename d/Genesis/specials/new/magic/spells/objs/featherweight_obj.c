/*
 * Standard Featherweight Object
 *
 * This is the spell object for the standard Genesis Magic System Featherweight
 * spell. When started, this spell object expands the weight capacity of
 * the spell target.
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Petros, March 2013
 *
 * Changes:
 * 2021-08-22 - Cotillion
 * - Redid the scaling so it follows the special scaling. It also no longer gives 
 *   more benefit to fat and tall players. Multiple effects no longer stack as 
 *   extremely either.
 *   This spell should probably be made peacful as it has combat benefits...
 */
#pragma strict_types

#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

// Defines
#define FEATHERWEIGHT_SUBLOC        "_featherweight_subloc"
#define FEATHERWEIGHT_FUNC_PROP     "_featherweight_functions"

// Global Variables
public mixed   original_weight_function = 0;
public int     Weight_factor = 140;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_featherweight_object_");
    set_short("featherweight spell object");    
    set_long("This is the standard featherweight spell's object. It allows "
        + "a person to lighten their load\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the featherweight spell.\n");
    set_spell_effect_desc("featherweight");    
}

/*
 * Function:    set_weight_factor
 * Description: Sets the weight factor to be used in granting more carrying capacity
 */
public void
set_weight_factor(int factor)
{
    Weight_factor = factor;
}

/*
 * Function:    query_weight_factor
 * Description: Returns the specified weight factor for this shadow
 */
public int
query_weight_factor()
{
    return Weight_factor;
}

/*
 * Function:    query_original_weight_function
 * Description: Constructs the default max weight function that every
 *              living object has. This is the base from which we
 *              will build the additional weight calculations from.
 */
public function
query_original_weight_function() 
{
    object target = query_effect_target();
    if (!objectp(target)) 
    {
        return 0;
    }
    return mkfunction("max_weight", target);
}

/*
 * Function:    query_adjusted_max_weight
 * Description: Function that uses the original weight function
 *              and adds the weight factor on top of it.
 */           
public int
query_adjusted_max_weight()
{
    function f = query_original_weight_function();
    object target = query_effect_target();
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    int adjustment;
    int base_max_weight = f();

    /* This is the max carry of a 100 stat player without the race attributes */
    int extra_base = (100 + 10) * 1000; 

    int drm = target->find_drm(query_spell_stats()) / 2;

    /* Scale, should be based on spell stats when we can get that here */
    extra_base = extra_base * F_STR_FACTOR(drm) / 100;
    
    if (!pointerp(featherweight_objects)) 
    {
        return base_max_weight;
    }

    foreach (object featherweight_object : featherweight_objects)
    {
        if (!objectp(featherweight_object)) 
        {
            continue;
        }
        int weight_factor = featherweight_object->query_weight_factor();
        if (weight_factor != 0)
        {
            adjustment += ((extra_base * weight_factor) / 100) - extra_base;
        }
    }

    return max(base_max_weight + adjustment, 0);
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(log(itof(power)) * 300.0);
    // Duration now based on spell class and skills

    set_dispel_time(get_default_spell_time());
    
    mapping spell_input = query_spell_effect_input();
    set_weight_factor(spell_input["weight_factor"]);

    // Now do the actual setting of the prop
    object target = query_effect_target();
    function f = &query_adjusted_max_weight();
    target->add_prop(CONT_I_MAX_WEIGHT, f);

    // Add this spell object to the list of featherweight objects
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    if (!pointerp(featherweight_objects))
    {
        featherweight_objects = ({ });
    }
    featherweight_objects += ({ this_object() });
    target->add_prop(FEATHERWEIGHT_FUNC_PROP, featherweight_objects);

    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    object target = query_effect_target();
    // Look for any other featherweight objects to point the weight function at
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    if (!pointerp(featherweight_objects))
    {
        target->add_prop(CONT_I_MAX_WEIGHT, query_original_weight_function());
        target->remove_prop(FEATHERWEIGHT_FUNC_PROP);
        return 1;
    }

    featherweight_objects -= ({ this_object() });
    featherweight_objects -= ({ 0 });
    if (sizeof(featherweight_objects) == 0) 
    {
        target->add_prop(CONT_I_MAX_WEIGHT, query_original_weight_function());
        target->remove_prop(FEATHERWEIGHT_FUNC_PROP);
        return 1;
    } 

    function f = mkfunction("query_adjusted_max_weight", featherweight_objects[0]);
    target->add_prop(CONT_I_MAX_WEIGHT, f);
    target->add_prop(FEATHERWEIGHT_FUNC_PROP, featherweight_objects);

    return 1;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You feel your burdens decrease.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to have a heavy "
            + "burden lifted from " + target->query_objective() + ".\n", 
            ({ target }));
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your burdens feel heavier.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "weighed down.\n", ({ target }));
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense your burdens start to weigh upon you "
            + "again.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the featherweight effect.\n");
    }    
}

/*
 * Function:    query_featherweight_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_featherweight_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "Your burdens feel lighter upon you.\n";
    else
        return capitalize(on->query_pronoun()) + " looks less burdened "
            + "than usual.\n";
}

// Subloc Information

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person has a beating heart now
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (interactive(to))
    {
        to->add_subloc(FEATHERWEIGHT_SUBLOC, this_object());        
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (interactive(old))
    {
        old->remove_subloc(FEATHERWEIGHT_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != FEATHERWEIGHT_SUBLOC)
    {
        return "";
    }
    
    return query_featherweight_subloc_description(on, for_obj);
}

