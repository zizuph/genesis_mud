/*
 * Evade Shadow
 * 
 * This is a default shadow that allows evade objects to be added
 * to it in order to support multiple stacking evade effects
 *
 * An evade object has the following methods defined:
 * int    query_evade_percentage();
 * int    query_evade_strength(object player, object attacker, 
                               int attack_id);
 * int    query_evade_valid(object player, object attacker, 
 *                          int attack_id);
 * void   attack_blocked(object player, object attacker, int attack_id);
 *
 * Created by Petros, May 2008
 *
 * Modified on 2021-03-06 by Carnak:
 * - An attempt to fix the stacking and scaling of defensive abilities.
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"

inherit EFFECT_BASE_SH;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

static mapping valid_evades;

/*
 * Function name:   query_effect_type
 * Description:     Returns the effect type with which we force this object
 *                  to stack.
 * Arguments:       None
 * Returns:         (string) The effect type
 */
public string
query_effect_type()
{
    return "defensive";
} /* query_effect_type */

/*
 * Function name:   query_effect_combat_aid
 * Description:     Based on the results of query_effect_percentage
 *                  This gives the total combat aid given by shadow
 *                  with the current effects.
 * Arguments:       None
 * Returns:         the calculated stacking combat aid
 */
public int
query_effect_combat_aid()
{
    object *effects = query_effects();
    int caid;
    
    if (m_sizeof(valid_evades))
        effects = m_indexes(valid_evades);
    
    foreach (object effect : effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        if (member_array(effect, m_indexes(valid_evades)) > -1)
        {
            int perc = valid_evades[effect];
            perc = perc < 0 ? 0 : perc;
            perc = perc > 99 ? 99 : perc;
            caid += (perc * 100) / (100 - perc) + (perc > 0 ? 1 : 0);
            continue;
        }
        object player = effect->query_effect_target();
        caid += effect->query_evade_combat_aid(player);
    }
    
    return caid;
} /* query_effect_combat_aid */

/*
 * Function     : has_evade_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int
has_evade_shadow()
{
    return 1;
} /* has_evade_shadow */

/*
 * Function     : remove_evade_shadow
 * Description  : Easy way to remove shadow. Must use this otherwise the
 *                wrong shadow could be removed.
 * Arguments    : none
 * Returns      : nothing
*/
public void
remove_evade_shadow()
{
    remove_shadow();
} /* remove_evade_shadow */

/*
 * Function     : query_evade_percentage
 * Description  : Returns the calculated percentage of all the evade
 *                objects that the evade shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum evade. The actual evade depends on the
 *                situation in query_evade_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
public int 
query_evade_percentage()
{
    return query_effect_percentage();
} /* query_evade_percentage */

/*
 * Function     : query_evade_combat_aid
 * Description  : Based on the results of query_evade_percentage
 *                This gives the total combat aid given by evade
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stacking combat aid
 */
public int
query_evade_combat_aid()
{
    return query_effect_combat_aid();
} /* query_evade_combat_aid */

/*
 * Function     : remove_evade_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
public nomask void
remove_evade_effect(object obj)
{
    remove_effect(obj);
    send_debug_message("evade_sh", "Removing evade effect " 
                     + obj->query_name() + ".");
} /* remove_evade_effect */

/*
 * Function     : add_evade_effect
 * Description  : Adds the evade effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask void
add_evade_effect(object obj)
{
    add_effect(obj);
    send_debug_message("evade_sh", "Adding evade effect " 
                     + obj->query_name() + ".");
    // Adding this shadow to the stacking list.
    if (!sizeof(query_stacking_effects()))
         add_stacking_effect(this_object());
} /* add_evade_effect */

/*
 * Function     : query_evade_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the evade shadow
 * Arguments    : none
 * Returns      : array of evade effect objects
 */
public object *
query_evade_effects()
{
    return query_effects();
} /* query_evade_effects */

/*
 * Function     : report_total_evade_percentage
 * Description  : Called by query_not_attack_me to report how much
 *                the total valid evade percentage is for the
 *                evader.
 * Arguments    : percentage - amount to report
 * Returns      : Nothing.
 */
public void
report_total_evade(int percentage, int caid)
{
    send_debug_message("evade_sh_total", 
        capitalize(shadow_who->query_real_name())
        + " has a total evade of " 
        + percentage + "% with a combat aid of " + caid + "%.");
} /* report_total_evade */

/*
 * Function     : query_not_attack_me
 * Description  : Goes through the list of evade effects and applies them
 *                one by one. If none of them succeed, then the normal
 *                result of query_not_attack_me is called.
 * Arguments    : attacker   - person attacking shadow_who
 *                attack_id  - The attack id of the attack
 * Returns      : the calculated stacking percentage
 */
public int
query_not_attack_me(object attacker, int att_id)
{
    valid_evades = ([]);
    foreach (object effect : query_evade_effects())
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        if (!effect->query_evade_valid(shadow_who, attacker, att_id))
        {
            send_debug_message("evade_sh", capitalize(effect->query_name())
                             + " cannot evade in the current situation.");
            continue;
        }

        valid_evades[effect] = effect->query_evade_strength(shadow_who, 
                                                        attacker, att_id);
    }
    
    if (!m_sizeof(valid_evades))
    {
        // Don't do any processing if there are no valid evade effects
        return shadow_who->query_not_attack_me(attacker, att_id);
    }
    
    if (query_effect_percentage() > random(100))
    {
        object effect = one_of_list(m_indexes(valid_evades) - ({ 0 }));
        send_debug_message("evade_sh", capitalize(effect->query_name()) 
            + " caused an evade.");
        effect->attack_blocked(shadow_who, attacker, att_id);
        valid_evades = ([]);
        return 1;
    }
    
    valid_evades = ([]);
    
    return shadow_who->query_not_attack_me(attacker, att_id);
} /* query_not_attack_me */

