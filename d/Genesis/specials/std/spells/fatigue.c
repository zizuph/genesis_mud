/*
 * General Fatigue Spell
 * 
 * This is a generic Fatigue spell that should be used as the basis for all
 * fatigue draining spells under the new Genesis Magic system created in 2009.
 * A fatigue spell drains fatigue from the target. It can optionally grant
 * the caster some of the fatigue in return.
 *
 * Because fatigue drain is such a powerful PK ability, we will limit its
 * use against a player enemy to once every 60 seconds. This does not, however,
 * prevent multiple casters from casting it on the target.
 *
 * Created by Navarre, October 2010.
 */
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_drain_spell(object caster, mixed *targets, int *resist, int result);
public string * query_drain_ingredients(object caster);
public int      query_drain_amount();
// Hook Prototypes
public void     hook_fatigue_unaffected(object caster, object * targets);
public void     hook_fatigue_resisted(object caster, object * targets);
public void     hook_fatigue_succeeded(object caster, object * targets, int * drain_amounts);

// Global Variables
public int drain_amount = 35; // default 35 is same as chicory
public int transfer_factor = 0; // By default, none of the fatigue will be transferred to the caster.

// Defines
#define OBJ_I_FATIGUE_DRAINED "_obj_i_fatigue_drained"

/*
 * Function:    query_drain_amount
 * Description: Return the amount that this drain spell should drain.
 */
public int
query_drain_amount()
{
    return drain_amount;
}

/*
 * Function:    set_drain_amount
 * Description: Sets the amount to be drained by this spell.
 */
public void
set_drain_amount(int amount)
{
    drain_amount = amount;
}

/*
 * Function:    query_transfer_factor
 * Description: Returns the percentage of the fatigue that will be
 *              transferred to the caster from the drainee.
 */
public int
query_transfer_factor()
{
    return transfer_factor;
}

/*
 * Function:    set_transfer_factor
 * Description: Sets the percentage of the fatigue that will be
 *              transferred to the caster from the drainee.
 */
public void
set_transfer_factor(int factor)
{
    // We don't allow transfer amounts to exceed 90%.
    transfer_factor = min(90, max(0, factor));
}

/*
 * Function:    config_drain_spell
 * Description: Config function for drain spells. Redefine this in your
 *              own drain spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_drain_spell()
{
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // This spell has no spell effect object
    set_drain_amount(35);
    set_transfer_factor(50); // by default 50% of the fatigue drained gets transferred 
}

private nomask void
config_required_parameters()
{
    set_spell_offensive(1);
    // Place required parameters here.
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("fatigue");
    set_spell_desc("Drain fatigue");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_other_present_living_or_enemy);
    set_spell_ingredients(query_drain_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_drain_spell();
    
    // Call this after the config_drain_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

public int
drained_by_caster_recently(object caster, object target)
{
    if (!IS_PLAYER_OBJECT(target))
    {
        // Only players are affected by this cooldown effect.
        return 0;
    }
    
    mapping fatigue_drains = target->query_prop(OBJ_I_FATIGUE_DRAINED);
    if (!mappingp(fatigue_drains))
    {
        return 0;
    }
    
    if (fatigue_drains[caster->query_real_name()] + 60 > time())
    {
        send_debug_message("fatigue_spell", "Cooldown for drain in effect.");
        return 1;
    }
    
    return 0;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets  - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    object * targets_drained = ({ });
    object * targets_resisted = ({ });
    object * targets_unaffected = ({ });
    int * drain_amounts = ({ });
    resolve_drain_spell(caster, targets, resist, result);

    int amount = query_drain_amount() / 2;
    amount = amount + random(amount) + random(amount); 
    amount = max(1, (amount * query_spell_power()) / 396); // F_PENMOD(60, 100) = 396
    int max_drained = 0;
    for (int index = 0; index < sizeof(targets); ++index)
    {
        object target = targets[index];
        if (resist[index] > random(100))
        {
            targets_resisted += ({ target });
        }
        else
        {
            if (drained_by_caster_recently(caster, target))
            {
                targets_unaffected += ({ target });
                continue;
            }
            int current_drain = min(target->query_fatigue(), amount);
            max_drained = max(max_drained, current_drain);
            target->add_fatigue(-current_drain);
            if (current_drain > 0)
            {
                targets_drained += ({ target });
                drain_amounts += ({ current_drain });
            }
            else
            {
                targets_unaffected += ({ target });
            }
            
            // We set the time that this caster drained so we can handle
            // the cooldown.
            if (!mappingp(target->query_prop(OBJ_I_FATIGUE_DRAINED)))
            {
                target->add_prop(OBJ_I_FATIGUE_DRAINED, ([ ]));
            }
            mapping fatigue_drains = target->query_prop(OBJ_I_FATIGUE_DRAINED);
            fatigue_drains[caster->query_real_name()] = time();
            target->add_prop(OBJ_I_FATIGUE_DRAINED, fatigue_drains);
        }
    }
    // Now, add the fatigue to the caster based on the transfer factor
    int regained = (max_drained * query_transfer_factor()) / 100;
    caster->add_fatigue(regained);
    send_debug_message("fatigue_spell", max_drained + " drained and " + regained + " regained.");
    
    if (sizeof(targets_drained))
    {
        hook_fatigue_succeeded(caster, targets_drained, drain_amounts);
    }
    
    if (sizeof (targets_unaffected))
    {
        hook_fatigue_unaffected(caster, targets_unaffected);
    }
    
    if (sizeof(targets_resisted))
    {
        hook_fatigue_resisted(caster, targets_resisted);
    }
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_drain_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_drain_spell(object caster, mixed *targets, int *resist, int result)
{
}

/*
 * Function:    query_drain_ingredients
 * Description: This function defines what components are required for
 *              this drain spell.
 */
public string*
query_drain_ingredients(object caster)
{
    return ({});
}

/*
 * Function name: hook_fatigue_succeeded
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster   - the caster
 *                object *targets - the targets
 *                int * drain_amounts      - the amount drained for each target
 */
public void
hook_fatigue_succeeded(object caster, object * targets, int * drain_amounts)
{
    caster->catch_msg("You channel your power and drain " + 
                      QTNAME(targets[0])+".\n");
    targets[0]->catch_msg(QCTNAME(caster) + " extends " + 
                          caster->query_possessive() +
                          " clenched fist toward " +
                          "you and you feel drained.\n");
}

/*
 * Function:    hook_fatigue_unaffected
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets either because the
 *              target has no more fatigue points, or because it
 *              just didn't work.
 */
public void
hook_fatigue_unaffected(object caster, object * targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " are "
        + "not affected by your spell.\n");
    targets->catch_msg("You shrug off an attempt by " + QTNAME(caster)
        + "to tire you.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in "
        + "trying to fatigue " + COMPOSITE_LIVE(targets) + ".\n",
        ({ caster }) + targets);
}

/*
 * Function:    hook_drain_resisted
 * Description: Function that gets called to tell that the spell did
 *              not succeed against the targets because of resistance
 */
public void
hook_fatigue_resisted(object caster, object * targets)
{
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " resist "
        + "your spell.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster)
        + "to tire you.\n");
    caster->tell_watcher(QCTNAME(caster) + " doesn't seem to succeed in "
        + "trying to fatigue " + COMPOSITE_LIVE(targets) + ".\n",
        ({ caster }) + targets);
}
