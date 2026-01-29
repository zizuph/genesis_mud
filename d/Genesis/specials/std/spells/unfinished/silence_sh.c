/*
 * Support Shadow for the silence spell, based off the 
 * Illfortunate Spell.
 *
 * This shadow gets cloned by the shadow object when the spell
 * is cast. We use this shadow to override the LIVE_AS_ATTACK_FUMBLE
 * prop instead of altering it. There are many effects that alter
 * this property and using a shadow is "safer" as it should not
 * cause an interaction issue.
 *
 * Adapted from code from Petros by Arman, Sept 2017
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>

#ifndef LIVE_M_MOUTH_BLOCKED
#define LIVE_M_MOUTH_BLOCKED   ("_live_m_mouth_blocked")
#endif

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

// Global Variables
public int silence_duration_modifier = 0;

/*
 * Function     : has_silence_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 */
public int 
has_silence_shadow() 
{
    return 1;
}

/*
 * Function     : remove_silence_shadow
 * Description  : Easy way to remove silence shadow. 
*/
public void 
remove_silence_shadow()
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
    // silence duration modifier formula is 
    // (100 * combat_aid) / (100 + combat_aid) 
    // 100 caid equates to 50% duration (15 seconds), 
    // 50 caid equates to 33% duration (10 seconds)
    // while 25 caid equates to 20% duration (6 seconds).

    silence_duration_modifier = spell_input["silence_duration"];
    silence_duration_modifier = min(silence_duration_modifier, 100);
    silence_duration_modifier = max(silence_duration_modifier, 1);
    
    spell_object->set_spell_effect_desc("silence");
    spell_object->set_short("silence spell shadow");   

    // 30 second max duration
    int duration = ftoi((itof(silence_duration_modifier) / 100.0) * 30.0);
    spell_object->set_dispel_time(duration);
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

    if (prop != LIVE_M_MOUTH_BLOCKED)
    {
        return result;
    }
    
    if (intp(result))
    {
        return "You have been magically silenced! You are unable to do that.\n";
    }
    else 
    {
        return 1;
    }
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
        target->catch_tell("Your feel yourself magically silenced!\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "magically silenced.\n", ({ target }));
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
        target->catch_tell("You are no longer magically silenced.\n");
        tell_room(environment(target), QCTNAME(target) + " is no longer "
            + "magically silenced.\n", ({ target }));
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
            + "magical silence on " + QTNAME(target) + " begin to waver.\n");
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
            + "the magical silence.\n");
    }    
}
