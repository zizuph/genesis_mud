/*
 * Evade Effect Object
 * 
 * This is the base evade effect object that handles evade in conjunction
 * with the evade shadow. Evade objects stack with one another.
 *
 * An evade object has the following methods defined:
 * int    query_evade_percentage();
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

#include "defs.h"

inherit EFFECT_BASE_OBJ;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         set_evade_combat_aid(int caid);

// Global Variables
public function     Block_function = 0;

/*
 * Function     : set_evade_skills
 * Description  : Set the skills that will be used in calculating
 *                the strength of the evade
 * Arguments    : skills
 * Returns      : nothing
 */
public nomask void 
set_evade_skills(mixed skills)
{
    set_effect_skills(skills);
}

/*
 * Function     : query_evade_skills
 * Description  : Returns the skills being used to calculate evade strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_evade_skills()
{
    return query_effect_skills();
}

/*
 * Function     : set_evade_stats
 * Description  : Set the stats that will be used in calculating
 *                the strength of the evade
 * Arguments    : stats
 * Returns      : nothing
 */
public nomask void 
set_evade_stats(mixed stats)
{
    set_effect_stats(stats);
}

/*
 * Function     : query_evade_stats
 * Description  : Returns the stats being used to calculate evade strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public mixed 
query_evade_stats()
{
    return query_effect_stats();
}

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_base_evade_object_");
    add_name( ({"base_evade_obj" }) );
    set_short("hidden base evade object");    
    set_long("A basic evade object. One should not be able to see it "
           + "in their inventory.\n");

    setuid();
    seteuid(getuid());

    // By default, it doesn't modify by skills nor stats
    set_evade_stats( TS_DEX );
    set_evade_skills( SS_DEFENCE );
    // 25% combat aid == 20% evade
    set_evade_combat_aid(25);
}

/*
 * Function     : set_evade_combat_aid
 * Description  : Sets the evade combat aid which is used to determine
 *                the evade percentage
 * Arguments    : combat aid number
 * Returns      : nothing
 */
public nomask void
set_evade_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
}

/*
 * Function     : query_evade_combat_aid
 * Description  : returns the evade combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public int
query_evade_combat_aid(object player)
{
    return ::query_effect_combat_aid(player);
}

/*
 * Function     : query_effect_combat_aid
 * Description  : returns the effect combat aid for player
 * Arguments    : player - the player who is receiving combat aid
 * Returns      : combat aid number
 */
public nomask int
query_effect_combat_aid(object player)
{
    return query_evade_combat_aid(player);
}

/*
 * Function     : query_evade_percentage
 * Description  : Returns the max percentage set during creation
 * Arguments    : none
 * Returns      : the evasion percentage
 */
public nomask int 
query_evade_percentage(object player)
{
    return query_effect_percentage(player);
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{
    return 1;
}

/*
 * Function:    set_blocked_function
 * Description: A person who creates the evade object can define their own
 *              function that they want called when the evade happens.
 *              Call this to set it and have custom descriptions.
 */
public void
set_blocked_function(function func)
{
    Block_function = func;
}

// Evade shadow does not support likelyhood.
public nomask void set_effect_likelyhood(int likelyhood)
{
    return;
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    if (functionp(Block_function))
    {
        // If a custom block function has been defined, we use that instead.
        Block_function(player, attacker, attack_id);
        return;
    }
    
    player->catch_msg("You block the attack of "+QTNAME(attacker)+".\n");
    attacker->catch_msg(QCTNAME(player)+" blocks your attack.\n");
    tell_room(environment(player), QCTNAME(attacker) + " tries to "
            + "attack " + QTNAME(player) + ", but the attack is "
            + "blocked.\n", ({ player, attacker }), player);
}


/*
/*
 * Function name: remove_evade_effect
 * Description:   Remove this evade from a target, also removing the evade
 *                shadow as needed
 * Arguments:     object target - the one affected by the evade
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_evade_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        send_debug_message("base_evade", "Master object, will not process "
                                       + "shadow check.");
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_evade_effect(this_object());
    if (!sizeof(target->query_evade_effects()) 
        && target->has_evade_shadow())
    {
        send_debug_message("base_evade", "Removing shadow because there "
                         + "are no more effects.");
        target->remove_evade_shadow();
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
        remove_evade_effect(shadowobj->query_shadow_who());
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
 * Function name: add_evade_effect
 * Description;   Add this effect to a target
 * Returns:       1/0 - effect added/not added
 */
public int add_evade_effect(object target)
{
    if (target && living(target))
    {
        if (!target->has_evade_shadow())
        {
            send_debug_message("base_evade", 
                               "Did not find shadow, creating shadow.");
            clone_object(EVADE_SH)->shadow_me(target);
        }
        else
        {
            send_debug_message("base_evade", "Found evade shadow.");
        }
        
        target->add_evade_effect(this_object());
        return 1;
    }    
    return 0;
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
    add_evade_effect(query_effect_target());
    return 1;
}
