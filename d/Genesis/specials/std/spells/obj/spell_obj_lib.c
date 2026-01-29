/*
 * Standard Spell Object Library
 *
 * This is the standard spell object library used by the new Genesis Magic
 * System. This spell object will be the base of all duration effects.
 * It is not an object. For the actual spell obj, please look at
 * spell_obj_base.c.
 *
 * When this library is used, be sure and also include auto_remove.h and
 * implement and call create_spell_object.
 *
 * Example Skeleton Spell Object
 * 
 *   #include <stdproperties.h>
 *   #include <macros.h>
 *
 *   inherit "/std/object";
 *   inherit "/d/Genesis/specials/std/spells/obj/spell_obj_lib";
 * 
 *   #include "auto_remove.h"
 * 
 *   public void
 *   create_object()
 *   {
 *       ... // standard create stuff.
 *       create_spell_object();
 *   } 
 *
 * Created by Petros, September 2009
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit "/d/Genesis/specials/spell_effect_object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define MAINTAIN_INTERVAL   60.0
#define MINIMUM_WARNING_SPELL 300

// Global Variables
public int      Warning_seconds = 60;
public int      Warning_alarm = 0;
public mixed    Spell_input   = 0;
public int      Maintain_mana = 5;
public int      Initial_duration = 0;
public string   Spell_notes       = "";

// Prototypes
public void     hook_spell_effect_started();
public void     hook_spell_effect_ended();
public void     hook_spell_effect_not_maintained();
public void     hook_spell_effect_warn_fading();
public int      query_spell_effect_still_valid();
public int      query_maintain_mana();

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void
create_spell_object()
{
}

/*
 * Function:    maintain_spell_effect
 * Description: In order to continue functioning, the spell effect
 *              must cause the caster to lose mana.
 */
public nomask void
maintain_spell_effect()
{
    object caster = query_effect_caster();
    if (!objectp(caster)
        || caster->query_mana() < query_maintain_mana()
        || caster->query_ghost())
    {
        set_alarm(0.0, 0.0, &dispel_effect(caster));
        hook_spell_effect_not_maintained();
        return;
    }
    
    if (!query_spell_effect_still_valid())
    {
        set_alarm(0.0, 0.0, &dispel_effect(caster));
        return;
    }
    
    send_debug_message("spell_obj_base", query_spell_effect_name()
        + " reduces " + query_maintain_mana() + " mana from "
        + capitalize(caster->query_real_name()) + ".");
    caster->add_mana(-query_maintain_mana());
}

/*
 * Function:    query_maintain_mana
 * Description: Returns how much mana it takes to maintain the
 *              mana for this effect object
 */
public int
query_maintain_mana()
{
    return Maintain_mana;   
}

/*
 * Function:    set_maintain_mana
 * Description: Change the default mana amount taken for every
 *              maintenance interval. By default, this is set to
 *              5. Please have a good reason for changing it.
 */
public int
set_maintain_mana(int mana)
{
    Maintain_mana = mana;
}

/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    return 1;
}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the effects in the spell.
 *              Anything done here should be reversed during the
 *              matching dispel_spell_effect function.
 *              Duration effects take a constant amount of mana to
 *              maintain. If the caster doesn't have enough mana to
 *              maintain the effect, then it is dispelled.
 *              We set up the alarm in this setup.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    
    // Move the spell object to the target
    object target = query_effect_target();
    if (!objectp(target))
    {
        return result;
    }
    
    // Check whether the target is a container or not. If not, then the spell
    // object will be retained by the caster. The caster also keeps the spell
    // object if there's a problem moving to the target. (move returns 0 for success)
    if (IS_CONTAINER_OBJECT(target) || this_object()->move(target, 1))
    {
        object caster = query_effect_caster();
        if (objectp(caster))
        {
            this_object()->move(caster, 1);
        }
    }
    hook_spell_effect_started();
        
    // Set up an alarm to reduce mana every minute
    set_alarm(MAINTAIN_INTERVAL, MAINTAIN_INTERVAL, &maintain_spell_effect());
    return result;
}

/*
 * Function name: dispel_spell_effect
 * Description:   Cause this spell effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_spell_effect(object dispeler)
{
    int result = ::dispel_spell_effect(dispeler);
    if (!result)
    {
        return result;
    }
    
    hook_spell_effect_ended();
    return result;
}

/*
 * Function:    remove_spell_object
 * Description: Calls the base remove_object function
 */
public void
remove_spell_object()
{
}

/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
public varargs nomask int
dispel_effect(object dispeler)
{
    object target = query_effect_target();
    if (objectp(target) && target->query_npc())
    {
        // For automation, make sure that we notify that the npc caster gets
        // notified that the effect has ended.
        target->notify_spell_effect_complete(this_object());
    }
    set_alarm(0.0, 0.0, &remove_spell_object());
    return ::dispel_effect(dispeler); 
}

/*
 * Function:    set_dispel_time
 * Description: Creates a timer that will dispel the effect
 * Arguments:   i - number of seconds before the effect vanishes                
 */
public void 
set_dispel_time(int i)
{
    ::set_dispel_time(i);
 
    // Store the initial duration in case we want to "renew" this effect
    Initial_duration = i;   
    
    // We remove any existing warning alarm
    remove_alarm(Warning_alarm);
    Warning_alarm = 0;
    if (i > MINIMUM_WARNING_SPELL)
    {
        // Only set up warnings for effects that are longer
        // than 5 minutes
        Warning_alarm = set_alarm(itof(i - Warning_seconds), 0.0, 
            &hook_spell_effect_warn_fading());
    }
}

/*
 * Function:    renew_spell_duration
 * Description: Allows an existing spell object to be renewed in its
 *              duration. Useful for recasting a spell that you don't
 *              want to expire.
 */
public void
renew_spell_duration()
{
    set_dispel_time(Initial_duration);
}

/*
 * Function:    query_spell_effect_input
 * Description: This function returns whatever input that the spell
 *              passed into the spell effect
 */
public mixed
query_spell_effect_input()
{
    return Spell_input;    
}

/*
 * Function:    set_spell_effect_input
 * Description: Allows one to pass any arbitrary input to the spell
 *              effect.
 */
public void
set_spell_effect_input(mixed input)
{
    Spell_input = input;
}

/*
 * Function:    query_spell_effect_notes
 * Description: This function returns whatever notes that the spell
 *              passed into the spell effect
 */
public string
query_spell_effect_notes()
{
    return Spell_notes;    
}

/*
 * Function:    set_spell_effect_notes
 * Description: Allows one to set notes that the player can see
 *              when they use the <spelleffects> and <spellnotes>
 *              commands.
 */
public void
set_spell_effect_notes(string input)
{
    Spell_notes = input;
}

/*
 * Function:    query_about_to_expire
 * Description: If the warning alarm was set for this, this will
 *              inform the user whether the spell effect already
 *              warned the user it was going to expire.
 */
public int
query_about_to_expire()
{
    mixed effect_alarm = get_alarm(alarm_id);
    
    if (!pointerp(effect_alarm))
    {
        // Should never happen! We should always have an effect alarm
        return 0;
    }
    
    if (effect_alarm[2] < itof(Warning_seconds))
    {
        return 1;
    }
    
    return 0;
}

// HOOKS TO BE DEFINED
/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    object target = query_effect_target();
    
    if (objectp(caster))
    {
        if (objectp(target))
        {
            if (target != caster)
            {
                caster->catch_msg("You are unable to maintain the spell "
                    + "effect upon " + QTNAME(target) + ".\n");
            }
            else
            {
                caster->catch_tell("You are unable to maintain the spell "
                    + "effect upon yourself.\n");
            }
        }
    }    
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
        target->catch_tell("The spell effect upon you begins.\n");
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
        target->catch_tell("The spell effect upon you ends.\n");
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
        target->catch_tell("The spell effect is about to end.\n");
    }
}
