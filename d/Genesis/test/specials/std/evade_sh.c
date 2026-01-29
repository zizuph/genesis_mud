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
}

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
}

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
}

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
}

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
}

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
}

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
}


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
    int evade_percentage;
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
                             + " was not successful in helping to evade.");
            continue;
        }
        
        evade_percentage = effect->query_evade_strength(shadow_who, 
                                                        attacker, att_id);
        if (evade_percentage > 0 && evade_percentage > random(100))
        {
            send_debug_message("evade_sh", 
                capitalize(effect->query_name()) 
                + " caused an evade.");
            effect->attack_blocked(shadow_who, attacker, att_id);
            return 1;
        }
    }
 
    return shadow_who->query_not_attack_me(attacker, att_id);
}

