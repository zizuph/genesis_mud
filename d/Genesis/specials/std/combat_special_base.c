/*
 * Base Combat Special
 *
 * This base object contains all of the functions that you need
 * to implement a combat special. See the damage special for 
 * an example of how it can be inherited and used.
 *
 * Created by Petros, July 2016
 */
#pragma strict_types

#include "defs.h"
inherit TIMED_ABILITY_LIB;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include "/std/combat/combat.h"
#include "../debugger/debugger_tell.h"

static int  Special_tohit,
            Special_dt,
            Special_aid=100;
            
static mixed
            Skills_used,
            Stats_used;           

static int  Special_gstat_type = 0,
            Special_gstat_min_pct = 20,
            Special_gstat_cap = 100;
            
public mixed * verify_present_or_enemy(object actor, 
            mixed *targets, string arg);
public mixed * verify_change_enemy(object actor, 
            mixed *targets, string arg);

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    player->add_fatigue(-2);
}

public void set_tohit(int i)
{
    Special_tohit=i;
}

public void set_dt(int i)
{
    Special_dt=i;
}

/*
 * Function name: set_guild_stat_modifier
 * Description  : For damage specials, we want to provide a way
 *                for GMs to scale the damage of their specials
 *                based on the guild stat. By calling this function
 *                They can specify which guild stat to use, what
 *                the minimum damage percentage should be when the
 *                player has no guild stat at all, and also at
 *                what guild stat the player achieves the full power
 *                of the special.
 * Arguments    : guild_type - This is the value for one of the guild
 *                             stats, like SS_LAYMAN, SS_OCCUP, etc.
 *                min_pct - This is the minimum percentage that the
 *                          special will have when the person has
 *                          no guild stat. This is what players will
 *                          see when they initially enter the guild
 *                cap - This is the guild stat cap at which the player
 *                      achieves the full amount of the damage. For
 *                      example, if you set this to 150. Then when a
 *                      player achieves 150 guild stat, then they will
 *                      no longer have their damage reduced in the
 *                      calculate_damage function.
 * Returns      : nothing
 */
public void 
set_guild_stat_modifier(int guild_type, int min_pct, int cap)
{
    switch (guild_type)
    {
    case SS_RACE:
    case SS_OCCUP:
    case SS_LAYMAN:
    case SS_CRAFT:    
        Special_gstat_type = guild_type;
        break;
    default:
        Special_gstat_type = 0;
    }
    
    if (min_pct < 0)
    {
        min_pct = 0;
    }
    else if (min_pct > 100)
    {
        min_pct = 100;
    }
    
    Special_gstat_min_pct = min_pct;
    Special_gstat_cap = cap;
}

public int
query_guild_stat_minimum_percentage(object player)
{
    return Special_gstat_min_pct;
}

public int
query_guild_stat_type(object player)
{
    return Special_gstat_type;
}

public string
query_guild_stat_type_desc(object player)
{        
    switch (query_guild_stat_type(player))
    {
    case SS_RACE:
        return "Race";
        
    case SS_OCCUP:
        return "Occupational";
        
    case SS_LAYMAN:
        return "Layman";
        
    case SS_CRAFT:    
        return "Craft";
    }
    
    return "None";
}

public int
query_guild_stat_cap(object player)
{
    return Special_gstat_cap;
}

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Typically only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int query_dt(object * items)
{
    return Special_dt;
}

/*
 * Function name: query_tohit
 * Description  : Calculates the tohit for the player. Based on
 *                swarm knowledge or wisdom
 * Arguments    : none
 * Returns      : input to cb_tohit function
 */
public int query_tohit()
{
    return Special_tohit;
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
public int query_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return 100;
}

public void set_combat_aid(int aid)
{
    Special_aid = aid;
}

public nomask int query_combat_aid()
{
    int modifier;
    
    // The combat aid can change by situation. Query for
    // the modifier to change the combat aid for the
    // current situation.
    modifier = query_combat_aid_modifier();
    modifier = modifier > 100 ? 100 : modifier;
    modifier = modifier < 1 ? 1 : modifier;
    return (Special_aid * modifier) / 100;
}

public void set_skills(mixed skills)
{
   Skills_used=skills;   
}

public mixed query_skills()
{
    return Skills_used;
}

public void set_stats(mixed stats)
{
   Stats_used=stats;   
}

public mixed query_stats()
{
    return Stats_used;
}

/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void config_ability()
{
    ::config_ability();
    set_combat_aid(100);
    set_tohit(75);
    set_ability_time(15);
    set_ability_offensive(1);
    set_ability_visual(0);
    set_dt(W_BLUDGEON);
    set_skills(({ SS_UNARM_COMBAT }));
    set_stats(TS_STR);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_ability_target_verify(verify_change_enemy);
    
    // Set the scaling functions for the ability. by default, we
    // don't know what guild stat will be used
    set_guild_stat_modifier(0, 20, 100);
}

public nomask int calc_stat_modifier()
{
    if (intp(query_stats()))
    {
        return find_drm(this_player(), ({ query_stats() }));
    }
    return find_drm(this_player(),query_stats());
}

public int calc_base_pen(mixed  * items)
{
    if (sizeof(items))
    {
        int count=0;
        int total=0;
        foreach (mixed item : items)
        {
            if (objectp(item))
            {
                /* For shield-based attacks */
                if (item->check_armour())
                {
                    count++;
                    total+=item->query_ac();
                }
                
                /* For weapon-based attacks */
                if (item->check_weapon())
                {
                    count++;
                    int pen = item->query_pen();
            
                    if (item->query_wt() == W_KNIFE)
                    {
                        /* Treat 20/20 dagger as 40/40, and 40/40 dagger
                         * as 50/50 */
                        pen = (pen > 20 ? 30 + (pen / 2) : pen * 2);
                    }

                    if (item->query_attack_id() == W_BOTH)
                    {
                        /* Two handed weapons recieve a pen bonus */
                        pen = pen * 110 / 100;
                    }
                    total += pen;
                }
                continue;
            }
                
            /* We have a attack_loc, so we'll grab its pen */
            if (intp(item))
            {
                object cob = this_player()->query_combat_object();
                mixed at = cob->query_attack(item);
                
                if (!sizeof(at))
                    continue;
            
                    count++;
                    total+=at[ATT_WCPEN][0];
            }
        }
        
        if (count > 0)
                return total / count;
            else
                return 40;
    }
    return 40;
}

public nomask int calc_base_skill()
{
    // Change made on Nov 19, 2013 by Petros
    // Enforce a maximum of 100 (sup guru) for base skill
    if (intp(query_skills()))
    {
        return min(100, max(15, find_drm(this_player(), ({ query_skills() }))));
    }
    return min(100, max(15, find_drm(this_player(), query_skills())));
}

/*
 * Function Name: calc_weapon_modifier
 * Description  : Hook for last minute modifiers
 *                
 */
public int calc_weapon_modifier(mixed * items)
{
    return 100;
    /*
     * PRE 2008-09-27 - Remove when we won't need it anymore.
     object * shields = filter(this_player()->query_armour(-1), 
     &operator(==)(A_SHIELD) @ &->query_at());
     return 120-20*sizeof(shields);
    */
}


public nomask int calc_hitme_modifier()
{
    switch (query_tohit() / 5)
    {
       case 0: return 96;
       case 1: return 91;
       case 2: return 86;
       case 3: return 82;
       case 4: return 77;
       case 5: return 72;
       case 6: return 67;
       case 7: return 63;
       case 8: return 58;
       case 9: return 52;
       case 10: return 48;
       case 11: return 43;
       case 12: return 38;
       case 13: return 34;
       case 14: return 29;
       case 15: return 25;
       case 16: return 22;
       case 17: return 22;
       case 18: return 18;
       case 19: return 16;
       case 20: return 11;
       case 21: return 10;
       default: return 0;
    }
    return 0;
}

/*
 * Function name: calc_guildstat_modifier_helper
 * Description  : This is the helper function for calc_guild_stat_modifier
 *                It takes in the values and does a standard set of
 *                calculations to determine the modifier for the special.
 * Arguments    : player - the player executing the special
 *                res    - the current damage value to be modified
 * Returns      : nothing
 */
static nomask int
calc_guildstat_modifier_helper(object player, int res,
                               int gstat_type, int gstat_min_pct,
                               int gstat_cap)
{
    int gstat_modifier = 100;
    
    if (gstat_type != 0)
    {
        int player_gstat = player->query_stat(gstat_type);
        if (player_gstat < gstat_cap)
        {
            // We're at less than the cap. so we will modify the result
            // downwards based on the scaling from the minimum percentage
            gstat_modifier = (100 - gstat_min_pct) * player_gstat / gstat_cap;
            gstat_modifier += gstat_min_pct;

            res = res * gstat_modifier / 100;
            
            send_debug_message("debug_damage",
                               "Res after gstat modifier " + gstat_modifier
                             + " applied: " + res + "\n");
        }        
    }
    
    return res;
}

/*
 * Function name: calc_guildstat_modifier
 * Description  : This function by default takes the values that are
 *                set during set_guild_stat_modifier, and calculates
 *                a scaling mechanism for the special. It should
 *                return a value that modifies the input "res" down
 *                if the person does not have sufficient guild stat.
 * Arguments    : player - the player executing the special
 *                res    - the current damage value to be modified
 * Returns      : nothing
 */
static int
calc_guildstat_modifier(object player, int res)
{
    // Now we modify based on guild stat if it has been set
    int gstat_type = query_guild_stat_type(player);
    int gstat_min_pct = query_guild_stat_minimum_percentage(player);
    int gstat_cap = query_guild_stat_cap(player);
    
    return calc_guildstat_modifier_helper(player, res, gstat_type,
                                          gstat_min_pct, gstat_cap);
}

public nomask int
calculate_damage(object player, object target, mixed * items, 
                 int resist, int result)
{
    int base_pen = calc_base_pen(items);
    int stat_modifier = calc_stat_modifier();
    int base_skill = calc_base_skill();
    
    int modifier = calc_weapon_modifier(items);
    send_debug_message("debug_damage", 
                           "Wep modifier " + modifier+ ", "
                         + "Stat mod " + stat_modifier + ", "
                         + "base skill " + base_skill + ", "
                         + "base pen " + base_pen + "\n");


    int res = F_PENMOD(base_pen, base_skill);
    
    res=res * F_STR_FACTOR(stat_modifier) / 100;
    
    res = (res * query_combat_aid()) / 100;

    send_debug_message("debug_damage", 
                           "Res after CAID applied: "+res+"\n");
    
    // Normally, an ability is modified by the ability time in order
    // to modify the ability damage. However, there are some abilities
    // which need to be done immediately. In this case, an ability
    // time of 0 cannot modify the damage result
    if (query_ability_time())
    {        
        res = (res * query_ability_time()) / 5;
    }
    
    send_debug_message("debug_damage", 
                           "Res after speed applied: "+res+"\n");

    res=res * 100 / (100 - calc_hitme_modifier());

    send_debug_message("debug_damage", 
                           "Res after hitme applied: "+res+"\n");
    
    res = res * (100 - resist) / 100;
    
    send_debug_message("debug_damage",
                           "Res after resistance applied: " + res + "\n");
                           
    if (!player->query_npc())
    {
        // NPCs don't generally have guild stat, so we don't limit
        // their abilities by guildstat.        
        int gstat_result = calc_guildstat_modifier(player, res);
        if (gstat_result < res)
        {
            // We put this if-condition check here so that GM's don't
            // try and use this function to increase the aid without
            // using the correct functions.
            res = gstat_result;
        }
    }
    
    // Weapon modifier is a last-minute modifier.
    res=res * modifier / 100;
    send_debug_message("debug_damage",
                           "Res after weapon modifier applied: " + res + "\n");

    send_debug_message("debug_damage", 
                           "Final result: "+res+"\n");
    
    return res;
}

/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason.
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int force_fail(object player,mixed * items,object target, int 
                        resist,int result)
{
    return 0;
}

/*
 * Function name: query_hitloc_factor
 * Description:   This function applies the penalty for targeting a 
 *                specific hitloc.
 * Returns:       Percentage of damage for targeted attacks
 */
public int query_hitloc_factor()
{
    return 85;
}

public int
select_random_hitloc(object target)
{
    int * hitloc_ids;
    object cobj;
    int j, tmp;
    
    if (!objectp(target))
    {
        return -1;
    }
    
    cobj = target->query_combat_object();
    tmp = random(100);
    hitloc_ids = cobj->query_hitloc_id();
    j = 0;

    foreach (int hloc : hitloc_ids)
    {    
        j += (cobj->query_hitloc(hloc))[1];
        if (j >= tmp)
        {
            return hloc;
        }
    }
    
    // should never get here unless the hitloc pct
    // don't add up to 100.
    return one_of_list(hitloc_ids);
}

/*
 * Function:    resolve_combat_special
 * Description: This gets called for each target that the player's special
 *              is hitting. It provides all the information needed in order
 *              to determine whether it will actually hit, and what should
 *              happen when it does.
 */
public void
resolve_combat_special(object player, object target, int hitloc,
                       int random_hitloc, int pen, int damage_type,
                       mixed * items, int result)
{
    // Process the actual effects of the special here
}

/*
 * Function name: resolve_ability
 * Description:   This function is responsible for performing the routines
 *                necessary to produce the special effect(s).  All specials that
 *                manifest any effect whatsoever need to redefine this and
 *                implement those.
 *                NB: _live_i_attack_delay is treated as a partial stun, 
 *                and does not block these specials
 *
 * Arguments:     1. (object)   The player
 *                2. (object *) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 */
public nomask void
resolve_ability(object player, mixed * items, mixed * targets, int * 
                resist, mixed * result)
{
    mixed *hitresult;

    mixed fail;
        
    /* First do some check if we actually attack. */
    if (pointerp(fail = player->query_prop(LIVE_AS_ATTACK_FUMBLE)) &&
        sizeof(fail))
    {
        if (query_interactive(player))
        {
            player->catch_msg(fail[0]);
        }
    }
    else
    {
        for (int i=0;i<sizeof(targets);i++)
        {
    
            int hitloc = -1;
            int random_hitloc = -1;
            mixed target=targets[i];
        
            int hitloc_factor=100;
        
            object ob;

            if (objectp(target))
            {
                ob = target;
            } else
            if (pointerp(target))
            {
                ob = target[0];
                hitloc = target[1];
                hitloc_factor = query_hitloc_factor();
                random_hitloc = select_random_hitloc(ob);
            }
            if (!objectp(ob))
                continue;

            if (ob->query_not_attack_me(player,-1))
            {
                continue;
            }

            int pen=0;
            if (result[i]<=0)
            {
                pen=result[i];
            }
            else
            {
                pen=calculate_damage(player,ob,items,resist[i],result[i]);
                pen=pen*hitloc_factor/100;
            }

            if (force_fail(player, items, ob, resist[i], result[i]))
            {
                continue;
            }

            int damage_type = query_dt(items);

            resolve_combat_special(player, ob, hitloc, random_hitloc, pen, damage_type, items, result[i]);
        }
    }

    // Apply any costs to player, such as fatigue
    apply_costs_to_player(player);
}

public void
restart_npc_special(object player, string arg)
{    
    if (query_ability_time() > 0)
    {
        set_alarm(0.1,0.0,&do_ability(arg));
    }
}



/*
 * Function name: query_success
 * Description:   Determine if a special is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
                  indicating % success, possibly > 100)
 */
static nomask int
query_success(object player, mixed target, mixed *items)
{
    object ob;
    object combat_obj;
    int result;
    
    if (pointerp(target))
    {
        ob = target[0];
    }
    
    if (objectp(target))
    {
        ob = target;
    }
    if (!objectp(ob))
    {
        return 0;
    }
    
    combat_obj = player->query_combat_object();
    result = combat_obj->cb_tohit(-1, query_tohit(), ob);
    
    send_debug_message("debug_tohit", 
                           "Result " + result +  "\n");
    return result;
}



/* 
 * Target verification functions 
 */

public int
filter_present(mixed ob, object actor)
{
    object env;

    object target;
    
    if (pointerp(ob))
    {
        target=ob[0];
    }
    
    if (objectp(ob))
    {
        target=ob;
    }

    if (!objectp(target) || !objectp(actor))
        return 0;

    env = environment(target);
    return ((env == actor) || (env == environment(actor)));
}

/*
 * Function name: verify_present_or_enemy
 * Description:   Verification function to check whether the objects
 *                in the target list are still present or not.
 * Returns:       A filtering of the target list of those that
 *                are not present.
 */    
public mixed *
verify_present_or_enemy(object actor, mixed *targets, string arg)
{
    if (!objectp(actor))
    {
        return 0;
    }
        
    mixed * results=({ });
    int ob_gone=0;
    foreach(mixed target : targets)
    {
        object ob;
    
        if (pointerp(target))
        {
            ob=target[0];
        }
    
        if (objectp(target))
        {
            ob=target;
        }

        if (!objectp(ob))
        {
            ob_gone=1;
            continue;
        }
    
        if (ob->query_prop(OBJ_M_NO_ATTACK))
        {
            ob_gone=1;
            continue;
        }
    
        object env = environment(ob);
        if (env==actor || env==environment(actor))
        {
            results+= ({ target });
        }
    }
    if (!sizeof(results) && ob_gone && 
        filter_present(actor->query_attack(),actor))
    {
        hook_autochanged_target(actor->query_attack());
        return ({ actor->query_attack() });
    }
    return results;
}

/*
 * Function name: get_new_hitloc
 * Description:   When switching targets, we need to change the
 *                hit locations if it is a targeted attack.
 * Returns:       The new hit location for the target.
 */    
public int 
get_new_hitloc(object oldtarget, object newtarget, int hitloc)
{
    object old_cb, new_cb;
    mixed hresult;
    string location;
    
    if (!objectp(oldtarget) || !objectp(newtarget))
    {
        return -1;
    }
    
    old_cb = oldtarget->query_combat_object();
    new_cb = newtarget->query_combat_object();
    
    hresult = old_cb->query_hitloc(hitloc);
    if (!pointerp(hresult))
    {
        return -1;
    }
    location = hresult[2]; // the old hit location

    // Now look for it in the new target
    int * hitloc_ids = new_cb->query_hitloc_id();
    string * hitloc_descs = map(hitloc_ids, 
        &operator([])(, HIT_DESC) @ &new_cb->query_hitloc());
	int pos = member_array(location, hitloc_descs);
        
    if (pos < 0)
    {
        return -1;
    }

    return hitloc_ids[pos];   
}

/*
 * Function name: verify_change_enemy
 * Description:   This is a verification function to ensure that
 *                the special always hits the person whom is
 *                currently being attacked.
 * Returns:       The new target list
 */    
public mixed *
verify_change_enemy(object actor, mixed * targets, string arg)
{
    if (!objectp(actor))
    {
        return 0;
    }
        
    mixed * results = ({ });

    if (sizeof(targets) != 1)
    {
        return verify_present_or_enemy(actor, targets, arg);
    }
    
    if (!query_ability_attack_during_prep()
        && !objectp(actor->query_attack()))
    {
        // If we're not currently attacking anyone, and the
        // ability doesn't attack during prep, just do normal
        // verification.
        return verify_present_or_enemy(actor, targets, arg);
    }
    
    // August 29, 2008 - Balance team agreed to change Genesis
    //                   combat specials so that they will target
    //                   the currently attacked enemy, rather
    //                   than the originally targeted living

    mixed oldtarget = targets[0];
    object enemy = actor->query_attack();
    if (pointerp(oldtarget))
    {
        if (oldtarget[0] == enemy)
        {
            results = targets;
        }
        else
        {
            // Hit Locations are different by living, so
            // we will query for the same hit location as
            // the old one
            int old_hitloc = oldtarget[1];        
            int new_hitloc = get_new_hitloc(oldtarget[0], enemy, 
                                            old_hitloc);
            results = ({ ({ enemy, new_hitloc }) });
        }
    }
    else
    {
        // target is just an object or 0. If 0, that means that the old
        // target has died or has been destroyed. In this case, we will
        // still retarget the new enemy. September 23, 2008 - Petros
        results = ({ enemy });
    }
    
    return verify_present_or_enemy(actor, results, arg);
}

public void
hook_concentration_fail(object ability)
{
    write("You are too busy casting a spell.\n");
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
    if (actor->query_prop(LIVE_I_CONCENTRATE))
    {
        hook_concentration_fail(this_object());
        return 0;
    }
    return 1;
}

/*
 * Function name: query_best_wielded_weapon
 * Description  : Compares the wielded weapons according to the appraise and
 *                weapon skill of the wielder. Returns the better of the
 *                weapons (if there is one wielded). Compare code taken from
 *                /cmd/live/state.c in the compare_weapon method
 * Arguments    : object player - person wielding the weapons
 */
public object
query_best_wielded_weapon(object player)
{
    object * weapons;
    object weapon1, weapon2;
    int stat1, stat2, skill, seed;
        
    weapons = player->query_weapon(-1);
    if (!sizeof(weapons))
    {
        return 0;
    }
    else if (sizeof(weapons) == 1)
    {
        return weapons[0];
    }
    
    // Have more than one weapon.
    if (OB_NUM(weapons[0]) > OB_NUM(weapons[1]))
    {
        weapon1 = weapons[1];
        weapon2 = weapons[0];
    }
    else
    {        
        weapon1 = weapons[0];
        weapon2 = weapons[1];
    }
    
    skill = (2000 / (1 + player->query_skill(SS_APPR_OBJ) +
        player->query_skill(SS_WEP_FIRST + weapon1->query_wt())));
    seed = atoi(OB_NUM(weapon1)) + atoi(OB_NUM(weapon2));

    /* Compare the penetration values. */
    stat1 = weapon1->query_pen() + random(skill, seed);
    stat2 = weapon2->query_pen() + random(skill, seed + 27);
    send_debug_message("damage_compare", weapon1->short() + " stat1: " + stat1 + " " + weapon2->short() + " stat2: " + stat2 + " skill: " + skill + " seed: " + seed);

    if (stat1 > stat2)
    {
        return weapon1;
    }
    
    return weapon2;    
}
