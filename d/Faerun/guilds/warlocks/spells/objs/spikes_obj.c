/*
 * Reflect Damage Object
 */
 
#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/reflect_obj";

#include "/d/Faerun/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */

public void 
create_spell_object()
{
    ::create_spell_object();
    
    set_name("_spikes_object_");
    set_spell_effect_desc("Shadowy Spikes");
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Transparent shadowy spikes suddenly "
        +"cover your body! They will "
        +"do additional harm back to potential attackers.\n");
           
        tell_room(environment(target), QCTNAME(target) 
        + " is suddenly covered by transparent shadowy spikes!\n", 
        ({ target }));
            
        target->add_subloc(REFLECT_SUBLOC, this_object());
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
hook_spell_effect_ended()
{
    object target = query_effect_target();
    
    target->remove_prop(SPIKES_EFFECT);
    target->remove_prop(SHIELD_ON);
    
    if(target->query_ghost())
        return;
    
    if (objectp(target))
    {
        target->catch_tell("You are no longer covered by "
        +"transparent shadowy spikes.\n");
        
        tell_room(environment(target), QCTNAME(target) + " is no longer "
            + "covered with transparent shadowy spikes.\n", ({ target }));
            
        target->remove_subloc(REFLECT_SUBLOC);
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
        target->catch_tell("You sense your Ormule "
        +"starts to fade away.\n");
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
            + "Ormule.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_describe_reflect_effect(object player, object attacker, mixed results)
{
    int phurt = results[0];
    int dam = results[3];
    string dam_desc;
    
    switch (phurt) // percentage hurt
    {
        case 0..7:
          dam_desc = "slight";
        break;
        case 8..20:
          dam_desc = "";
        break;
        case 21..45:
          dam_desc = "great";
        break;
        default:
          dam_desc = "severe";
        break; 
    }
    
    attacker->catch_msg("As you lunge forward in an attempt to hit "
    + QTNAME(player) + ", the transparent shadowy spikes surrounding "
    +HIM_HER(player)+" strike back with dark energy, inflicting "
    +dam_desc+" pain.\n");  
        
    player->catch_msg("The transparent shadowy spikes surrounding you "
    +"strike back at "+ QTNAME(attacker)+", inflicting "
    +dam_desc+" pain.\n");  
          
    tell_room(environment(player), "As "+QCTNAME(attacker) 
    +" lunges forward in attempt to hit "+ QTNAME(player)
    +", the transparent shadowy spikes surrounding "+HIM_HER(player)
    +"strike back with dark energy, inflicting "+dam_desc
    +" pain.\n", ({ attacker, player }));
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
        return on->show_subloc(subloc, on, for_obj); 
    }
    
    return query_reflect_subloc_description(on, for_obj);
}
