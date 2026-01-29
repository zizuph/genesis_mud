/*
 * Standard Illfortunate Curse Object
 *
 * This is the spell object for the standard Genesis Magic System Illfortunate
 * curse spell. 
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 * Created by Navarre, May 2013
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "../../defs.h"

inherit "/d/Genesis/specials/std/spells/obj/illfortunate_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_illfortunate_object_");
    set_short("pcurse spell object");    
    set_long("This is the illfortunate curse spell's object for the pots. " +
             "It makes it harder for the target to hit his enemies.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pcurse spell from pot.\n");
    set_spell_effect_desc("curse of the illfortunate");    
}

/*
 * This function is meant to be overridden in the guild specific code to 
 * provide the fumble message desired.
 * It is obviously possible to create an array of messages and pick a random
 * one to use.
 */
public string
query_fumble_message()
{
    return "As you are about to strike your enemy you suddenly fumble " +
            "and miss.\n"; 
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
        target->catch_tell("Your feel yourself cursed.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "cursed.\n", ({ target }));
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
        target->catch_tell("Your curse disappears.\n");
        tell_room(environment(target), QCTPNAME(target) + " curse "
            + "disappears.\n", ({ target }));
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
    // Alert the caster that the effect is about to expire.
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster) && objectp(target))
    {
        caster->catch_tell("You feel your ability to maintain the "
            + "curse on " + QTNAME(target) + " begin to waver.\n");
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
            + "the curse effect.\n");
    }    
}


