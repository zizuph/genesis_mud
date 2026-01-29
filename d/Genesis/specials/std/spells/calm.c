/*
 * General Calm Spell
 * 
 * This is a generic calm spell that should be used as the basis for all
 * calm spells under the Genesis Magic system created in 2009. A calm
 * spell cures panic.
 *
 * Created by Petros, May 2010
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_calm_spell(object caster, mixed * targets, int * resist, int result);
public string * query_calm_ingredients(object caster);
public void     desc_calm_cast(object caster, mapping calm_amounts);
public int      query_calm_amount();

// Global Variables
public int      Calm_amount = 200; // default to 200 avg for each casting

/*
 * Function:    query_calm_amount
 * Description: Return the amount that this calm spell should calm.
 */
public int
query_calm_amount()
{
    return Calm_amount;
}

/*
 * Function:    set_calm_amount
 * Description: Sets the amount to be calmed by this spell.
 */
public void
set_calm_amount(int amount)
{
    Calm_amount = amount;
}

/*
 * Function:    config_calm_spell
 * Description: Config function for calm spells. Redefine this in your
 *              own calm spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_calm_spell()
{
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

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

    set_spell_name("calm");
    set_spell_desc("Calm fear");

    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_living);
    set_spell_ingredients(query_calm_ingredients);

    set_spell_fail("You fail in your efforts to invoke the spell.\n");
    set_ability_target_verify(spell_verify_present);
    
    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_ILLUSION, 15);
        
    // Call the specific configuration that is to be masked.
    config_calm_spell();
    
    // Call this after the config_calm_spell to ensure that
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
    resolve_calm_spell(caster, targets, resist, result);

    int amount = query_calm_amount() / 2;
    amount = amount + random(amount) + random(amount) + random(amount); 
    amount = max(1, query_spell_power() * amount / 396); // F_PENMOD(60, 100) = 396
    mapping calm_amounts = ([ ]);
    foreach (object target : targets)
    {
        // Since panic is unbounded, you could have more panic than the wimpy level.
        // We will add the extra amount also to the amount, if applicable.
        int calm_amount = amount + max(0, target->query_panic() - F_PANIC_WIMP_LEVEL(target->query_stat(SS_DIS)));
        target->add_panic(-calm_amount);
        calm_amounts[target] = calm_amount;
    }
    
    desc_calm_cast(caster, calm_amounts);
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_calm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_calm_spell(object caster, mixed * targets, int * resist, int result)
{
}

/*
 * Function:    query_calm_ingredients
 * Description: This function defines what components are required for
 *              this calm spell.
 */
public string *
query_calm_ingredients(object caster)
{
    return ({ });
}

/*
 * Function name: desc_calm_cast
 * Description:   Describe casting of the spell to cure fatigue.
 *                This can be redefined for custom messages.
 * Arguments:     object caster - the caster
 *                mapping calm_amounts - the amount calmed for each target
 */
public void
desc_calm_cast(object caster, mapping calm_amounts)
{
    object * targets = m_indices(calm_amounts);
    object * other_targets = targets - ({ caster });
    if (!IN_ARRAY(caster, targets))
    {
        caster->catch_tell("You channel your power and calm " + 
            FO_COMPOSITE_ALL_LIVE(other_targets, caster) + ".\n");
    }
    else
    {
        if (sizeof(targets) == 1)
        {
            // Only casting on self
            caster->catch_tell("You channel your power into yourself "
                + "and calm yourself.\n");
        }
        else
        {
            caster->catch_tell("You channel your power and calm " + 
                FO_COMPOSITE_ALL_LIVE(other_targets, caster) 
              + " and yourself.\n");
        }
    }
    
    if (sizeof(other_targets))
    {
        other_targets->catch_msg(QCTNAME(caster) + " extends " 
            + caster->query_possessive() + " clenched fist toward "
            + "you and you feel more calm.\n");
    }
}
