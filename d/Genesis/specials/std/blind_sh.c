/*
 * blind_sh.c
 *
 * 100% blind has been calculated to 135caid
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"
#include <stdproperties.h>
#include <formulas.h>

inherit EFFECT_BASE_SH;

// Prototypes
public void         remove_blind_shadow();

// Global Variables
static mapping      gBlindAlarms = ([]);

/*
 * Function Name:   sort_ascending
 * Description:     This function is used by the sort_array to sort the array
 *                  into an ascending order.
 * Arguments:       1. (mixed *) call_a
 *                  2. (mixed *) call_b
 * Returns:         (int) The position of the comparative arguments
 */
public int
sort_ascending(mixed *call_a, mixed *call_b)
{
    return call_a[2] - call_b[2];
} /* sort_ascending */

/*
 * Function Name:   query_blind_effects
 * Description:     Returns the full list of blind effects currently being kept
 *                  track of by the effect shadow
 * Arguments:       None
 * Returns:         (object *) An array of blind effect objects
 */
public object *
query_blind_effects()
{
    return query_effects();
} /* query_blind_effects */

/*
 * Function name:   remove_blind_effect
 * Description:     Removes the specified blind effect from the shadowed target.
 * Arguments:       (object) effect - The blind effect being removed
 * Returns:         (status) 1 - effect successfully removed
 *                           0 - effect failed to be removed
 */ 
public status
remove_blind_effect(object effect)
{
    if (member_array(effect, query_blind_effects()) > -1)
    {
        int blind = shadow_who->query_prop(LIVE_I_BLIND);
        
        shadow_who->add_prop(LIVE_I_BLIND, --blind);
        
        remove_alarm(gBlindAlarms[effect]);
        m_delkey(gBlindAlarms, effect);
        remove_effect(effect);
        
        if (!sizeof(query_blind_effects()))
            set_alarm(0.0, 0.0, &remove_blind_shadow());
        
        return 1;
    }
    
    return 0;
} /* remove_blind_effect */

public void
handle_effect(object effect)
{
    effect->remove_blind_effect(shadow_who);
}

/*
 * Function name:   add_blind_alarm
 * Description:     Handles the balance and stacking of effect alarms.
 * Arguments:       (object) effect - The effect which is being added.
 * Returns:         Nothing
 */
public void
add_blind_alarm(object effect)
{
    int     caid,
            stat_mod,
            skill_mod;
    mixed  *eff_arr;
    object  player;
    float   time;
    
    player = effect->query_effect_caster();
    
    // Fetch the caid from the effect
    caid = effect->query_blind_combat_aid();
    
    // Scale caid based on chance to fail
    caid = caid * 100 / effect->query_blind_chance();
    
    // Fetch the time from the effect
    time = itof(effect->query_blind_cycle());
    
    // Scale time based on the effect caid (divided by caid of 100% blind)
    time = time * itof(caid) / 135.0;
    
    // Scale time based on haste
    if (effect->query_blind_hasted())
        time = time * 100.0 / itof(shadow_who->query_speed(100));
    
    // Scale time based on stats and skills
    stat_mod = effect->calc_stat_modifier(player, effect->query_blind_stats());
    skill_mod = effect->calc_base_skill(player, effect->query_blind_skills());
    time = time * itof(F_STR_FACTOR(stat_mod)) / 100.0;
    time = time * itof(skill_mod) / 100.0;
    
    if (m_sizeof(gBlindAlarms))
    {
        eff_arr = map(m_values(gBlindAlarms), get_alarm);
        eff_arr = sort_array(eff_arr, sort_ascending);
        
        if (sizeof(eff_arr))
            time += eff_arr[0][2];
    }
    
    gBlindAlarms[effect] = set_alarm(time, 0.0, &handle_effect(effect));
} /* add_blind_alarm */

/*
 * Function name:   add_blind_effect
 * Description:     Adds the specified blind effect to the shadowed target.
 * Arguments:       (object) effect - The blind effect being added
 * Returns:         (status) 1 - effect successfully added
 *                           0 - effect failed to be added
 */
public status
add_blind_effect(object effect)
{
    if (effect->query_blind_valid(shadow_who))
    {
        if (effect->query_blind_tohit() >= random(100))
        {
            int blind = shadow_who->query_prop(LIVE_I_BLIND);
        
            shadow_who->add_prop(LIVE_I_BLIND, ++blind);
        
            add_blind_alarm(effect);
            
            add_effect(effect);
            return 1;
        }
    }
    
    return 0;
} /* add_blind_effect */

/*
 * Function name:   remove_blind_shadow
 * Description:     Handles the removal of effects when removing the shadow.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
remove_blind_shadow()
{
    foreach(object effect: query_effects())
    {
        remove_blind_effect(effect);
    }
    
    remove_shadow();
} /* remove_blind_shadow */
