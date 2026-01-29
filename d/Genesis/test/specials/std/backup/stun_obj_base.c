/*
 * stun Effect Object
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
public void         set_stun_combat_aid(int caid);

// Global Variables
private int         stun_combat_aid;
private mixed       Skills_used;
private mixed       Stats_used;

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
   Skills_used=skills;   
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
    return Skills_used;
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
   Stats_used=stats;   
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
    return Stats_used;
}

/*
 * Function     : create_stun_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_stun_effect()
{    
}

/*
 * Function     : create_object
 * Description  : Creates the base stun object
 * Arguments    : none
 * Returns      : nothing
 */
public nomask void
create_object()
{
    set_name("_base_stun_object_");
    add_name( ({"base_stun_obj" }) );
    set_short("hidden base stun object");    
    set_long("A basic stun object. One should not be able to see it "
           + "in their inventory.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    // By default, it doesn't modify by skills nor stats
    set_stun_stats( TS_DEX );
    set_stun_skills( SS_DEFENCE );
    // 25% combat aid == 20% stun
    set_stun_combat_aid(25);
    
    // Register debugger tags
    register_debugger_tag("base_stun");

    setuid();
    seteuid(getuid());

    create_stun_effect();
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
    stun_combat_aid = caid;
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
    return stun_combat_aid;
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
    if (intp(query_stun_stats()))
    {
        return find_drm(player, ({ query_stun_stats() }));
    }
    return find_drm(player, query_stun_stats());
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
    if (intp(query_stun_skills()))
    {
        return max(15, find_drm(player, ({ query_stun_skills() })));
    }
    return max(15, find_drm(player, query_stun_skills()));
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
    // Formula for Calculating stun percentage from the combat aid (c)
    //   (100 * c) / (100 + c)
    // eg. 25% combat aid => (100 * 25) / (100 + 25) = 20%
    int caid=query_stun_combat_aid(player);
    int stun_percentage = (100 * caid) / (100 + caid);    
    stun_percentage = stun_percentage < 0 ? 0 : stun_percentage;
    stun_percentage = stun_percentage > 100 ? 100 : stun_percentage;
    return stun_percentage;
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
public int
query_stun_strength(object player)
{
    int stun = query_stun_percentage(player);
    stun = stun * calc_base_skill(player);
    stun = stun * F_STR_FACTOR(calc_stat_modifier(player)) / 10000;
    stun = stun * query_combat_aid_modifier(player) / 100;
    send_debug_message("base_stun", "stun Strength: " + stun);
    return stun;
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
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player)
{
}


/*
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
        target->remove_stun_shadow();
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
 * Function name: start
 * Description;   Start up the spell effect.  This should be redefined
 *                to provide specific behaviour for a given spell
 *                effect.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    add_stun_effect(effect_target);
    return 1;
}
