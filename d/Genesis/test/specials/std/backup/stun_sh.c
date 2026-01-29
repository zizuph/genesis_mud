/*
 * Stun Shadow
 * 
 * This is a default shadow that allows stun objects to be added
 * to it in order to support multiple stacking stun effects
 *
 * An stun object has the following methods defined:
 * int    query_stun_percentage();
 * int    query_stun_strength(object player, object attacker, 
                               int attack_id);
 * int    query_stun_valid(object player, object attacker, 
 *                          int attack_id);
 * void   attack_blocked(object player, object attacker, int attack_id);
 *
 * Created by Petros, May 2008
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

inherit "/std/shadow";

#include "./defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

// List of objects with stun percentages
object * stun_effects = ({ });

int full_stuns;
int last_stun_result;

int is_removing=0;

/*
 * Function     : has_stun_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int
has_stun_shadow()
{
    return 1;
}

/*
 * Function     : query_stun_percentage
 * Description  : Returns the calculated percentage of all the stun
 *                objects that the stun shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum stun. The actual stun depends on the
 *                situation in query_stun_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
public int 
query_stun_percentage()
{
    int percentage = 0;
    int x, y;
    foreach (object effect : stun_effects)
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        // Stacking stun Formula (x, y)
        //    100 - (((100 - x) * (100 - y)) / 100)
        // This works out to be the same as:
        //    x + y - (x * y / 100)
        x = percentage;
        y = effect->query_stun_percentage();
        y = y < 0 ? 0 : y; // make sure it's not negative
        y = y > 100 ? 100 : y; // make sure it's at most 100
        percentage = x + y - ((x * y) / 100);
    }
    
    return percentage;
}

/*
 * Function     : query_stun_combat_aid
 * Description  : Based on the results of query_stun_percentage
 *                This gives the total combat aid given by stun
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stacking combat aid
 */
public int
query_stun_combat_aid()
{
    // Formula for calculating combat aid based on stun is:
    //   (e * 100) / (100 - e)
    int percentage, caid;
    
    percentage = query_stun_percentage();
    caid = (percentage * 100) / (100 - percentage);
    return caid;
}

/*
 * Function     : remove_stun_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
public nomask void
remove_stun_effect(object obj)
{
    stun_effects -= ({ obj });
    stun_effects -= ({ 0 });
    send_debug_message("stun_sh", "Removing stun effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : add_stun_effect
 * Description  : Adds the stun effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask void
add_stun_effect(object obj)
{
    stun_effects += ({ obj });
    stun_effects -= ({ 0 });
    send_debug_message("stun_sh", "Adding stun effect " 
                     + obj->query_name() + ".");
}

/*
 * Function     : query_stun_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the stun shadow
 * Arguments    : none
 * Returns      : array of stun effect objects
 */
public object *
query_stun_effects()
{
    return stun_effects;
}

/*
 * Function     : add_stun
 * Description  : Normally would add a full stun, instead we track these
 *                in the shadow
 * Arguments    : none
 * Returns      : none
 */
public void add_stun()
{
    full_stuns++;
}

/*
 * Function     : remove_stun
 * Description  : Normally would remove a full stun, instead we track these
 *                in the shadow
 * Arguments    : none
 * Returns      : none
 */
public void remove_stun()
{
    if (full_stuns>0)
    {
        full_stuns--;
    }
}

/*
 * Function     : query_full_stuns
 * Description  : returns how many actual stuns are in place
 * Arguments    : none
 * Returns      : true value of LIVE_I_STUNNED prop
 */
public int query_full_stuns()
{
    return full_stuns;
}

/*
 * Function     : add_prop_live_i_stunned
 * Description  : Normally would remove all active stuns
 *                these in the shadow
 * Arguments    : none
 * Returns      : none
 */
public int add_prop_live_i_stunned(mixed val)
{
    if (is_removing)
    {
        return shadow_who->add_prop_live_i_stunned(val);
    }
    if (!intp(val))
    {
        return shadow_who->add_prop_live_i_stunned(val);
    }
    full_stuns=val-last_stun_result+full_stuns;
    return 1;
}


/*
 * Function     : remove_prop_live_i_stunned
 * Description  : Normally would remove all active stuns
 *                these in the shadow
 * Arguments    : none
 * Returns      : none
 */
public int remove_prop_live_i_stunned()
{
    if (is_removing)
    {
        return shadow_who->remove_prop_live_i_stunned();
    }
    shadow_who->add_prop(LIVE_I_STUNNED,"@@stun_shadow_stun@@");
    full_stuns=0;
    return 1;
}
    
/*
 * Function     : remove_stun_shadow
 * Description  : Easy way to remove shadow
 * Arguments    : none
 */
public void
remove_stun_shadow()
{
    is_removing=1;
    shadow_who->add_prop(LIVE_I_STUNNED,full_stuns);
    remove_shadow();
}

public int stun_shadow_stun()
{
    if (full_stuns)
    {
        last_stun_result=full_stuns;
        return full_stuns;
    }

    int stun_percentage;
    foreach (object effect : query_stun_effects())
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        if (!effect->query_stun_valid(shadow_who))
        {
            send_debug_message("stun_sh", capitalize(effect->query_name())
                             + " was not successful in helping to stun.");
            continue;
        }
        
        stun_percentage = effect->query_stun_strength(shadow_who);
        if (stun_percentage > 0 && stun_percentage > random(100))
        {
            send_debug_message("stun_sh", 
                capitalize(effect->query_name()) 
                + " caused a stun.");
            effect->attack_blocked(shadow_who);
            last_stun_result=1;
            return 1;
        }
    }
    last_stun_result=0;
    return 0;
}

public varargs int shadow_me(mixed to_shadow)
{
    int result=::shadow_me(to_shadow);
    if (result)
    {
        full_stuns=shadow_who->query_prop(LIVE_I_STUNNED);
        shadow_who->add_prop(LIVE_I_STUNNED,"@@stun_shadow_stun@@");
    }
    return result;
}


