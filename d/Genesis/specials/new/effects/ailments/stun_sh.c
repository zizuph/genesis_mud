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
 *
 * Created by Petros, September 2008
 *   (Original evade shadow written by Petros, Original Stun shadow
 *    based on evade shadow adapted by Novo. This is the latest 
 *    incarnation)
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
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public int              stun_shadow_stun();
public mixed *          calculate_stun_times();
public object *         query_stun_effects();

// Global variables
private int full_stuns;
private int last_stun_result;
private int is_removing = 0;

private int stun_alarm = 0;
private int cooldown_alarm = 0;

// Defines
#define LIVE_I_STUN_BEGIN           "_live_i_stun_begin"

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
 * Function     : remove_stun_shadow
 * Description  : Easy way to remove shadow
 * Arguments    : none
 */
public void
remove_stun_shadow()
{
    is_removing = 1;
    shadow_who->add_prop(LIVE_I_STUNNED,full_stuns);
    remove_shadow();
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
query_max_stun_percentage()
{
    return query_effect_percentage(query_effects());
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
query_max_stun_combat_aid()
{
    return query_effect_combat_aid(query_effects());
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
    remove_effect(obj);
    send_debug_message("stun_sh", "Removing stun effect " 
                     + obj->query_name() + ".");
}

public nomask int
query_is_stunned()
{
    if (pointerp(get_alarm(stun_alarm)))
    {
        return 1;
    }
    
    return 0;
    
/*    
    mixed * stun_times;
    float stun_time;
    int current_time, start_time;

    if (pointerp(get_alarm(stun_alarm)))
    {
        send_debug_message("stun_sh", "Is stunned.");
    }
    else
    {
        send_debug_message("stun_sh", "Is not stunned.");
    }
    
    stun_times = calculate_stun_times();
    stun_time = 0.0;
    current_time = time();
    start_time = shadow_who->query_prop(LIVE_I_STUN_BEGIN);
    
    if (!pointerp(stun_times))
    {
        send_debug_message("stun_sh", "Error occurred while calculating "
                         + "stun times.");
        return 0;
    }

    if (intp(stun_times[0]))
    {
        stun_time = itof(stun_times[0]);
    }
    else if (floatp(stun_times[0]))
    {
        stun_time = stun_times[0];
    }
    
    // Start Time + Stun Time translates to the end of the stun period
    if (current_time <= start_time + ftoi(stun_time + 1.0))
    {
        return 1;
    }

    return 0;    */
}

public nomask int
query_in_cooldown()
{
    if (!query_is_stunned() && pointerp(get_alarm(cooldown_alarm)))
    {
        return 1;
    }
    
    return 0;
/*
    mixed * stun_times;
    float stun_time, cooldown_time;
    int current_time, start_time;
    
    stun_times = calculate_stun_times();
    stun_time = 0.0;
    cooldown_time = 0.0;
    current_time = time();
    start_time = shadow_who->query_prop(LIVE_I_STUN_BEGIN);
    
    if (!pointerp(stun_times))
    {
        send_debug_message("stun_sh", "Error occurred while calculating "
                         + "stun times.");
        return 0;
    }

    if (intp(stun_times[0]))
    {
        stun_time = itof(stun_times[0]);
    }
    else if (floatp(stun_times[0]))
    {
        stun_time = stun_times[0];
    }
    
    if (intp(stun_times[1]))
    {            
        cooldown_time = itof(stun_times[1]);
    }
    else if (floatp(stun_times[1]))
    {
        cooldown_time = stun_times[1];
    }
    
    // Start Time + Stun Time translates to the end of the stun period
    if (current_time < start_time + ftoi(stun_time + cooldown_time))
    {
        return 1;
    }

    return 0;    */
}

public void
notify_stun_end(object player)
{
    int effect_size;
    object * effects;
    
    effects = query_stun_effects();
    effect_size = sizeof(effects);
    if (effect_size > 0)
    {
        effects[random(effect_size)]->hook_stun_ended(player);
    }
    
    send_debug_message("stun_sh", "Stun has ended. Cooldown beginning.");
}

public void
remove_stun_after_cooldown(object player)
{
    send_debug_message("stun_sh", "Cooldown ended. Removing stun effects.");
    foreach (object effect : query_stun_effects())
    {
        effect->remove_object();
    }
}

public void
reset_stun_alarms()
{
    mixed * stun_times;
    int start_time, current_time;
    
    current_time = time();
    start_time = shadow_who->query_prop(LIVE_I_STUN_BEGIN);
    start_time = current_time - start_time;
    
    // Alarms are reset in the following situations:
    // 1. Before stun has begun
    // 2. During stun
    // It is never reset during the cooldown period.
    if (query_in_cooldown())
    {
        return;
    }
/*
    if (!query_is_stunned())
    {
        // Alarms are only reset during stunning.
        return;
    }
*/    
    stun_times = calculate_stun_times();
    remove_alarm(stun_alarm);
    remove_alarm(cooldown_alarm);
    stun_alarm = set_alarm(stun_times[0] - itof(start_time), 0.0, 
                           &notify_stun_end(shadow_who));
    send_debug_message("stun_sh", "Stun will last for " 
                     + ftoi(stun_times[0] - itof(start_time))
                     + " more seconds.");
    cooldown_alarm = set_alarm(stun_times[0] + stun_times[1] 
                               - itof(start_time), 0.0,
                               &remove_stun_after_cooldown(shadow_who));
    send_debug_message("stun_sh", "Cooldown will end in " 
                     + ftoi(stun_times[0] + stun_times[1] - itof(start_time))
                     + " more seconds.");
}

/*
 * Function     : add_stun_effect
 * Description  : Adds the stun effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask int
add_stun_effect(object obj)
{   
    /*
    This section prevented someone from double stunning a target,
    Since we block all stacking stuns below, it is not needed.
    
    foreach (object stun : query_effects())
    {
        // Disarms should not stack on the same target, from the
        // same caster, with the same effect.
        if (stun->query_effect_caster() == obj->query_effect_caster()
            && MASTER_OB(stun) == MASTER_OB(obj))
            {
                obj->hook_stun_cooldown_in_effect(shadow_who);
                return 0;
            }
    }
    */
    
    if (query_is_stunned())
    {
        // We're currently stunned and adding another stun effect.
        //add_effect(obj);
        //send_debug_message("stun_sh", "Adding stun effect " 
        //                 + obj->query_name() + " to existing stuns.");
        // Stuns are not stacking well, so we will only allow one at a time.
        obj->hook_stun_cooldown_in_effect(shadow_who);
        obj->remove_object();
        return 0;                         
    }
    else if (query_in_cooldown())
    {
        // We're currently in the cooldown period and no more stun
        // effects are allowed to be added.
        send_debug_message("stun_sh", "In cooldown period and trying to "
                         + "add a stun effect.");
        obj->hook_stun_cooldown_in_effect(shadow_who);
        obj->remove_object();
    }
    else
    {
        // We're completely outside of the effect. We add the effect
        // as the first one.        
        add_effect(obj);
        send_debug_message("stun_sh", "Adding stun effect " 
                         + obj->query_name() + " as first stun.");
        
        // Remove all other effects
        foreach (object effect : query_stun_effects())
        {
            if (obj == effect)
            {
                continue;
            }
            effect->remove_object();
        }
        
        // Set the stun start time
        shadow_who->add_prop(LIVE_I_STUN_BEGIN, time());
    }
    
    reset_stun_alarms();
    return 1;
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
    return query_effects();
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
    ++full_stuns;
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
        --full_stuns;
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
        return 0;
    }
    if (!intp(val))
    {
        return 0;
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
        return 0;
    }
    shadow_who->add_prop(LIVE_I_STUNNED,stun_shadow_stun);
    full_stuns=0;
    return 1;
}
   

/*
 * Function     : stun_shadow_stun
 * Description  : VBFC function set inside of LIVE_I_STUNNED property
 *                Evaluates each effect separately in determining whether
 *                the person is stunned or not.
 * Arguments    : none
 * Returns      : result of whether stunned or not
 */
public int 
stun_shadow_stun()
{
    int effect_size;
    object * effects;
    object effect;
    
    if (full_stuns)
    {
        last_stun_result = full_stuns;
        return full_stuns;
    }

    last_stun_result = query_is_stunned();
    if (last_stun_result)
    {
        // We are currently stunned. We will randomly select
        // an effect and call its blocking code to print its
        // messages
        effects = query_stun_effects();        
        effect_size = sizeof(effects);
        if (effect_size > 0)
        {
            effect = effects[random(effect_size)];
            send_debug_message("stun_sh", capitalize(effect->query_name())
                + " caused a stun.");
            effect->attack_blocked(shadow_who);
        }
    }                        

    return last_stun_result;
}

/*
 * Function     : shadow_me
 * Description  : This is the function used to add the shadow to someone.
 *                We override it here to set up the stun property
 *                with a VBFC function stun_shadow_stun.
 * Arguments    : to_shadow
 * Returns      : result of whether the shadow was successful or not
 */
public varargs int 
shadow_me(mixed to_shadow)
{
    int result=::shadow_me(to_shadow);
    if (result)
    {
        full_stuns=shadow_who->query_prop(LIVE_I_STUNNED);
        shadow_who->add_prop(LIVE_I_STUNNED,stun_shadow_stun);
    }
    return result;
}

int 
sort_descending(object a, object b) 
{ 
    int a_pct, b_pct, a_cycle, b_cycle, a_time, b_time;
    
    a_pct = a->query_stun_percentage();
    b_pct = b->query_stun_percentage();
    a_cycle = a->query_stun_cycle_time(shadow_who);
    b_cycle = b->query_stun_cycle_time(shadow_who);
    a_time = a_pct * a_cycle;
    b_time = b_pct * b_cycle;
    
    if (a_time == b_time)
    {
        return 0;
    }
    else if (a_time < b_time)
    {
        return 1;
    }
    else if (a_time > b_time)
    {
        return -1;
    }
}

public mixed *
calculate_stun_times()
{
    int cycle, total_caid, stun_caid;
    float total_stun, total_cooldown, total_percentage;
    float stun_time, stun_percentage;
    object * sorted_effects;
    
    // Initialize
    total_caid = 0;
    total_stun = 0.0;
    total_cooldown = 0.0;
    total_percentage = 1.0;
    sorted_effects = sort_array(query_stun_effects(), sort_descending);
    foreach (object effect : sorted_effects)
    {
        object caster = effect->query_effect_caster();
        stun_percentage = itof(effect->query_stun_percentage(caster)) / 100.0;
        send_debug_message("stun_sh", sprintf(
            "Stun percentage: %2.0f",
            stun_percentage * 100.0));

        total_percentage *= stun_percentage;
        stun_percentage = total_percentage;
        stun_caid = effect->query_stun_combat_aid(caster);
        send_debug_message("stun_sh", sprintf(
            "Stun caid: %d",
            stun_caid));
        total_caid += stun_caid;
        cycle = effect->query_stun_cycle_time(caster);
        stun_time = stun_percentage * itof(cycle);
        total_stun += stun_time;
    }
    
    // Cooldown time is calculated using the total stun time and the
    // total combat aid of all the effects. Adding more stunners
    if (total_caid > 0)
    {
        total_cooldown = total_stun * 100.0 / itof(total_caid);
        // We cap the cooldown so that it doesn't become silly.
        if (total_cooldown > total_stun * 3.0)
        {
            total_cooldown = total_stun * 3.0;
        }
    }
    
    return ({ total_stun, total_cooldown });
}
