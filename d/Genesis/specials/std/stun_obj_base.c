/*
 * Stun Effect Object
 * 
 * This is the base stun effect object that handles stun in conjunction
 * with the stun shadow. stun objects stack with one another.
 *
 * An stun object has the following methods defined:
 * int    query_stun_percentage();
 * int    query_stun_strength(object player, object attacker, 
                               int attack_id);
 * int    query_stun_valid(object player, object attacker, 
 *                          int attack_id);
 * void   attack_blocked(object player);
 *
 * Created by Petros, September 2008
 *   (Original evade shadow written by Petros, Original Stun shadow
 *    based on evade shadow adapted by Novo. This is the latest 
 *    incarnation)
 */
 
#pragma strict_types

#include "defs.h"

inherit EFFECT_BASE_OBJ;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

// Prototypes
public void         set_stun_combat_aid(int caid);
public void         set_stun_cycle_time(int cycle);
public void         set_stun_chance(int percentage);
public void         set_stun_tohit(int percentage);
public void         hook_stun_begin(object stunner, object stunnee);
public int          query_stun_combat_aid(object player);

// Global Variables
static int       m_cycle = 30;
static int       m_stunChance = 100;
static int       m_stunTohit = 100;

/*
 * Function     : set_stun_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the stun
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_stun_skills(mixed skills)
{
    set_effect_skills(skills);
}

/*
 * Function     : query_stun_skills
 * Description  : Returns the skills being used to calculate stun strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_stun_skills()
{
    return query_effect_skills();
}

/*
 * Function     : set_stun_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the stun
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_stun_stats(mixed stats)
{
    set_effect_stats(stats);
}

/*
 * Function     : query_stun_stats
 * Description  : Returns the stats being used to calculate stun strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_stun_stats()
{
    query_effect_stats();
}

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_base_stun_object_");
    add_name( ({"base_stun_obj" }) );
    set_short("hidden base stun object");    
    set_long("A basic stun object. One should not be able to see it "
           + "in their inventory.\n");

    set_stun_stats( TS_DEX );
    set_stun_skills( SS_DEFENCE );
    // 25% combat aid == 20% stun
    set_stun_combat_aid(100);
    // By default stun always hits 100%
    set_stun_chance(100);
    // By default stun is always triggered at 100%
    set_stun_tohit(100);
    // Cycle time of 30 seconds == 15 seconds stun, 15 seconds cooldown
    // if the aid is 100%. At 25% combat aid, this equals 5 seconds
    // of stun, and 15 seconds of cooldown.
    set_stun_cycle_time(30);
    
    setuid();
    seteuid(getuid());
}

/*
 * Function     : query_stun_percentage
 * Description  : Returns the max percentage set during creation
 * Arguments    : none
 * Returns      : the stun percentage
 */
public nomask int 
query_stun_percentage(object player)
{
    int caid, effect_percentage;
    // Formula for Calculating effect percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    caid = query_stun_combat_aid(player);
    effect_percentage = (100 * caid) / (100 + caid);    
    effect_percentage = effect_percentage < 0 ? 0 : effect_percentage;
    effect_percentage = effect_percentage > 100 ? 100 : effect_percentage;
    return effect_percentage;
}

/*
 * Function     : set_stun_cycle_time
 * Description  : The cycle time plus the combat aid determines how long
 *                the stun will last. eg. A 100% stun for 20 seconds
 *                equals 10 seconds of stun, and 10 seconds of cooldown.
 * Arguments    : cycle - time in seconds for the cycle
 * Returns      : nothing
 */
public nomask void
set_stun_cycle_time(int cycle)
{
    m_cycle = cycle;    
}

/*
 * Function     : query_stun_cycle_time
 * Description  : Returns the cycle time for the stun
 * Arguments    : none
 * Returns      : the stun cycle time
 */
public nomask int 
query_stun_cycle_time(object player)
{
    return m_cycle;
}

/*
 * Function     : set_stun_chance
 * Description  : Sets the chance that the stun will have effect.
 * Arguments    : percentage between 0 and 100
 * Returns      : nothing
 */
public nomask void
set_stun_chance(int percentage)
{
    if (percentage < 0)
    {
        percentage = 0;
    }
    else if (percentage > 100)
    {
        percentage = 100;
    }
    m_stunChance = percentage;
}

/*
 * Function     : query_stun_chance
 * Description  : returns the chance that the stun will succeed
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_stun_chance(object player)
{
    return m_stunChance;
}

/*
 * Function     : set_stun_tohit
 * Description  : This sets the percentage that the stun will actually
 *                hit because of an external ability. For example, if
 *                a shield slam causes the stun, then the tohit percentage
 *                of the shield slam would be set here.
 * Arguments    : percentage between 0 and 100
 * Returns      : nothing
 */
public nomask void
set_stun_tohit(int percentage)
{
    if (percentage < 0)
    {
        percentage = 0;
    }
    else if (percentage > 100)
    {
        percentage = 100;
    }
    m_stunTohit = percentage;
}

/*
 * Function     : query_stun_tohit
 * Description  : returns the chance that the stun will actually be
 *                triggered.
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : percentage for the ability triggering the stun
 */
public nomask int
query_stun_tohit(object player)
{
    return m_stunTohit;
}

/*
 * Function     : set_stun_combat_aid
 * Description  : Sets the stun combat aid which is used to determine
 *                the stun percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_stun_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
}

/*
 * Function     : query_stun_combat_aid
 * Description  : returns the stun combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_stun_combat_aid(object player)
{
    int percentage, chance, tohit;
    
    // The actual stun combat aid is modified by the stun chance
    // as well as the declared miss chance
    percentage = ::query_effect_combat_aid(player);
    chance = query_stun_chance(player);
    tohit = query_stun_tohit(player);
    if (chance > 0)
    {
        percentage = percentage * 100 / chance;
    }
    
    if (tohit > 0)
    {
        percentage = percentage * 100 / tohit;
    }
    send_debug_message("base_stun", "Final stun combat aid after "
                     + "adjustment is " + percentage + ".");
    return percentage;
}

/*
 * Function     : query_effect_combat_aid
 * Description  : returns the effect combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_effect_combat_aid(object player)
{
    return query_stun_combat_aid(player);
}

/*
 * Function     : query_stun_strength
 * Description  : Function that will be used to gauge the strength of
 *                the stun based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the stun percentage
 */
public varargs int
query_stun_strength(object player, object attacker, int attack_id)
{
    return ::query_effect_strength(player, attacker, attack_id);
}                            

/*
 * Function     : query_effect_strength
 * Description  : Function that will be used to gauge the strength of
 *                the effect based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the effect percentage
 */
public int
query_effect_strength(object player, object attacker, int attack_id)
{
    return query_stun_strength(player, attacker, attack_id);
}

/*
 * Function     : query_stun_valid
 * Description  : Validation function to see whether this stun object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_stun_valid(object player)
{
    return 1;
}

/*
 * Function name: remove_stun_effect
 * Description:   Remove this stun from a target, also removing the stun
 *                shadow as needed
 * Arguments:     object target - the one affected by the stun
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_stun_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_stun", "Master object, will not process "
                                       + "shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_stun_effect(this_object());
    if (!sizeof(target->query_stun_effects()) 
        && target->has_stun_shadow())
    {
        send_debug_message("base_stun", "Removing shadow because there "
                         + "are no more effects.");        
        target->remove_stun_shadow();
    }
    return 1;
}

/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none
 * Returns:       nothing
 */
public void
remove_object()
{
    foreach (object shadowobj : query_shadow_list())
    {
        remove_stun_effect(shadowobj->query_shadow_who());
    }
    ::remove_object();
}

/*
/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    remove_object();
    return ::dispel_effect(dispeler);
}
    

/*
 * Function name: add_stun_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_stun_effect(object target)
{
    if (random(100) >= query_stun_chance(target))
    {
        // The stun chance did not succeed. In this case, we just
        // return.
        send_debug_message("base_stun", "Stun chance failed. Object is "
                         + "to be removed.");
        remove_object();
        return 0;
    }

    // Objects which cannot be stunned should not have the stun effect added.
    if (target->query_prop(LIVE_I_NO_STUN))
    {
        send_debug_message("base_stun", "Target cannot be stunned. Object is to be removed.");
        remove_object();
        return 0;
    }

    if (target && living(target))
    {
        if (!target->has_stun_shadow())
        {
            send_debug_message("base_stun", "Did not find shadow, creating shadow.");
            object sh = clone_object(STUN_SH);
            if (!sh->shadow_me(target)) {
                send_debug_message("base_stun", "Could not add shadow, stun failed.");
                sh->remove_object();
                remove_object();
                return 0;
            }
        }
        else
        {
            send_debug_message("base_stun", "Found stun shadow.");
        }
        
        target->add_stun_effect(this_object());
        hook_stun_begin(query_effect_caster(), query_effect_target());
        return 1;
    }    
    return 0;
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked because the player is stunned
 * Arguments    : player    - player who is trying to attack
 * Returns      : nothing
 */
public void
attack_blocked(object player)
{
    object enemy;
    
    enemy = player->query_attack();
    if (enemy)
    {
        // There's a person that is being fought. We display messages
        // about the stun.
        player->catch_msg("You attempt to attack " + QTNAME(enemy)
                         + ", but find that you are stunned.\n");
        enemy->catch_msg(QCTNAME(player) + " tries to attack you, but "
                           + "cannot seem to move.\n");
        tell_room(environment(player), QCTNAME(player) + " tries to "
                + "attack " + QTNAME(enemy) + ", but cannot seem to "
                + "move.\n", ({ player, enemy }), player);
    }        
}

public void
hook_stun_cooldown_in_effect(object player)
{
    player->catch_msg("You shrug off the attempts to hinder your "
                    + "movements.\n");
    player->tell_watcher(QCTNAME(player) + " shrugs off the attempt "
                       + "to hinder " + player->query_possessive()
                       + " movements.\n", ({ }));
}

public void
hook_stun_ended(object player)
{
    player->catch_msg("You feel like you can move freely again.\n");
    player->tell_watcher(QCTNAME(player) + " seems to be able to move "
                       + "freely again.\n");
}

public void
hook_stun_begin(object attacker, object target)
{
    if (!objectp(target))
    {
        return;
    }
    
    if (objectp(attacker))
    {            
        target->catch_msg(QCTNAME(attacker) + " stuns you!\n");
        target->tell_watcher(QCTNAME(attacker) + " stuns " + QCTNAME(target));
    }
    else
    {
        target->catch_msg("You have been stunned!\n");
        target->tell_watcher(QCTNAME(target) + " has been stunned!\n");
    }
}

/*
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    return add_stun_effect(query_effect_target());
}
