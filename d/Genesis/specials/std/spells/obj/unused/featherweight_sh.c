/*
 * Featherweight Shadow
 * 
 * This is a default shadow that adds the featherweight effect.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 * Created by Petros, May 2010
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Global Variables
public int      Weight_factor = 100;

/*
 * Function:    has_featherweight_shadow
 * Description: Indicates that the person shadowed has the featherweight
 *              effect on them.
 */
public int
has_featherweight_shadow()
{
    return has_spell_shadow();
}

/*
 * Function:    remove_featherweight_shadow
 * Description: Removes this particular shadow
 */
public void
remove_featherweight_shadow()
{
    remove_spell_shadow();
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
 * Function:    get_weight_factor
 * Description: Returns the specified weight factor for this shadow
 */
public int
get_weight_factor()
{
    return Weight_factor;
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("lighten burden");
    spell_object->set_short("featherweight spell object");
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);

    set_weight_factor(spell_input["weight_factor"]);
}

/*
 * Function name:   max_weight
 * Description:     Calculate the maximum weight this living can budge.
 * Returns:         The weight.
 */
public int
max_weight()
{
    return (shadow_who->max_weight() * get_weight_factor()) / 100;
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
    if (prop == CONT_I_MAX_WEIGHT && intp(result))
    {
        result = (result * get_weight_factor()) / 100;
    }
    
    return result;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

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
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

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
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
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
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the featherweight effect.\n");
    }    
}
