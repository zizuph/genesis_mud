/*
 * General Refresh Spell
 * 
 * This is a generic refresh spell that should be used as the basis for all
 * refresh spells under the Genesis Magic system created in 2009. A refresh
 * spell cures fatigue.
 *
 * Created by Petros, May 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include "defs.h"

inherit SPELL_DIR + "centralized_spell";
#include "centralized_spell_restrictions.h"

// Prototypes
public void resolve_refresh_spell(object caster, mixed * targets, int * resist, int result);
public string * query_refresh_ingredients(object caster);
public void     desc_refresh_cast(object caster, object * targets, int amount);
public int      query_refresh_amount();

// Global Variables
public int      Refresh_amount = 35; // default 35 is same as chicory

/*
 * Function:    query_refresh_amount
 * Description: Return the amount that this refresh spell should refresh.
 */
public int
query_refresh_amount()
{
    return Refresh_amount;
}

/*
 * Function:    set_refresh_amount
 * Description: Sets the amount to be refreshed by this spell.
 */
public void
set_refresh_amount(int amount)
{
    Refresh_amount = amount;
}

/*
 * Function:    config_refresh_spell
 * Description: Config function for refresh spells. Redefine this in your
 *              own refresh spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_refresh_spell()
{
    // This spell has no spell effect object
}

private nomask void
config_required_parameters()
{
    // Place required parameters here.
}

public nomask void
config_spell()
{
    ::config_spell();

    set_spell_name("refresh");
    set_spell_desc("Cure fatigue");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_refresh_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 15);
        
    // Call the specific configuration that is to be masked.
    config_refresh_spell();
    
    // Call this after the config_refresh_spell to ensure that
    // required parameters aren't overridden
    config_required_parameters();
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    object enhancer = get_best_spellpower_enhancer(caster);

    if (enhancer)
        hook_enhancer_modified_spell(caster, enhancer, targets);

    resolve_refresh_spell(caster, targets, resist, result);

    int amount = query_refresh_amount() / 2;
    amount = amount + random(amount) + random(amount) + random(amount); 
    amount = max(1, query_spell_power() * amount / F_PENMOD(40, 100));
    targets->add_fatigue(amount);
    
    desc_refresh_cast(caster, targets, amount);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_refresh_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_refresh_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_refresh_ingredients
 * Description: This function defines what components are required for
 *              this refresh spell.
 */
public string *
query_refresh_ingredients(object caster)
{
    return ({  });
}

/*
 * Function name: desc_refresh_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                object * targets - the targets
 *                int amount - the amount refreshed
 */
public void
desc_refresh_cast(object caster, object * targets, int amount)
{
    object * other_targets = targets - ({ caster });
    if (!IN_ARRAY(caster, targets))
    {
        caster->catch_tell("You channel your power and refresh " + 
            FO_COMPOSITE_ALL_LIVE(other_targets, caster) + ".\n");
    }
    else
    {
        if (sizeof(targets) == 1)
        {
            // Only casting on self
            caster->catch_tell("You channel your power into yourself "
                + "and refresh yourself.\n");
        }
        else
        {
            caster->catch_tell("You channel your power and refresh " + 
                FO_COMPOSITE_ALL_LIVE(other_targets, caster) 
              + " and yourself.\n");
        }
    }
    
    if (sizeof(other_targets))
    {
        other_targets->catch_msg(QCTNAME(caster) + " extends " 
            + caster->query_possessive() + " clenched fist toward "
            + "you and you feel refreshed.\n");
    }
}
