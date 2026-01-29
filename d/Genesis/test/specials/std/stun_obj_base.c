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
 * Created by Novo, June 2008
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
    set_stun_combat_aid(25);

    setuid();
    seteuid(getuid());
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
public int
query_stun_combat_aid(object player)
{
    return query_effect_combat_aid(player);
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
    return query_effect_percentage(player);
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
    return query_effect_strength(player, attacker, attack_id);
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
    remove_stun_effect(effect_target);
    return ::dispel_effect(dispeler);
}
    

/*
 * Function name: add_stun_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_stun_effect(object target)
{
    if (target && living(target))
    {
        if (!target->has_stun_shadow())
        {
            send_debug_message("base_stun", 
                               "Did not find shadow, creating shadow.");
            clone_object(STUN_SH)->shadow_me(target);
        }
        else
        {
            send_debug_message("base_stun", "Found stun shadow.");
        }
        
        target->add_stun_effect(this_object());
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
    add_stun_effect(query_effect_target());
    return 1;
}
