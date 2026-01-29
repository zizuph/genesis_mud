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
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/shadow";

#include "defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

// Array of effects being tracked by this shadow
private object * my_effects = ({ });

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
static int 
query_effect_percentage()
{
    int percentage = 0;
    int x, y;
    foreach (object effect : my_effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        // Stacking Effect Formula (x, y)
        //    100 - (((100 - x) * (100 - y)) / 100)
        // This works out to be the same as:
        //    x + y - (x * y / 100)
        x = percentage;
        y = effect->query_effect_percentage();
        y = y < 0 ? 0 : y; // make sure it's not negative
        y = y > 100 ? 100 : y; // make sure it's at most 100
        percentage = x + y - ((x * y) / 100);
    }
    
    return percentage;
}

/*
 * Function     : query_effect_combat_aid
 * Description  : Based on the results of query_effect_percentage
 *                This gives the total combat aid given by shadow
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stacking combat aid
 */
static int
query_effect_combat_aid()
{
    // Formula for calculating combat aid based on effects is:
    //   (e * 100) / (100 - e)
    int percentage, caid;
    
    percentage = query_effect_percentage();
    caid = (percentage * 100) / (100 - percentage);
    return caid;
}

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
static object *
query_effects()
{
    return my_effects;
}
