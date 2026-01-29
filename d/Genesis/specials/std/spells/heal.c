/*
 * General Healing Spell
 *
 * Implementation of a general healing spell.  Healing spells restore
 * hit points to a target using heal_hp. It will hurt undead, however.
 *
 * Inherit this and reconfigure it for your particular heal spell.
 *
 * Created by Petros, September 2009
 */

#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_heal_spell(object caster, object * targets, int * resist, int result);
public void hook_describe_heal_result(object caster, object *targets, int * heal_amounts);
public void hook_describe_harm_result(object caster, object *targets, int * harm_amounts);
public void hook_describe_heal_cast(object caster, object * targets);

/*
 * Function:    query_heal_ingredients
 * Description: This function defines what components are required for
 *              this heal spell.
 */
public string *
query_heal_ingredients(object caster)
{
    // One herb, and one leftover. No gem requirements
    return ({ "pearl_shard", "_leftover_intestine" });
}

/*
 * Function:    config_heal_spell
 * Description: Config function for heal spells. Redefine this in your
 *              own heal spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_heal_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_combat_aid(100.0);
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
    set_spell_stationary(1);
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("heal");
    set_spell_desc("heal someone");
    set_spell_target(spell_target_one_present_living);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_ingredients(query_heal_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each heal spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 40);
    set_spell_form(SS_FORM_TRANSMUTATION, 40);
        
    // Call the specific configuration that is to be masked.
    config_heal_spell();
    
    // Call this after the config_heal_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function:    check_valid_action
 * Description: Checks conditions to see whether this spell can be cast.
 */
public int 
check_valid_action(object caster, mixed * targets, string arg, int execute)
{
    int result = ::check_valid_action(caster, targets, arg, execute);
    if (!result)
    {
        return result;
    }
    
    if (execute)
    {
        // This is a bit of a hack that will make sure that if a healing
        // spell is cast against an undead, the undead will be attacked.
        object current_enemy = caster->query_attack();
        int bChangedAttacker = 0;
        object * enemies = caster->query_enemy(-1);
        foreach (object target : targets)
        {
            if (!target->query_prop(LIVE_I_UNDEAD) || target == caster)
            {
                // Only do this check for undead. If the caster is undead,
                // don't try to attack self.
                continue;
            }
            
            if (!IN_ARRAY(target, enemies))
            {
                caster->attack_object(target);
                target->catch_msg(QCTNAME(caster) + " attacks you!\n");
                caster->catch_msg("You attack " + QTNAME(target) + ".\n");
                bChangedAttacker = 1;
            }
        }
        if (bChangedAttacker && objectp(current_enemy))
        {
            // Reset the attack to the original enemy, if applicable.
            caster->attack_object(current_enemy);
        }
    }
        
    return result;    
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, object * targets, int * resist, int result)
{
    resolve_heal_spell(caster, targets, resist, result);

    // Display the spell being cast
    hook_describe_heal_cast(caster, targets);

    // Healing Spells heal normal people, but harm undead. The harming
    // of undead is done via the undead shadow, first implemented by
    // Eowul. What this means is that healing for normal people don't
    // need resistance checks, but healing against undead need to be
    // checked for resistance.
    object * living_targets = filter(targets, not @ &->query_prop(LIVE_I_UNDEAD));
    if (caster->query_prop(LIVE_I_UNDEAD) && IN_ARRAY(caster, targets))
    {
        // If you yourself are undead, we don't try and hurt ourselves
        living_targets += ({ caster });
    }
    
    // Handle the normal Heal
    int * heal_amounts = ({ });
    foreach (object target : living_targets)
    {
        int pen = calculate_pen(0);
        // We calculate the equivalent damage done against AC 40 for
        // this pen. This becomes the heal amount for this combat aid.
        int heal_max = F_NEW_DAMAGE(pen, 100, 40) / 4;
        // Randomize heal_max a bit using similar formula to cb_hit_me
        heal_max += random(heal_max) + random(heal_max) + random(heal_max);
        int heal_amount = min(heal_max, target->query_max_hp() - target->query_hp());
        target->heal_hp(heal_amount);
        send_debug_message("heal_spell", caster->query_name()
            + " heals max of " + heal_max + " on " + target->query_name() 
            + " for " + heal_amount + " hit points.");
        heal_amounts += ({ min(heal_amount, heal_max) });
    }
    
    // Handle the Undead Harm
    object * undead_targets = targets - living_targets + ({ });
    int * harm_amounts = ({ });
    foreach (object target : undead_targets)
    {
        if (target->query_not_attack_me(caster, -1))
        {
            harm_amounts += ({ 0 });
            continue;
        }
        int index = member_array(target, targets);
        int pen = calculate_pen(resist[index]);
        mixed * hitresult = target->hit_me(pen, MAGIC_DT, caster, -1);
        if (sizeof(hitresult) >= 4)
        {
            int harm_amount = hitresult[3];
            send_debug_message("heal_spell", caster->query_name()
                             + " harms undead " + target->query_name() 
                             + " for " + harm_amount + " hit points.");   
            harm_amounts += ({ harm_amount });
        }
    }
        
    if (sizeof(living_targets))
    {
        hook_describe_heal_result(caster, living_targets, heal_amounts);
    }
    
    if (sizeof(undead_targets))
    {
        // Make sure that the spell triggers an attack
        attack_targets(caster, undead_targets);
        hook_describe_harm_result(caster, undead_targets, harm_amounts);
        // If the targets are at <= 0 hit points, we call do_die also.
        foreach (object target : undead_targets)
        {
            if (target->query_hp() <= 0)
            {
                target->do_die(caster);
            }        
        }
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_heal_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_heal_spell(object caster, object *targets, int *resist, int result)
{
}

/*
 * Function name: hook_describe_heal_cast
 * Description:   Describe casting of the spell. This takes place before the
 *                actual healing happens.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 */
public void
hook_describe_heal_cast(object caster, object *targets)
{
    if (IN_ARRAY(caster, targets))
    {
        object * other_targets = targets - ({ caster });
        if (sizeof(other_targets))
        {
            caster->catch_tell("You channel healing energies into yourself "
                + "and " + COMPOSITE_LIVE(other_targets) + ".\n");
        }
        else
        {
            caster->catch_tell("You channel healing energies into yourself.\n");
        }
    }
    else
    {
        caster->catch_tell("You channel healing energies into "
            + COMPOSITE_LIVE(targets) + ".\n");
    }
}

/*
 * Function name: hook_describe_heal_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * heal_amts - the amounts healed
 */
public void
hook_describe_heal_result(object caster, object *targets, int * heal_amounts)
{
    tell_room(environment(caster), capitalize(COMPOSITE_LIVE(targets))
        + ((sizeof(targets) == 1) ? " looks " : " look ")
        + "healthier.\n", targets);
    targets->catch_tell("You feel healthier.\n");
}


/*
 * Function name: hook_describe_harm_result
 * Description:   Describe the results of the spell upon its targets. This
 *                happens after the healing has happened.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object * target - the target(s)
 *                int * harm_amounts - the amounts healed
 */
public void
hook_describe_harm_result(object caster, object *targets, int * harm_amounts)
{
    tell_room(environment(caster), capitalize(COMPOSITE_LIVE(targets))
        + ((sizeof(targets) == 1) ? " looks " : " look ")
        + "hurt by the living energies.\n", targets);
    targets->catch_tell("You feel hurt by the living energies.\n");
}
