/*
 * Spell Shadow
 * 
 * This is a default shadow for spell effects. It gets cloned by the shadow
 * spell object. One should inherit from this shadow only when defining shadow
 * effects. The shadow_obj.c file should automatically clone the right shadow.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 * Created by Petros, March 2011
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Global Variables
public object       m_spell_object = 0;

/*
 * Function:    remove_spell_shadow
 * Description: Helper function to ensure that the correct shadow
 *              gets removed.
 */
public nomask void
remove_spell_shadow()
{
    remove_shadow();
}

/*
 * Function:    has_spell_shadow
 * Description: Indicates that the person shadowed has the effect on them.
 */
public nomask int
has_spell_shadow()
{
    return 1;
}

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
}

/*
 * Function:    initialize_shadow_base
 * Description: Called after first cloned. Calls initialize_shadow to 
 *              do all the initialization effects for this particular shadow.
 */
public nomask void
initialize_shadow_base(object spell_object, mapping spell_input)
{
    setuid();
    seteuid(getuid());
    
    // Set up the spell_object as a member variable so that we can dispel
    // it later if needed.
    m_spell_object = spell_object;
    
    // Call the derived object's initialize_shadow
    initialize_shadow(spell_object, spell_input);
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
        target->catch_tell("You have been shadowed.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to gain " 
            + target->query_possessive() + " shadow.\n", 
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
        target->catch_tell("You lose your shadow.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to have lost "
            + "a shadow.\n", ({ target }));
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
        target->catch_tell("You sense your shadow begin to fade.\n");
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
            + "the shadow effect.\n");
    }    
}
