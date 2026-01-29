/*
 * Support Shadow for the Prop Change Base Spell
 *
 * This shadow gets cloned by the shadow object when the spell
 * is cast. We use this shadow to override the props in a shadow
 * instead of altering it. Using a shadow is typically safer
 * because it can handle stacking from multiple effects well.
 *
 * Created by Petros, July 2016
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPELL_OBJ_DIR + "shadow_base_sh";

// Global Variables
public mapping input_parameters;

// Prototypes

/*
 * Function     : has_propchange_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 */
public int 
has_propchange_shadow() 
{
    return has_spell_shadow();
}

/*
 * Function     : remove_propchange_shadow
 * Description  : Easy way to remove propchange shadow. 
*/
public void 
remove_propchange_shadow()
{
    remove_spell_shadow();
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    input_parameters = spell_input; // input_parameters can be used in the query_prop override
    
    spell_object->set_spell_effect_desc("propchange");
    spell_object->set_short("propchange spell object");
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    // int duration = ftoi(log(itof(power)) * 300.0);
    // Spell class and skills now determines duration

}

/*
 * Function:    query_prop
 * Description: This is the primary function that you should override to
 *              implement the propchange shadow. Make sure to return
 *              the shadow_who->query_prop(prop) result if you don't
 *              want to handle that particular prop.
 */
public mixed
query_prop(string prop)
{
    mixed result = shadow_who->query_prop(prop);
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
        target->catch_tell("Your feel your prop being changed.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "changing props.\n", ({ target }));
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
        target->catch_tell("Your prop change disappears.\n");
        tell_room(environment(target), QCTPNAME(target) + " prop change "
            + "disappears.\n", ({ target }));
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
    // Alert the caster that the effect is about to expire.
    object caster = spell_object->query_effect_caster();
    object target = spell_object->query_effect_target();
    
    if (objectp(caster) && objectp(target))
    {
        caster->catch_tell("You feel your ability to maintain the "
            + "prop change on " + QTNAME(target) + " begin to waver.\n");
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
            + "the prop change effect.\n");
    }    
}
