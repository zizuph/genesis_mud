/*
 * Base Effect Shadow
 * 
 * This is a default shadow that allows effects to be stacked on a
 * person. This shadow is currently the base for both evade and
 * stuns.
 *
 * The implementation shadows should be cloned when the effect is
 * added, and removed when the effects are all gone. The code for
 * this can be found in the base effect object.
 *
 * Created by Petros, June 2008
 *
 * Modified 2021-03-03 by Carnak:
 * - Fixed and simplified calculations for stacking effects.
 * - Added stacking for external objects of same effect type.
 *
 * Modified 2022-06-15 by Zizuph:
 * - Each shadow collects its own effects - no need to pass it down
 *   through a separate chain.  These compute the right CAID for
 *   their own effect.
 *
 * Modified 2022-06-21 by Zizuph:
 * - Add a function to allow child shadows to override the function
 *   used for getting combat aid.  This can happen if there are
 *   tohit, or percentage failure chances to account for, for example.
 *
 * Modified 2022-06-24 by Zizuph:
 * - The query_effect_percentage was returning values that were lower
 *   than the individual effects.  Instead, sum the CAID, and convert to
 *   percentage.
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include "defs.h"
inherit "/d/Genesis/specials/calculations";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Array of effects being tracked by this shadow
private object *my_effects = ({ });

/*
 * Function name:   get_individual_effect_combat_aid
 * Description:     This gives the total combat aid given by a specific
 *                  effect.  This can be overridden when there are extra
 *                  factors affecting the effective combat aid.
 * Arguments:       None
 * Returns:         the calculated stacking combat aid
 */

static int get_individual_effect_combat_aid(object effect)
{
    return effect->query_effect_modified_combat_aid(
          effect->query_effect_caster());
}

/*
 * Function name:   query_effect_combat_aid
 * Description:     This gives the total combat aid given by shadow
 *                  with the current effects.
 * Arguments:       None
 * Returns:         the calculated stacking combat aid
 */
static nomask int query_effect_combat_aid(object* effects)
{
    int caid;
    if (!sizeof(effects))
    {
        return 0;
    }
    foreach (object effect : effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        caid += get_individual_effect_combat_aid(effect);
    }
    
    return caid;
} /* query_effect_combat_aid */

/*
 * Function     : query_effect_percentage
 * Description  : Returns the calculated percentage of all the effect
 *                objects that the effect shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum effect. The actual effect depends on the
 *                situation in query_effect_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
static nomask int query_effect_percentage(object* effects)
{
    int last, total;
    mapping percentage = ([]);
    foreach(object effect: effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        int current, caid;
        // Get the combat aid of the effect
        caid = get_individual_effect_combat_aid(effect);
        send_debug_message("effect_sh", "Individual effect CAID: "  + caid);

        // Damage mod can return a negative CAID..
        if (caid < 1) continue;
        
        // Tally the total amount caid
        total += caid;
    }
    return convert_caid_to_percentage(total);
    
} /* query_effect_percentage */

/*
 * Function     : remove_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
static nomask void
remove_effect(object obj)
{
    my_effects -= ({ obj });
    my_effects -= ({ 0 });
    obj->remove_shadow_from_list(this_object());
    send_debug_message("effect_sh", "Removing effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : add_effect
 * Description  : Adds the effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
static nomask void
add_effect(object obj)
{
    my_effects -= ({ 0 });
    if (IN_ARRAY(obj, my_effects))
    {
        // We don't want the same effect to be added twice
        send_debug_message("effect_sh", "Effect " + obj->query_name() 
                         + " already added.");
        return;
    }
    my_effects += ({ obj });
    obj->add_shadow_to_list(this_object());
    send_debug_message("effect_sh", "Adding effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : query_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the effect shadow
 * Arguments    : none
 * Returns      : array of effect objects
 */
static object * query_effects()
{
    return my_effects;
}