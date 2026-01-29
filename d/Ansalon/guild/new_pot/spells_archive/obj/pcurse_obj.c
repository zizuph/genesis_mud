/*
 * Curse spell object, based on standard Illfortunate Curse shadow
 *
 * This is the spell shadow for the standard Genesis Magic System Illfortunate
 * curse spell. 
 *
 * Specific guild implementations must inherit from this one to get
 * the standard AoB approved effects.
 *
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>

#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/obj/illfortunate_sh";

#define ACTIVE_CURSE "_pot_curse_active"

int percentage_miss;


/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{   
    spell_object->set_spell_effect_desc("curse");
    spell_object->set_short("curse spell object");

    int power = spell_object->query_spell_effect_power();

    percentage_miss = spell_input["percentage_miss"];

    int duration = power / 3; 

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
    if (prop == LIVE_AS_ATTACK_FUMBLE)
    {
        if (percentage_miss <= random(100))
        {
            // Just use the base property because it didn't hit
            // the right percentage.
            return result;
        }
        string * fumble_messages = query_attack_fumble_messages();
        if (!sizeof(fumble_messages))
        {
            // If nothing is returned, we default to the base result
            return result;
        }
        string message_to_observers = query_fumble_to_observers_message();
        if (strlen(message_to_observers))
        { 
            shadow_who->tell_watcher_miss(message_to_observers, 0, 0);
        }
        return fumble_messages;
    }
    
    return result;
}


/*
 * Function:    query_attack_fumble_messages
 * Description: Override this to customize the message(s) that displays when
 *              the target actually fumbles an attack. It should return an
 *              array of strings, or 0 if there should not be a message.
 */
public string *
query_attack_fumble_messages()
{
    return ({
            "As you are about to strike your enemy you inexplicably feel " +
            "a malevolent presence behind you, and miss your opportunity.\n" 
           }); 
}

/*
 * Function:    query_fumble_to_observers_message
 * Description: Override this to retrieve the message to show observers
 *              when an attack is fumbled. Return 0 if no message should
 *              be displayed.
 */

public string
query_fumble_to_observers_message()
{
    object target = shadow_who;
    return QCTNAME(target) + " is overcome with paranoia as " +HE(target)+
           " is about to attack, missing " +HIS(target)+ " opportunity.\n";
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
        target->catch_tell("Your feel the malevolent attention of a dark " +
           "goddess upon you.\n");
        tell_room(environment(target), QCTNAME(target) + " has been "
            + "cursed with the malevolent attention of Takhisis, Queen " +
            "of Darkness, and her unholy pantheon.\n", ({ target }));
        target->add_prop(ACTIVE_CURSE, 1);
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The malevolent curse upon you disappears.\n");
        tell_room(environment(target), QCTPNAME(target) + " malevolent curse "
            + "disappears.\n", ({ target }));
        target->remove_prop(ACTIVE_CURSE);
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
            + "curse on " + QTNAME(target) + " begin to waver.\n");
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
            + "the curse.\n");
    }    
}


