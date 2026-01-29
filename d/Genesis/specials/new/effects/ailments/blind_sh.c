/*
 * blind_sh.c
 *
 * 100% blind has been calculated to 135caid
 *
 * Updated by Zizuph, Dec 2021
 *
 * The blind has a 30 second cycle time, and the actual length of
 * blind is based on the CAID given to the ability - 45 CAID will
 * provide 10 seconds of blind, for example.
 * Stat modifiers, skills, chance, and tohit bonuses are also applied to 
 * determine the effective CAID for the player.
 *
 * To account for team size, a blind by default has 2 points per one
 * second of length.  So a 10 second blind would have 20 points.
 * Every second, a blind is decreased by 1 + attack team size points.
 * So for an attacking team of 2, the blind will be reduced by 3 
 * points a second, and last 20/3 = 7 seconds instead of 10.  This accounts
 * for the bonus damage the second player is causing.
 *
 * If there are multiple stacked blinds, these points are only deducted
 * from one of the active blinds.  
 * For example, if two players are fighting a target, and both blind it
 * for 10 seconds each, each blind would be worth 20 points.  3 points
 * would be deducted randomly from the two blinds each second, since the
 * team size is two.  The 40 points will wear out after 40/3 = 14 seconds.
 * Note that this is identical in time if the two players did their 
 * blinds one after the other ended (7 seconds + 7 seconds).  This means
 * that players will not have to time their blinds to get full advantage.
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>

inherit EFFECT_BASE_SH;
inherit "/d/Genesis/specials/calculations";

// Blind effects 
#define BLIND_COOLDOWN_CYCLE 30

// Prototypes
public void         remove_blind_shadow();

// Global Variables
static mapping      gBlindCountdowns = ([]);
static object*      gBlindInstantRemoves = ({});

static int          gBlindCounter;

static int          gBlindShadowAlarmId;

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
 * Function Name:   query_active_blind_effects
 * Description:     Returns the full list of active blind effects currently 
 *                  being kept track of by the effect shadow.  These have not
 *                  had remove_blind_effect called on them yet.
 * Arguments:       None
 * Returns:         (object *) An array of blind effect objects
 */
public object *
query_active_blind_effects()
{
    return m_indexes(gBlindCountdowns);
} /* query_active_blind_effects */


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
        
        m_delkey(gBlindCountdowns, effect);
        effect->end_blind_effect(shadow_who);
        return 1;
    }
    
    return 0;
} /* remove_blind_effect */

public void
decrease_effects()
{
    gBlindCounter++;

    /* If one opponent is present, one attack and defense is affected.
       If two are present, the attack and two defenses of the blinded
       are affected.  If three are present, the attack and three
       defenses or the blinded are present.  We increase the rate of
       blind expiration proportionally based on the total number
       of attacks/defenses affected by the blind.
       
       If there are multiple blinds, we will only deduct from one of
       them.  This will allow stacked blinds to last as long as
       concurrent blinds.
    */
    int decrease = 1;
    object* present_enemies = shadow_who->query_enemy(-1);
    foreach (object enemy : present_enemies)
    {
        if (environment(shadow_who) == environment(enemy))
            decrease++;
    }
    
    decrease = max(2, decrease);
    for (int i = 0; i < decrease; i++)
    {
        if (!m_sizeof(gBlindCountdowns))
            break;
        object effect = one_of_list(m_indexes(gBlindCountdowns));
        gBlindCountdowns[effect] -= 1;
        if (gBlindCountdowns[effect] <= 0)
        {
            send_debug_message("blind_sh", capitalize(effect->query_name())
                + " has ended its blindness.");
            remove_blind_effect(effect);
            
            if (member_array(effect, gBlindInstantRemoves) >= 0)
            {
                remove_effect(effect);
                gBlindInstantRemoves -= ({ effect });
                send_debug_message("blind_sh", capitalize(effect->query_name())
                    + " has been removed.");
                effect->remove_object();
            }
        }
    }
    if ((gBlindCounter % BLIND_COOLDOWN_CYCLE) == 0)
    {
        foreach (object effect : query_blind_effects())
        {
            if (member_array(effect, m_indexes(gBlindCountdowns)) >= 0)
            {
                // It still has time left, let it continue to the
                // next cycle.  It will not keep the cooldown active.
                gBlindInstantRemoves += ({ effect });
                continue;
            }
            remove_effect(effect);
            send_debug_message("blind_sh", capitalize(effect->query_name())
                + " has been removed.");
            effect->remove_object();
        }
        if (!sizeof(query_effects()))
        {
            remove_blind_shadow();
        }
    }
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
    caid = effect->query_effect_modified_combat_aid(player);

    send_debug_message("blind_sh_debug", sprintf("%s has initial caid of %d.",
             capitalize(effect->query_name()), caid));

    send_debug_message("blind_sh_debug", sprintf("%s should have initial caid of %d.",
             capitalize(effect->query_name()), effect->query_effect_combat_aid(player)));
    
    
    // Scale caid based on chance to fail
    caid = caid * 100 / effect->query_blind_chance();

    send_debug_message("blind_sh_debug", sprintf("%s has next caid of %d.",
             capitalize(effect->query_name()), caid));

    if (effect->query_blind_tohit() > 0) {
        
      int hit_reduction = convert_tohit_to_combat_aid_reduction(
          effect->query_blind_tohit());

      send_debug_message("blind_sh_debug", sprintf("%s has a HR of %d %d.",
            capitalize(effect->query_name()), 
            effect->query_blind_tohit(), hit_reduction));
    
        caid = caid * 100 / max(1, 100-hit_reduction);
    }

    send_debug_message("blind_sh_debug", sprintf("%s has a caid of %d.",
             capitalize(effect->query_name()), caid));
    
    // Fetch the time from the effect
    time = itof(BLIND_COOLDOWN_CYCLE);
    
    // Scale time based on the effect caid (divided by caid of 100% blind)
    time = time * itof(caid) / 135.0;
    
    send_debug_message("blind_sh_debug", sprintf("%s has a time of %f.",
             capitalize(effect->query_name()), time));
    
    // Blind affects incoming and outgoing attacks.  Each effect earns credit
    // for affecting one outgoing and one incoming, hence the 2x multiplier.  
    // A minimum of 2 points will be deducted every second, depending on the
    // size of team fighting the blinded.
    gBlindCountdowns[effect] = ftoi(time * 2.0);

    if (!gBlindShadowAlarmId)
    {
        gBlindShadowAlarmId = set_alarm(1.0, 1.0, decrease_effects);
    }
    
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
    foreach (object blind : query_blind_effects())
    {
        // Blinds should not stack on the same target, from the
        // same caster, with the same effect.
        if (blind->query_effect_caster() == effect->query_effect_caster()
            && MASTER_OB(blind) == MASTER_OB(effect))
            {
                return 0;
            }
    }
    
    if (effect->query_blind_valid(shadow_who))
    {
        if (effect->query_blind_chance() >= random(100))
        {
            int blind = shadow_who->query_prop(LIVE_I_BLIND);
        
            shadow_who->add_prop(LIVE_I_BLIND, ++blind);
        
            add_blind_alarm(effect);
            send_debug_message("blind_sh", capitalize(effect->query_name())
                + " has been added.");
            
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
