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

#include "defs.h"
inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_heal_spell(object caster, object * targets, int * resist, int result);
public void hook_describe_heal_result(object caster, object *targets, int * heal_amounts);
public void hook_describe_harm_result(object caster, object *targets, int * harm_amounts);
public void hook_describe_heal_cast(object caster, object * targets);

public status
query_heal_harmful(object target)
{
    return !!target->query_prop(LIVE_I_UNDEAD);
}

/*
 * Function:    query_ability_offensive
 * Description: By default, just returns the value specified in
 *              set_ability_offensive. However, this can be
 *              overridden to take into account the targets and
 *              determine whether to be offensive or not.
 */
public varargs nomask int
query_ability_offensive(mixed * targets = 0)
{
    // Removing the player from the equation to allow for self-harming in case
    // of player being of the harmful variety.
    targets -= ({ this_player() });
    return sizeof(filter(targets, &query_heal_harmful()));
}

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

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

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

    set_spell_apply_whitehit_aid(1);
        
    // Call the specific configuration that is to be masked.
    config_heal_spell();
    
    // Call this after the config_heal_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

static nomask void
resolve_compound_combat_special(object actor, object *targets, int *hitlocs,
    int *random_hitlocs, int *pen, int *damage_types, mixed * items,
    int *resist, int *results)
{
    // Stupid code, but using it for backwards compatibility
    if (sizeof(filter(results, &operator(>)(,0))))
    {
        resolve_heal_spell(actor, targets, resist, 1);

        // Display the spell being cast
        hook_describe_heal_cast(actor, targets);
    
        object *heal_targets = ({}),
               *harm_targets = ({});
        int    *heal_amounts = ({}),
               *harm_amounts = ({});

        object enhancer = get_best_spellpower_enhancer(actor);

        if (enhancer)
            hook_enhancer_modified_spell(actor, enhancer, targets);
    
        for (int i = 0; i < sizeof(targets); i++)
        {
            if (query_heal_harmful(targets[i]))
            {
                mixed * hitresult = targets[i]->hit_me(pen[i], MAGIC_DT, actor, -1);
                if (sizeof(hitresult) >= 4)
                {
                    int amount = hitresult[3];
                    send_debug_message("heal_spell", actor->query_name()
                             + " harms undead " + targets[i]->query_name() 
                             + " for " + amount + " hit points.");
                    harm_amounts += ({ amount });
                    harm_targets += ({ targets[i] });
                    if (enhancer)
                    {
                        enhancer->did_spell_hit(-1, hitresult[0], targets[i],
                            query_spell_element(), query_spell_form_needed(), hitresult[2],
                            hitresult[3]);
                    }
                }
            }
            else
            {
                int heal, amount, health;
                heal = pen[i] / 4;
                // This will mimic the dice roll for MAGIC_DT.  The pen was
                // reduced by the apply resistance function, to account for
                // the differences between MAGIC_DT and other weapon hitme.
                heal = heal + random(heal) + random(heal) + random(heal);
                health = targets[i]->query_max_hp() - targets[i]->query_hp();
                amount = max(0, min(heal, health));
                heal_amounts += ({ amount });
                heal_targets += ({ targets[i] });
                targets[i]->heal_hp(amount);
                send_debug_message("heal_spell", actor->query_name()
                + " heals max of " + heal + " on " + targets[i]->query_name() 
                + " for " + amount + " hit points.");
            }
        }
        
        if (sizeof(heal_targets))
        {
            hook_describe_heal_result(actor, heal_targets, heal_amounts);
        }
    
        if (sizeof(harm_targets))
        {
            // Make sure that the spell triggers an attack
            attack_targets(actor, harm_targets);
            hook_describe_harm_result(actor, harm_targets, harm_amounts);
            foreach (object harm_target : harm_targets)
            {
                if (harm_target->query_hp() <= 0)
                {
                    harm_target->do_die(actor);
                }

            }
        }
    }
    else
    {
        mixed fail_message = query_spell_fail();
        if (functionp(fail_message))
        {
            function f = fail_message;
            write(f());
        }
        else if (stringp(fail_message))
        {
            write(fail_message);
        }
    }
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
    // Obsolete?
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
