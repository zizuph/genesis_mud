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
 * Based on fatigue.c created by Navarre, October 2010.
 *
 * Coded by Arman 2016.
 */
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include <stdproperties.h>
#include <flags.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/fatigue";

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
    set_ability_group(GUILD_NAME);
    set_spell_name("wintektor");
    set_spell_desc("Scare - Irrational fear spell causing fatigue and panic");

    set_spell_task(TASK_ROUTINE);    

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);

    // This spell has no spell effect object
    // Fatigue drain amount of 35, panic added 3x 
    set_drain_amount(35);
    set_transfer_factor(0);  
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"wintektor_memorised");
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
    return ({"snake fang", "salt wort"});
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (mixed *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message, target_message;
    object target = targets[0];

        caster_message = "You loom menacingly over " +COMPOSITE_LIVE(targets)+ 
             ", intoning the magical word of power 'Wintektor!'\n";
        target_message = QCTNAME(caster)+ " looms menacingly over you, " +
             "intoning dark and ominous words of magic.\n";
        watcher_message = QCTNAME(caster) + " looms menacingly over " +
              QTNAME(target)+ ", intoning dark and ominous words of magic.\n"; 
        
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    tell_room(environment(caster), watcher_message, ({ caster, target }), 
              caster);

    setuid();
    seteuid(getuid());  
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
    object target = targets[0];

    tell_room(environment(caster), QCTNAME(target)+" is overcome with " +
          "debilitating fear, fatiguing " +HIM(target)+ ".\n", 
          ({ target }), caster);

    target->add_panic((drain_amounts[0] * 3));
    target->catch_msg("You are overcome with irrational fear, making " +
          "you panicky and fatigued.\n");

    // target->catch_msg("Drain amounts: " +drain_amounts[0]+ ".\n");

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
    caster->catch_msg("You sense that " + COMPOSITE_LIVE(targets) + " is "
        + "unaffected by your ensorcellment of fear.\n");
    targets->catch_msg("You are unaffected an attempt by " + QTNAME(caster)
        + " to ensorcel you with fear.\n");
    caster->tell_watcher(QCTPNAME(caster) + " attempt to ensorcel " +
        COMPOSITE_LIVE(targets) + " with fear fails.\n",
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
    caster->catch_msg("Your attempt to ensorcel " + COMPOSITE_LIVE(targets) + 
        " with fear is resisted.\n");
    targets->catch_msg("You resist an attempt by " + QTNAME(caster)
        + " to ensorcel you with fear.\n");
    caster->tell_watcher(QCTPNAME(caster) + " attempt to ensorcel "
        + COMPOSITE_LIVE(targets) + " with fear is resisted.\n",
        ({ caster }) + targets);
}
