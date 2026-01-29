/*
 *  Support shadow for the standard invisibility spell. Monitors attacks
 *  on and by the player and removes the invisibility effect.
 *
 *  Created by Eowul, July 2010, borrowed by Nerull 2021.
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/invisibility_sh";

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../../guild.h"




// Prototypes
public void     hook_spell_no_fighting(object spell_object, object target);


/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    object spell_effect = spell_object;
    
    spell_object->set_spell_effect_desc("obfuscate");
    spell_object->set_short("invisibility spell object");

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
        target->catch_tell("You turn invisible to the naked eye.\n");
           
        tell_room(environment(target), QCTNAME(target)+ " fades from view.\n", ({ target }));
    }
    
    invis_in_effect = 1;
    
    target->add_prop(IAM_OBFUSCATED, 1);
    
    // Need to call the property change functions
    int oldvalue = shadow_who->query_prop(OBJ_I_INVIS);
    
    int newvalue = oldvalue + 1;
    
    call_other(shadow_who, "add_prop_obj_i_invis", newvalue); 
    
    if (environment())
    {
        environment()->notify_change_prop(OBJ_I_INVIS, newvalue, oldvalue);
        
        environment()->hook_change_invis(shadow_who);
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
    invis_in_effect = 0;
    
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You " +
           "return back to normal sight.\n");
           
        tell_room(environment(target), QCTNAME(target) + " appears "
            + "from nowhere.\n", ({ target }));
    }
    
    target->remove_prop(IAM_OBFUSCATED);
    
    // Need to call the property change functions
    int newvalue = shadow_who->query_prop(OBJ_I_INVIS);
    
    int oldvalue = newvalue + 1;
    
    if (newvalue <= 0)
    {
        call_other(shadow_who, "remove_prop_obj_i_invis");
    }
    
    if (environment())
    {
        environment()->notify_change_prop(OBJ_I_INVIS, newvalue, oldvalue);
        environment()->hook_change_invis(shadow_who);
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
        target->catch_tell("You feel you will soon be visible again.\n");
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
            + "Obfuscate.\n");
    }    
}


/*
 * Function:    hook_spell_no_fighting
 * Description: Override this to describe the effect when the caster 
 *              engages someone into battle.
 * Arguments:   target - our enemy that caused us to dispel the effect
 */
public void
hook_spell_no_fighting(object spell_object, object target)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You cannot fight while invisible.\n");
    }    
}
