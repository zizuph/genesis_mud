/*
 * Implementation of a general damage special.  
 *
 * Inherit this and reconfigure it for your particular special.
 * 
 * Example:
 * 
 * inherit ABILITY_DIR+"damage";
 * 
 * #include <ss_types.h>
 * #include <wa_types.h>
 * #include <tasks.h> 
 *
 * public varargs int
 * config_ability()
 * {  
 *     ::config_ability();
 * 
 *     set_special_time(25);
 *     set_tohit(65);
 *     set_combat_aid(80);
 *     set_dt(SLASH_DT);
 *     set_skills(({ SKILL_AVG, SS_SWORD, SS_MYSPECIAL, SKILL_END }) );
 *     set_stats(({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END }) );
 *
 *     return 0;
 * }
 * public varargs void special_did_hit(int aid, string hdesc, int hid, 
 *               int phurt, object enemy, int dt,int phit, int dam,
 *               mixed * items, int result)
 *
 * {
 *    switch(phurt)
 *      case 1..4: 
 * }
 *
 * static mixed * check_required_items(object actor,mixed * targets,
 *                   string arg,int pretest)
 * {
 *    object * weapons=this_player()->query_tool(-1) -
 *             this_player()->query_armour(-1);
 *     
 *    foreach (object weapon : weapons)
 *    {
 *       if (weapon->query_wt()==WT_SWORD)
 *       {
 *            //Found our required weapon - this will be used in our
 *            //damage calculation.  If I wanted to use a certain
 *            //attack_id, I could specify that.
 *            return ({ weapon });
 *       }
 *    }
 *    return 0;  //Needed a wielded sword
 *
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

public object * verify_present_or_enemy(object actor, 
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
    set_ability_target_verify(verify_present_or_enemy);
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
                //For shield-based attacks
                if (item->check_armour())
                {
                    count++;
                    total+=item->query_ac();
                }
                //For weapon-based attacks
                if (item->check_weapon())
                {
                    count++;
                    int pen=item->query_pen();
                    if (item->query_wt==W_KNIFE)
                    {
                        //Treat 20/20 dagger as 40/40, and 40/40 dagger
                        //as 50/50
                        pen=(pen > 20 ? 30 + (pen / 2) : pen * 2);
                    }
                    total+=pen;
                }
                continue;
            }
            //We have a attack_loc, so we'll grab its pen
            if (intp(item))
            {
                object cob=this_player()->query_combat_object();
                mixed at=cob->query_attack(item);
                if (!sizeof(at))
                {
                    //Could not find
                    continue;
                }
                count++;
                total+=at[ATT_WCPEN][0];
            }
        }
        if (count>0)
        {
            return total/count;
        }
        else
        {
            return 40;
        }
    }
    return 40;
}

public nomask int calc_base_skill()
{
    if (intp(query_skills()))
    {
        return max(15,find_drm(this_player(), ({ query_skills() })));
    }
    return max(15,find_drm(this_player(), query_skills()));
}

public int calc_weapon_modifier(mixed * items)
{
    object * shields = filter(this_player()->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at());
    return 120-20*sizeof(shields);
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
    
    res=res * modifier / 100;

    send_debug_message("debug_damage", 
                           "Final result: "+res+"\n");
    
    return res;
}


/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam, mixed * items, int result)
{
    //Messages for the hit here
}

public void hook_special_complete()
{
    write("You feel ready to "+short()+" again.\n");
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
    //85 based on 15% reduction due to:
    //40 AC shield avoided 50% more often
    //50% of NPCs have completely equal AC
    //net gain, 10 AC avoided on avg
    //converted 10 AC to 15% evade
    return 85;
}

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_resolve_ability(int pen, int dt, int damage)
{
    send_debug_message("resolve_ability", 
                    "Pen of " + pen + ", "
                    + "DT of " + dt + ", "
                    + "Damage of " + damage + "\n");        
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
    
            int hitloc=-1;
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
                hitloc_factor=query_hitloc_factor();
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
            hitresult=ob->hit_me(pen, damage_type, player, -1, hitloc);
            report_resolve_ability(pen, query_dt(items), hitresult[3]);
    
            special_did_hit(-1, hitresult[1], hitresult[4], 
                hitresult[0], ob, damage_type, hitresult[2], 
                hitresult[3], items, result[i]);
        }
    }

    // Apply any costs to player, such as fatigue
    apply_costs_to_player(player);
    hook_special_complete();
    if (player->query_npc() && query_ability_time()>0)
    {
        set_alarm(0.1,0.0,&do_ability(""));
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
query_success(object player, mixed target)
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
    
public object *
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
