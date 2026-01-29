/*
 * Evade Effect Object
 * 
 * This is the base evade effect object that handles evade in conjunction
 * with the evade shadow. Evade objects stack with one another.
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

#include "./defs.h"

inherit (ABILITY_DIR+"effect_object");
inherit "/std/object";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

// Prototypes
public void         set_evade_combat_aid(int caid);

// Global Variables
private int         Evade_combat_aid;
private mixed       Skills_used;
private mixed       Stats_used;

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
   Skills_used=skills;   
}

/*
 * Function     : query_evade_skills
 * Description  : Returns the skills being used to calculate evade strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_evade_skills()
{
    return Skills_used;
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
   Stats_used=stats;   
}

/*
 * Function     : query_evade_stats
 * Description  : Returns the stats being used to calculate evade strength
 * Arguments    : none
 * Returns      : Skills_used variable
 */
public nomask mixed 
query_evade_stats()
{
    return Stats_used;
}

/*
 * Function     : create_evade_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_evade_effect()
{    
}

/*
 * Function     : create_object
 * Description  : Creates the base evade object
 * Arguments    : none
 * Returns      : nothing
 */
public nomask void
create_object()
{
    set_name("_base_evade_object_");
    add_name( ({"base_evade_obj" }) );
    set_short("hidden base evade object");    
    set_long("A basic evade object. One should not be able to see it "
           + "in their inventory.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    // By default, it doesn't modify by skills nor stats
    set_evade_stats( TS_DEX );
    set_evade_skills( SS_DEFENCE );
    // 25% combat aid == 20% evade
    set_evade_combat_aid(25);
    
    // Register debugger tags
    register_debugger_tag("base_evade");

    setuid();
    seteuid(getuid());

    create_evade_effect();
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
    Evade_combat_aid = caid;
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
    return Evade_combat_aid;
}

/*
 * Function name: find_drm
 * Description  : Converts the stat list/skill list to an actual number
 * Arguments    : player - player executing special
 *                tasks - resolve_task style list of tasks
 * Returns      : actual stat/skill value
 */
public nomask int find_drm(object actor,mixed tasks)
{
    int result=actor->find_drm(tasks);
    result/=2; 
    return result;
}

/*
 * Function name: find_total_weight
 * Description  : Calculates the total weight going into a task
 * Arguments    : tasks - resolve_task style list of tasks
 * Returns      : sum of weights
 */
public nomask int find_total_weight(mixed tasks)
{
    int sum=0;
    int i = 0;
    int mod=0;
    int weight = 100;
    while(i < sizeof(tasks)) 
    {
        if (mod != 0)
            weight = 100;
        mod = 0;

        /* this added because the switch below can only take an
         * integer argument.
         */
        if (functionp(tasks[i]) || stringp(tasks[i]))
        {
            mod = 1;
        }
        else
        {
 	        switch (tasks[i]) 
            {
                case SKILL_MIN:
                case SKILL_MAX:
                case SKILL_AVG:
                    i++;
                    for(; i < sizeof(tasks) && tasks[i] != SKILL_END; i++) 
                    {
                        mod=1;
                    }
                break;

                case SKILL_WEIGHT:
                    i++;
                    weight = tasks[i++];
                    mod = 0;
                break;

                case SKILL_VALUE:
                    i++;
                    mod = 1;
                    i++;
                break;

                case SKILL_END:
                    i++;
                break;

                default:
                    mod = 1;
                    i++;
	            break;
            }
        }

        sum += weight;
    }
    return sum;
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier(object player)
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return 100;
}


/*
 * Function name: calc_stat_modifier
 * Description  : Obtains a modifier based on the players stats
 * Arguments    : player - player evading
 * Returns      : modifier
 */
public nomask int 
calc_stat_modifier(object player)
{
    if (intp(query_evade_stats()))
    {
        return find_drm(player, ({ query_evade_stats() }));
    }
    return find_drm(player, query_evade_stats());
}

/*
 * Function name: calc_base_skill
 * Description  : Obtains a modifier based on the players skills
 * Arguments    : player - player evading
 * Returns      : modifier
 */
public nomask int 
calc_base_skill(object player)
{
    if (intp(query_evade_skills()))
    {
        return max(15, find_drm(player, ({ query_evade_skills() })));
    }
    return max(15, find_drm(player, query_evade_skills()));
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
    // Formula for Calculating evade percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    int caid=query_evade_combat_aid(player);
    int evade_percentage = (100 * caid) / (100 + caid);    
    evade_percentage = evade_percentage < 0 ? 0 : evade_percentage;
    evade_percentage = evade_percentage > 100 ? 100 : evade_percentage;
    return evade_percentage;
}

/*
 * Function     : query_evade_strength
 * Description  : Function that will be used to gauge the strength of
 *                the evade based on the situation. 
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : the modified value of the evasion percentage
 */
public int
query_evade_strength(object player, object attacker, int attack_id)
{
    int evade = query_evade_percentage(player);
    evade = evade * calc_base_skill(player);
    evade = evade * F_STR_FACTOR(calc_stat_modifier(player)) / 10000;
    evade = evade * query_combat_aid_modifier(player) / 100;
    send_debug_message("base_evade", "Evade Strength: " + evade);
    return evade;
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
    player->catch_msg("You block the attack of "+QTNAME(attacker)+".\n");
    attacker->catch_msg(QCTNAME(player)+" blocks your attack.\n");
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
        target->remove_evade_shadow();
    }
    return 1;
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
    remove_evade_effect(effect_target);
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
    add_evade_effect(effect_target);
    return 1;
}
