/*
 * Standard Paranoia Object
 *
 * This is the spell object for the standard Genesis Magic System's
 * paranoia spell. It makes the target paranoid for a limited duration,
 * hearing voices etc.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Navarre, October 2010.
 * Adapted by Petros, August 2012
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit SPELL_OBJ_DIR + "spell_obj_base";

/* Prototypes. */
public void hook_do_paranoid_effect(object caster, object target, mixed * history);

/* The effect alarm */
int paranoid_effect_alarm = 0;

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_paranoia_object_");
    set_short("paranoia spell object");    
    set_long("This is the standard paranoia spell object. " +
             "It makes the target paranoid.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the paranoia spell.\n");
    set_spell_effect_desc("paranoia");

}

/*
 * Function:    query_paranoia_effect_interval
 * Description: Returns the time before the next paranoia effect should happen.
 */
public float
query_paranoia_effect_interval()
{
    return 30.0 + itof(random(30));
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
    paranoid_effect_alarm =
        set_alarm(query_paranoia_effect_interval(),
                  0.0,
                  &hook_do_paranoid_effect(query_effect_caster(),
                                           query_effect_target(),
                                           0));
    
    set_dispel_time(get_default_spell_time());

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
        
    remove_alarm(paranoid_effect_alarm);
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
        target->catch_tell("You feel a paranoia setting in.\n");
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
        target->catch_tell("The cloud in your mind subsides.\n");
    }
    
    object caster = query_effect_caster();
    if (objectp(caster))
    {
        caster->catch_msg("You are no longer maintaining paranoia on "
            + QTNAME(target) + ".\n");
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
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel your ability to maintain paranoia "
            + "start to fade.\n");
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
            + "the paranoia upon your target.\n");
    }    
}

/*
 * Function    : hook_do_paranoid_effect
 * Description : Function to be overridden to provide specific paranoia messages.
 * Arguments   : object caster - The person responsible for the paranoid, can be 0.
 *             : object target - The person being paranoid.
 *             : mixed * history - Historical context of the previous paranoid
 *                                 effects already experienced. Can help to 
 *                                 determine the next effect.
 */
public void
hook_do_paranoid_effect(object caster, object target, mixed * history)
{
    // We update the history
    if (!pointerp(history))
    {
        history = ({ 1 });
    }
    else
    {
        history = ({ history[0] + 1 }) + history;
    }
    
    if (objectp(target))
    {
        switch (history[0] % 2)
        {
        case 0:
            target->catch_msg("You feel someone following you.\n");
            break;
        
        case 1:
            target->catch_msg("A strong green goblin attacks you!\n");
            break;
        }
    }
    
    // Set the next paranoia effect alarm
    paranoid_effect_alarm =
        set_alarm(query_paranoia_effect_interval(),
                  0.0,
                  &hook_do_paranoid_effect(query_effect_caster(),
                                           query_effect_target(),
                                           history));    
}
