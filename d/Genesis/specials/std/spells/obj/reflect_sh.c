/*
 * Reflect Damage Shadow
 * 
 * This is a default shadow that reflects damage inflicted on the person
 * that has been shadowed.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 * The shadow code for the reflect damage effect was originally from the helm in
 * kendermore and adapted. Credit goes to Navarre for work on that armour. It
 * has been heavily adapted for use by the Genesis Magic System.
 *
 * Created by Petros, September 2012
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Defines
#define RESIST_LIBRARY          "/d/Genesis/specials/resist"
#define REFLECT_SUBLOC          "_reflect_spell_effect_subloc"

// Global Variables
public int      g_bAllowSpecials = 0;
public int      g_bAllowMagicAttacks = 0;
public int *    g_excludedTargetHitLocations = ({ });
public int      g_nCombatAid = 25;
public int      g_damageType = MAGIC_DT;
public int      g_nLikelihood = 75;
public string * g_resistance_types = ({ });

// Function Declarations
public void     set_allow_specials(int bAllowSpecials);
public void     set_allow_magic_attacks(int bAllowMagicAttacks);
public void     set_excluded_target_hit_locations(int * excludedTargetHitLocations);
public void     set_reflect_damage_combat_aid(int nCombatAid);
public void     set_reflect_damage_type(int damageType);
public void     set_reflect_damage_likelihood(int likelihood);
public void     set_reflect_resistance_types(string * resistances);

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
    spell_object->set_spell_effect_desc("reflect damage");
    spell_object->set_short("reflect damage spell object");
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);

    // Set the specific for this instance
    set_allow_specials(spell_input["allow_specials"]); 
    set_allow_magic_attacks(spell_input["allow_magic_attacks"]);
    set_excluded_target_hit_locations(spell_input["excluded_hit_locations"]); 
    set_reflect_damage_type(spell_input["damage_type"]);
    set_reflect_damage_combat_aid(spell_input["combat_aid"]);
    set_reflect_damage_likelihood(spell_input["likelihood"]);
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
        target->catch_tell("You feel you can reflect damage.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be able "
            + "to reflect damage.\n", 
            ({ target }));
        shadow_who->add_subloc(REFLECT_SUBLOC, this_object());
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
        target->catch_tell("You can no longer reflect damage.\n");
        tell_room(environment(target), QCTNAME(target) + " seems to be "
            + "unable to reflect damage anymore.\n", ({ target }));
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
        target->catch_tell("You sense your ability to reflect damage start "
            + "to decrease.\n");
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
            + "the reflect damage effect.\n");
    }    
}


// BELOW THIS LINE IS THE ACTUAL REFLECT DAMAGE SHADOW SPECIFIC CODE

/*
 * Function:    set_reflect_damage_likelihood
 * Description: Sets the percentage chance that the reflect damage will
 *              actually happen.
 */
public void
set_reflect_damage_likelihood(int likelihood)
{
    g_nLikelihood = max(1, min(100, likelihood));
}

/*
 * Function:    query_reflect_damage_likelihood
 * Description: Returns the percentage chance that the reflect damage will
 *              actually happen.
 */
public int
query_reflect_damage_likelihood()
{
    return g_nLikelihood;
}

/*
 * Function:    set_reflect_damage_combat_aid
 * Description: Sets the combat aid that will be provided by this reflect
 *              damage effect.
 *              25% aid == 20% reflected damage.
 */
public void
set_reflect_damage_combat_aid(int nCombatAid)
{
    g_nCombatAid = max(1, min(100, nCombatAid));
}

/*
 * Function:    query_reflect_damage_combat_aid
 * Description: Returns the combat aid that this reflect damage effect will
 *              have.
 */
public int
query_reflect_damage_combat_aid()
{
    return g_nCombatAid;
}

/*
 * Function:    set_reflect_damage_type
 * Description: Sets the damage type that should be inflicted on the attacker.
 *              Should be one of the values defined in /sys/wa_types.h.
 */
public void
set_reflect_damage_type(int damageType)
{
    g_damageType = damageType;
    switch (g_damageType)
    {
    case W_IMPALE:
    case W_SLASH:
    case W_BLUDGEON:
    case MAGIC_DT:
        break;
    
    default:
        // Ensure that if an invalid type gets set, we set it correctly.
        g_damageType = MAGIC_DT;
    }
}

/*
 * Function:    query_reflect_damage_type
 * Description: Returns the damage type that should be inflicted on attacker
 */
public int
query_reflect_damage_type()
{
    return g_damageType;
}

/*
 * Function:    set_allow_specials
 * Description: Usually called in the initialize_shadow function. This set
 *              whether the reflective damage will apply when specials
 *              are executed against this player.
 */
public void
set_allow_specials(int bAllowSpecials)
{
    g_bAllowSpecials = bAllowSpecials;
}

/*
 * Function:    query_allow_specials
 * Description: Returns whether reflective damage will apply when specials
 *              are executed against this player
 */
public int
query_allow_specials()
{
    return g_bAllowSpecials;
}

/*
 * Function:    set_allow_magic_attacks
 * Description: Usually called in the initialize_shadow function. This sets
 *              whether the reflective damage will apply when the attack
 *              is a magic attack, like a spell.
 */
public void
set_allow_magic_attacks(int bAllowMagicAttacks)
{
    g_bAllowMagicAttacks = bAllowMagicAttacks;
}

/*
 * Function:    query_allow_magic_attacks
 * Description: Returns whether reflective damage will apply when the attack
 *              is a magic attack, like a spell.
 */
public int
query_allow_magic_attacks()
{
    return g_bAllowMagicAttacks;
}

/*
 * Function:    set_excluded_target_hit_locations
 * Description: Sets up the locations that should not reflect damage. The
 *              argument is an integer array of the hit locations.
 */
public void      
set_excluded_target_hit_locations(int * excludedTargetHitLocations)
{
    if (sizeof(excludedTargetHitLocations))
    {
        g_excludedTargetHitLocations = excludedTargetHitLocations + ({ });
    }
    else
    {
        g_excludedTargetHitLocations = ({ });
    }
}

/*
 * Function:    query_allow_target_hitloc
 * Description: The argument target_hitloc is the hitloc that actually hit
 *              the player. Here we determine whether the reflective damage
 *              will occur based on where it hit. For example, if the effect
 *              only applies when A_HEAD is the target hitloc, then a check
 *              will check for A_HEAD.
 */
public int
query_allow_target_hitloc(int target_hitloc)
{
    // The default implementation of this function is to allow everything
    // unless it is specifically excluded.
    if (IN_ARRAY(target_hitloc, g_excludedTargetHitLocations))
    {
        return 0;
    }
    
    return 1;
}

/*
 * Function:    set_reflect_resistance_types
 * Description: Allows the setting of the types of resistances that
 *              should be checked when dealing magic damage.
 */
public void     
set_reflect_resistance_types(string * resistances)
{
    if (!sizeof(resistances))
    {
        g_resistance_types = ({ MAGIC_I_RES_MAGIC });
    }
    else
    {
        g_resistance_types = resistances;
        if (!IN_ARRAY(MAGIC_I_RES_MAGIC, g_resistance_types))
        {
            g_resistance_types += ({ MAGIC_I_RES_MAGIC });
        }
    }
}

/*
 * Function:    query_reflect_resistance_types
 * Description: Returns the types of resistances that should be
 *              checked whenever magic damage is being dealt
 */
public string *
query_reflect_resistance_types()
{
    return g_resistance_types;
}

/*
 * Function:    query_reflect_resistance
 * Description: Should return the resistance that the target has to this
 *              magical reflect. By default, it only returns the resistance
 *              to standard magic. Element based resistance will need to
 *              be overridden.
 */
public int
query_reflect_resistance(object target)
{
    return RESIST_LIBRARY->combine_resistances(target, query_reflect_resistance_types());
}

/* 
 * Function:    hook_is_valid_attack
 * Description: Returns whether the attack qualifies for a reflective
 *              damage. This function should be overridden if someone
 *              wants to use any special conditions.
 */
public int
hook_is_valid_attack(int wcpen, int dt, object attacker, int attack_id, int target_hitloc)
{
    return 1;
}

/*
 * Function:    query_reflect_damage_percentage
 * Description: Returns the percentage of damage that should be reflected
 *              based on the combat aid.
 */  
public nomask float
query_reflect_damage_percentage()
{
    int caid = query_reflect_damage_combat_aid();
    
    // Formula for calculating percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    return max(0.0, (100.0 * itof(caid)) / (100.0 + itof(caid)));    
}

/*
 * Function:    hook_reflect_damage_description
 * Description: Override this function to set your own descriptions on
 *              what happens when the damage gets reflected.
 */
public void
hook_reflect_damage_description(object attacker, mixed hitme_results)
{
    attacker->catch_msg("Your attack on " + QTNAME(shadow_who) + " ends up "
        + "hurting you also.\n");
    shadow_who->catch_msg("The attack on you by " + QTNAME(attacker)
        + " backfires and ends up hurting " + attacker->query_objective()
        + " also.\n");
    tell_room(environment(shadow_who), QCTNAME(attacker) + " is hurt by some "
        + "reflected damage from " + QTNAME(shadow_who) + ".\n", 
        ({ attacker, shadow_who }));
}

/*
 * Function:    do_reflect_damage
 * Description: Function that gets called via alarm to actually execute the reflective
 *              damage.
 */
public void
do_reflect_damage(int wcpen, int dt, object attacker, int attack_id, mixed hitme_results)
{
    if (!objectp(attacker))
    {
        // Double check that the attacker is still around.
        return;
    }
    
    // By default, we do the following steps:
    // 1. Multiply the wcpen by the appropriate amount based on likelihood that the
    //    attack actually happens.
    // 2. Multiply the wcpen by the percentage that should actually hit by combat aid
    // 3. Adjust the wcpen by the resistance amount/value
    // 3. Hit the attacker with the specified damage type using the special attack id
    // 4. Send out the appropriate messages to notify the environment of the hit.
    int reflect_pen = wcpen * 100 / query_reflect_damage_likelihood();
    reflect_pen = reflect_pen * ftoi(query_reflect_damage_percentage()) / 100;
    int reflect_dt = query_reflect_damage_type();
    if (reflect_dt == MAGIC_DT)
    {
        int resist = query_reflect_resistance(attacker);
        reflect_pen = reflect_pen * min(100, max(100 - resist, 0)) / 100;
        // One final modification to pen is to match non-magic calculation inside
        // of cb_hit_me, using F_NEW_DAMAGE formula. We multiply the resistance by 80%
        // make make that the chance that the pen goes to 0
        if (random(100) < (resist * 80 / 100))
        {
            reflect_pen = 0;
        }                
    }
    
    // Hit the attacker back
    mixed reflected_hitme_results = attacker->hit_me(reflect_pen, reflect_dt, shadow_who, -1);
    // Display the attack message
    hook_reflect_damage_description(attacker, reflected_hitme_results);
    // If the attacker dies as a result, call do_die
    if (attacker->query_hp() < 1)
    {
        attacker->do_die(shadow_who);
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
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    // First call the default hit_me and get the results.
    mixed hitme_results = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    // If there was no damage done, then we don't bother reflecting anything.
    if (sizeof(hitme_results) >= 4 && hitme_results[3] == 0)
    {
        return hitme_results;
    }
    
    // The damage reflection doesn't always happen. We randomize when it does.
    if (random(100) >= query_reflect_damage_likelihood())
    {
        return hitme_results;
    }
    
    object attacker_combat_object = attacker->query_combat_object();
    if (!sizeof(attacker_combat_object->query_attack(attack_id)))
    {
        // Something is wrong since the attacker's combat object doesn't recognize this
        // attack id. In this case, we don't allow this damage to be reflected.
        return hitme_results;
    }

    // Check if it's a special and if it's allowed
    if (!query_allow_specials() && attack_id == -1)
    {
        return hitme_results;
    }
    
    // Check if it's a magic attack and if it's allowed
    if (!query_allow_magic_attacks() && dt == MAGIC_DT)
    {
        return hitme_results;
    }
    
    // Call the generic function that may be customized
    if (!hook_is_valid_attack(wcpen, dt, attacker, attack_id, target_hitloc))
    {
        return hitme_results;
    }

    // We use an alarm so that there are no infinite recursive things happening
    // if both sides have reflective damage. This may look a little weird in combat, with
    // the reflective damage perhaps happening much later in the text scrollback.
    set_alarm(0.0, 0.0, &do_reflect_damage(wcpen, dt, attacker, attack_id, hitme_results));
    
    // Return the hit_me results to the caller
    return hitme_results;
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
        return  "You are reflecting damage.\n";
    else
        return capitalize(on->query_pronoun()) + " has something that reflects "
            + "damage.\n";
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || subloc != REFLECT_SUBLOC)
    {
        return shadow_who->show_subloc(subloc, on, for_obj); 
    }
    
    return query_reflect_subloc_description(on, for_obj);
}

