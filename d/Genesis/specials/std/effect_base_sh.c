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
private object *my_effects = ({ });
private mapping stacking_effects = ([]);

/*
 * Function name:   add_stacking_effect
 * Description:     Recursively adds an object to all the shadows which
 *                  are in succession.
 * Arguments:       (object) - effect to add
 * Returns:         Nothing
 */
public void
add_stacking_effect(object effect)
{
    string type = effect->query_effect_type();
    
    if (stringp(type))
    {
        if (!sizeof(stacking_effects[type]))
        {
            object * list = shadow_who->query_stacking_effects(type);
            if (!pointerp(list))
                list = ({});
            
            stacking_effects[type] = list;
        }
        
        stacking_effects[type] += ({ effect });
    }
    
    shadow_who->add_stacking_effect(effect);
} /* add_stacking_effect */

/*
 * Function name:   query_stacking_effects
 * Description:     Collects the effects which stacks with this
 *                  object.
 * Arguments:       None
 * Returns:         (object *) List of effects
 */
public varargs object *
query_stacking_effects(string type)
{
    if (!stringp(type))
        type = this_object()->query_effect_type();
    
    if (member_array(type, m_indexes(stacking_effects)) < 0)
        return ({});
    
    return stacking_effects[type];
} /* query_stacking_effects */

/*
 * Function name:   query_effect_combat_aid
 * Description:     This gives the total combat aid given by shadow
 *                  with the current effects.
 * Arguments:       None
 * Returns:         the calculated stacking combat aid
 */
static int
query_effect_combat_aid()
{
    int caid;
    
    foreach (object effect : my_effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        caid += effect->query_effect_combat_aid(shadow_who);
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
static int 
query_effect_percentage()
{
    int last, total;
    mapping percentage = ([]);
    
    foreach(object effect: query_stacking_effects())
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        int current, caid;
        // Get the combat aid of the effect
        caid = effect->query_effect_combat_aid(shadow_who);
        // Damage mod can return a negative CAID..
        if (caid < 1) continue;
        // Convert the effect caid
        current = (100 * caid) / (100 + caid);
        current = current < 0 ? 0 : current;
        current = current > 100 ? 100 : current;
        // Tally the total amount caid
        total += caid;
        // Convert cumulative effects
        // 100 - ((100 - (percent(caid))) * 100 / (100 - percent(last)))..
        current = 100 - ((100 - (total * 100 / (100 + total))) * 100 / (100 - (last)));
        percentage[effect] = current;
        last = current;
        if (effect == this_object())
        {
            // We really only need to tally until this object, for now..
            break;
        }
    }
    
    if (member_array(this_object(), m_indexes(percentage)) < 0)
        percentage[this_object()] = 0;

    return percentage[this_object()];
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
static object *
query_effects()
{
    return my_effects;
}