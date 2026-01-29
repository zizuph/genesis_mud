/*
 * Reflect Damage Shadow
 */

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/reflect_sh";

#include "/d/Faerun/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>


/*
 * Function:    has_reflect_shadow
 * Description: Indicates that the person shadowed has the reflect_damage
 *              effect on them.
 */
public int
has_reflect_shadow()
{
    return has_spell_shadow();
}


/*
 * Function:    remove_reflect_shadow
 * Description: Removes this particular shadow
 */
public void
remove_reflect_shadow()
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
    spell_object->set_spell_effect_desc("spikes");
    spell_object->set_short("spikes object");
    
    int power = spell_object->query_spell_effect_power();

}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();
    if (objectp(target))
    {
        target->catch_tell("An aura of darkness envelops you! It will "
        +"do additional harm back to potential attackers.\n");
           
        tell_room(environment(target), QCTNAME(target) 
        + " is suddenly covered by transparent shadowy spikes!\n", 
        ({ target }));
            
        shadow_who->add_subloc(REFLECT_SUBLOC, this_object());
    } 
    
    target->add_prop(SPIKES_EFFECT, 1); 
    target->add_prop(SHIELD_ON, 1); 
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
    
    target->remove_prop(SPIKES_EFFECT);
    target->remove_prop(SHIELD_ON);
    
    if(target->query_ghost())
        return;
    
    if (objectp(target))
    {
        target->catch_tell("You are no longer covered by "
        +"transparent shadowy spikes.\n");
        
        tell_room(environment(target), QCTNAME(target) + " no longer is "
            + "covered by transparent shadowy spikes.\n", ({ target }));
            
        shadow_who->remove_subloc(REFLECT_SUBLOC);
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
        target->catch_tell("You sense your transparent shadowy "
        +"spikes starts to fade away.\n");
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
            + "the transparent shadowy spikes.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_reflect_damage_description(object attacker, mixed hitme_results)
{
    int phurt = hitme_results[0];
    int dam = hitme_results[3];
    string dam_desc;
    
    switch (phurt) // percentage hurt
    {
        case 0..7:
          dam_desc = " slight";
        break;
        case 8..20:
          dam_desc = "";
        break;
        case 21..45:
          dam_desc = " great";
        break;
        default:
          dam_desc = " severe";
        break; 
    }
    
    attacker->catch_msg("As you lunge forward in an attempt to hit "
    + QTNAME(shadow_who) + ", the transparent shadowy spikes surrounding "
    +HIM_HER(shadow_who)+" strike back with dark energy, inflicting "
    +dam_desc+" pain.\n");  
        
    shadow_who->catch_msg("The transparent shadowy spikes surrounding you "
    +"strike back at "+ QTNAME(attacker)+", inflicting "
    +dam_desc+" pain.\n");  
          
    tell_room(environment(shadow_who), "As "+QCTNAME(attacker) 
    +" lunges forward in attempt to hit "+ QTNAME(shadow_who)
    +", the transparent shadowy spikes surrounding "+HIM_HER(shadow_who)
    +"strike back with dark energy, inflicting "+dam_desc
    +" pain.\n", ({ attacker, shadow_who }));
}


/*
 * Function:    query_reflect_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_reflect_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are protected by transparent shadowy spikes.\n";
    else
        return capitalize(on->query_pronoun()) + " is protected by "
            + "transparent shadowy spikes.\n";
}


public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) 
        || subloc != REFLECT_SUBLOC)
    {
        return shadow_who->show_subloc(subloc, on, for_obj); 
    }
    
    return query_reflect_subloc_description(on, for_obj);
}
