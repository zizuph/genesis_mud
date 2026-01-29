/*
 * Reflect Shadow
 * 
 * This is a default shadow that allows reflect objects to be added
 * to it in order to support multiple stacking reflect effects
 *
 * Modified from Evade Effect Object created by Petros.
 * Created by Carnak January 2018
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"

inherit EFFECT_BASE_SH;
inherit "/d/Genesis/specials/resist.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

#include "../debugger/debugger_tell.h"

// Global Variables

/*
 * Function     : has_reflect_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int
has_reflect_shadow()
{
    return 1;
}

/*
 * Function     : remove_reflect_shadow
 * Description  : Easy way to remove shadow. Must use this otherwise the
 *                wrong shadow could be removed.
 * Arguments    : none
 * Returns      : nothing
*/
public void
remove_reflect_shadow()
{
    remove_shadow();
}

/*
 * Function     : query_reflect_percentage
 * Description  : Returns the calculated percentage of all the reflect
 *                objects that the reflect shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum reflect. The actual reflect depends on the
 *                situation in query_reflect_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
public int 
query_reflect_percentage()
{
    return query_effect_percentage();    
}

/*
 * Function     : query_reflect_combat_aid
 * Description  : Based on the results of query_reflect_percentage
 *                This gives the total combat aid given by reflect
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stack*ing combat aid
 */
public int
query_reflect_combat_aid()
{
    return query_effect_combat_aid();
}

/*
 * Function     : remove_reflect_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
public nomask void
remove_reflect_effect(object obj)
{
    obj->hook_effect_ended(obj);
    remove_effect(obj);
    send_debug_message("reflect_sh", "Removing reflect effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : add_reflect_effect
 * Description  : Adds the reflect effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask void
add_reflect_effect(object obj)
{
    add_effect(obj);
    obj->hook_effect_started(obj);
    send_debug_message("reflect_sh", "Adding reflect effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : query_reflect_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the reflect shadow
 * Arguments    : none
 * Returns      : array of reflect effect objects
 */
public object *
query_reflect_effects()
{
    return query_effects();
}


/*
 * Function     : report_total_reflect_percentage
 * Description  : Called by query_not_attack_me to report how much
 *                the total valid reflect percentage is for the
 *                reflectr.
 * Arguments    : percentage - amount to report
 * Returns      : Nothing.
 */
public void
report_total_reflect(int percentage, int caid)
{
    send_debug_message("reflect_sh_total", 
        capitalize(shadow_who->query_real_name())
        + " has a total reflect of " 
        + percentage + "% with a combat aid of " + caid + "%.");
}


/*
 * Function:    do_reflect_damage
 * Description: Function that gets called via alarm to actually execute the reflective
 *              damage.
 */
public void
do_reflect_damage(int wcpen, int dt, object attacker, int att_id)
{
    object *valid_reflects;
    mixed   reflect_results;
    int     total_reflect_aid, reflect_pen,
            reflect_percentage, reflect_dt,
            caid, resist;
    float   total_reflect_percentage;
    
    valid_reflects = ({ });
    total_reflect_aid = 0;

    if (!objectp(attacker) || !objectp(shadow_who)) 
    {
        return;
    }
    
    foreach (object effect : query_reflect_effects())
    {
        // Just in case there's an invalid object
        if (!effect)
           continue;
        
        // Filter out the allowed hitlocs
        if (!effect->query_allow_target_hitloc(att_id))
        {
            send_debug_message("reflect_sh", "Hitloc " + att_id + " not allowed.");
            continue;
        }
        // The damage reflection doesn't always happen. We randomize when it does.
        if (random(100) >= effect->query_reflect_damage_likelihood())
        {
            send_debug_message("reflect_sh", "Failed due to likelihood.");
            continue;
        }
        
        if (att_id == -1)
        {
            // Check if it's a special and if it's allowed
            if (!effect->query_allow_specials() && dt != MAGIC_DT)
            {
                send_debug_message("reflect_sh", "Special not allowed.");
                continue;
            }
            
            // Check if it's a magic attack and if it's allowed
            if (!effect->query_allow_magic_attacks() && dt == MAGIC_DT)
            {
                send_debug_message("reflect_sh", "Magic not allowed.");
                continue;
            }
        }
        else if (!effect->query_allow_white_attacks())
        {
            // Check if it reflects white hits
            send_debug_message("reflect_sh", "White hits not allowed.");
            continue;
        }
        
        if (!effect->query_reflect_valid(shadow_who, attacker, att_id))
        {
            send_debug_message("reflect_sh", capitalize(effect->query_name())
                             + " cannot reflect in the current situation.");
            continue;
        }
        
        valid_reflects += ({ effect });
        reflect_percentage = effect->query_reflect_strength(shadow_who, 
                                                        attacker, att_id);
        send_debug_message("reflect_sh", "Caid: " + reflect_percentage + ".");
        caid = (reflect_percentage * 100) / (100 - reflect_percentage);
        send_debug_message("reflect_sh", "Caid: " + caid + ".");
        caid = caid * 100 / effect->query_reflect_damage_likelihood();
        send_debug_message("reflect_sh", "Real effect caid: " + effect->query_effect_combat_aid() + ".");
        total_reflect_aid += caid;
        send_debug_message("reflect_sh", capitalize(effect->query_name())
            + " contributing " + reflect_percentage + "% reflect with "
            + caid + "% combat aid for a total of " + total_reflect_aid
            + "% combat aid.");
    }
    
    if (!sizeof(valid_reflects))
    {
        return;
    }
    
    total_reflect_percentage =  (100.0 * itof(total_reflect_aid)) /
                                (100.0 + itof(total_reflect_aid));
    // Call the reporting function
    report_total_reflect(ftoi(total_reflect_percentage), total_reflect_aid);
    
    if (total_reflect_percentage > 0.0)
    {
        object effect = one_of_list(valid_reflects);
        send_debug_message("reflect_sh", capitalize(effect->query_name()) 
        + " caused an reflect.");
        
        reflect_pen = wcpen * ftoi(total_reflect_percentage) / 100;
        send_debug_message("reflect_sh", "Unmodified pen: " + wcpen
        + " after " + ftoi(total_reflect_percentage) + " percentage mod: "
        + reflect_pen + ".");
        
        reflect_dt = effect->query_reflect_damage_type();
        if (reflect_dt == MAGIC_DT)
        {
            resist = combine_resistances(attacker, effect->query_reflect_resistance_type());
            reflect_pen = reflect_pen * min(100, max(100 - resist, 0)) / 100;
            
            // One final modification to pen is to match non-magic calculation
            // inside of cb_hit_me, using F_NEW_DAMAGE formula. We multiply the
            // resistance by 80% to give it a chance that the pen goes to 0
            if (random(100) < (resist * 80 / 100))
            {
                reflect_pen = 0;
            }
        }
        send_debug_message("reflect_sh", "Pen after resist: " + reflect_pen + ".");
        
        // Hit the attacker back
        reflect_results = attacker->hit_me(reflect_pen, reflect_dt, shadow_who, -1);
        // Display the attack message
        effect->hook_reflect_damage_description(shadow_who, attacker, reflect_results);
        // If the attacker dies as a result, call do_die
        if (attacker->query_hp() < 1)
        {
            attacker->do_die(shadow_who);
        }
    }
}

/*
 * Function name: hit_me
 * Description:   Called to decide damage for a certain hit on 'me'.
 * Arguments:     wcpen:         Weapon class penetration
 *                dt:            Damage type, MAGIC_DT if no ac helps
 *                attacker:      Person/object doing the damage 
 *                attack_id:     -1 if a special attack
 *                target_hitloc: The hit location to damage.  If left
 *                               unspecified or an invalid hitloc is
 *                               given, a random hitlocation will be
 *                               used.
 * Returns:       Array: ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
 *                int proc_hurt - 0-100, incurred damage as percentage of
 *                     victim HP, or -1 = dodge, -2 = parry.
 *                string hitloc desc - descr. of the location that was hit.
 *                int phit - randomized value of the weapon penetration (wcpen)
 *                int dam - incurrent damage in hitpoints
 *                int hitloc ID - the ID of the location that was hit.
 */
public varargs mixed
hit_me(int wcpen, int dt, object attacker, int att_id, int target_hitloc = -1)
{
    // First call the default hit_me and get the results.
    mixed results = shadow_who->hit_me(wcpen, dt, attacker, att_id, target_hitloc);

    // If there was no damage done, then we don't bother reflecting anything.
    if (sizeof(results) >= 4 && results[3] == 0)
    {
        send_debug_message("reflect_sh", "No damage done.");
        return results;
    }
    
    object attacker_combat_object = attacker->query_combat_object();
    if (!sizeof(attacker_combat_object->query_attack(att_id)))
    {
        // Something is wrong since the attacker's combat object doesn't
        // recognize this attack id. In this case, we don't allow this damage
        // to be reflected. We must give an exception to -1 as we can allow
        // spells and specials.
        if (att_id != -1)
            return results;
        
        send_debug_message("reflect_sh", "Incorrect attack_id.");
    }

    // Why did we allow reflect_damage to be reflected? While not infinite, it
    // should loop quite a bit, so I added a check for previous function.
    // Carnak
    if (calling_function() == "do_reflect_damage")
    {
        send_debug_message("reflect_sh", "Unable to reflect a reflect.");
        return results;
    }
    
    send_debug_message("reflect_sh", "Reflect hit_me completed.");

    /* do_reflect_damage needs to be executed from an alarm to allow the attackers 
     * round to finish. Otherwise the hit attempt can result in the attackers death
     * and that will cause runtimes.
     */
    set_alarm(0.0, 0.0, &do_reflect_damage(wcpen, dt, attacker, att_id));
    return results;
}
