#pragma strict_types
/*
 * /d/Genesis/specials/new/combat_ability.c
 *
 * Code shared for combat abilities shared between spell and non-spell versions.
 *
 * 2022-02-27 - if an ability_hit function is specified, use it.  Don't fall back
 *              to a cb_tohit call if the result is 0.
 * 
*/
#include "defs.h"
inherit TIMED_ABILITY_LIB;
inherit TASK_MODIFIERS_LIB;
inherit TARGETTING_LIB;
inherit GUILD_MODIFIERS_LIB;
inherit "/d/Genesis/specials/calculations";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <tasks.h>
#include <math.h>

#include "/std/combat/combat.h"
#include "../debugger/debugger_tell.h"

// Prototypes
public int query_ability_damage_type(object *items);
public nomask int query_ability_combat_aid();
public mixed * verify_present_or_enemy(object actor, mixed *targets, string arg);
public mixed * verify_change_enemy(object actor, mixed *targets, string arg);
public void set_ability_armour_penetration(function ap);
public function query_ability_armour_penetration();

// Global Variables
static int      Ability_hit,
                Ability_damage_type,
                Ability_combat_aid = 0;

static mixed    Ability_skills,
                Ability_stats;

static function Ability_hit_function,
                Ability_apply_resistance_function,
                Ability_armour_pen;

public void
hook_ability_penetration_modification(object actor, mixed *items, mixed
    *target, int *pen, int *hitloc, int *resist, int *result, int *pdiff)
{
    int     differ = 0;
    string  desc = "lower";
    
    for (int i = 0; i < sizeof(target); i++)
    {
        if (pen[i] > 0)
            differ += pdiff[i];
    }
    differ /= sizeof(target);
    
    if (differ <= 0)
        return;
    
    if (differ > 100)
    {
        differ -= 100;
        desc = "greater";
    } else
        differ = 100 - differ;
    
    switch(differ)
    {
        case 1..25:
        desc = "slightly " + desc;
            break;
        case 26..50:
            break;
        case 51..100:
        desc = "much " + desc;
            break;
    }
    
    // Turned off this messaging - players expected it on every effect
    // and it does not work well with natural resistance from AC.
    /*
    if (random(100) < differ)
        actor->catch_msg("The effect was " + desc + " than you had "
        + "anticipated.\n");
    */
}

/************************************************************************
 *                       Ability Skill Functions                        *
 ************************************************************************/

/*
 * Function name:   set_ability_skills
 * Description:     
 * Arguments:       (mixed) 
 * Returns:         Nothing
 */
public void
set_ability_skills(mixed skills)
{
   Ability_skills = skills;   
} /* set_ability_skills */

/*
 * Function name:   query_ability_skills
 * Description:     
 * Arguments:       None
 * Returns:         (mixed) 
 */
public mixed
query_ability_skills()
{
    return Ability_skills;
} /* query_ability_skills */

/*
 * Function name:   query_ability_base_skill
 * Description:     Returns the skill value for the special, calculating the
 *                  set skills and potentially item skills.
 * Arguments:       (object) actor 
 *                  (mixed *) items - The items used with the ability
 * Returns:         (int) The ability skill value
 */
public nomask int
query_ability_base_skill(object actor, object * items)
{
    if (sizeof(items))
    {
        // Should we add the skills of used items?
    }
    
    // Why penalize this?
    if (!query_ability_skills())
        return 100;
    
    if (intp(query_ability_skills()))
    {
        return min(100, max(15, find_drm(actor, ({ query_ability_skills() }))));
    }
    
    return min(100, max(15, find_drm(actor, query_ability_skills())));
} /* query_ability_base_skill */

/************************************************************************
 *                       Ability Stats Functions                        *
 ************************************************************************/

/*
 * Function name:   set_ability_stats
 * Description:     
 * Arguments:       None
 * Returns:         (mixed) 
 */
public void
set_ability_stats(mixed stats)
{
   Ability_stats = stats;   
} /* set_ability_stats */

/*
 * Function name:   query_ability_stats
 * Description:     
 * Arguments:       None
 * Returns:         (mixed) 
 */
public mixed
query_ability_stats()
{
    return Ability_stats;
} /* query_ability_stats */

/*
 * Function name:   query_ability_stat_modifier
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 0
 */
public nomask int
query_ability_stat_modifier(object actor)
{
    mixed   tasks = query_ability_stats();
    int     cap = 0;
    
    for (int stat = 0; stat < SS_NO_EXP_STATS; stat++)
    {
        if (cap < actor->query_stat(stat))
            cap = actor->query_stat(stat);
    }
    
    if (intp(tasks))
        tasks = ({ tasks });
    
    return min(cap, find_drm(actor, tasks));
} /* query_ability_stat_modifier */

/*
 * Function name:   convert_unarmed_combat_stat
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 
 */
public nomask int
convert_unarmed_combat_stat(int stat, object actor)
{
    object *shields;
    int     value;
    
    shields = filter(this_player()->query_armour(-1), 
              &operator(==)(A_SHIELD) @ &->query_at());
    // Starting at 48 at 100 stat if no shield is worn.
    value = 8 * F_STR_FACTOR(actor->query_stat(stat)) / 100;
    value += 40;
    
    switch(sizeof(shields))
    {
        case 1:
        value = value * 50 / 60; // 50 is the 1-handed limit
            break;
        case 2:
        value = value * 35 / 60; // 35 is the non-magical limit
            break;
    }
    
    // To protect against wizard shenanigans
    if (query_ability_dual_wield() && sizeof(actor->query_weapon(-1)) > 1)
        value = value * 50 / 60;
    
    return value;
} /* convert_unarmed_combat_stat */

/*
 * Function name:   convert_stats_to_pen
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 
 */
static int
convert_stats_to_pen(object actor)
{
    return convert_unarmed_combat_stat(SS_STR, actor);
} /* convert_stats_to_pen */

/*
 * Function name:   convert_stats_to_hit
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 
 */
static int
convert_stats_to_hit(object actor)
{
    return convert_unarmed_combat_stat(SS_DEX, actor);
} /* convert_stats_to_hit */

/************************************************************************
 *                     Ability Targeting Functions                      *
 ************************************************************************/

/*
 * Function name:   select_random_hitloc
 * Description:     
 * Arguments:       (object) target 
 * Returns:         (int) 
 */
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
} /* select_random_hitloc */

/*
 * Function name:   get_new_hitloc
 * Description:     When switching targets, we need to change the hit locations
 *                  if it is a targeted attack.
 * Arguments:       1. (object) oldtarget
 *                  2. (object) newtarget
 *                  3. (int) hitloc
 * Returns:         (int) The new hit location for the target.
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
} /* get_new_hitloc */



/*
 * Function name:   verify_present_or_enemy
 * Description:     Verification function to check whether the objects in the
 *                  target list are still present or not.
 *                  1. (object) actor
 *                  2. (mixed *) targets
 *                  3. (string) arg
 * Returns:         (mixed *) A filtering of the target list of those that
 *                  are not present.
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
} /* verify_present_or_enemy */

/*
 * Function name:   verify_change_enemy
 * Description:     This is a verification function to ensure that the special
 *                  always hits the person whom is currently being attacked.
 * Arguments:       1. (object) actor
 *                  2. (mixed *) targets
 *                  3. (string) arg
 * Returns:         (mixed *) The new target list
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
} /* verify_change_enemy */
/************************************************************************
 *                         Ability Hit Functions                        *
 ************************************************************************/

/*
 * Function name:   query_ability_hit
 * Description:     Returns the set ability to-hit value.
 * Arguments:       (object) actor
 *                  (mixed) target
 *                  (object *) items
 * Returns:         (int) ability hit value
 */
public varargs int
query_ability_hit(object actor, mixed target, object * items)
{
    return Ability_hit;
} /* query_ability_hit */

/*
 * Function name:   set_ability_hit
 * Description:     Sets the ability to-hit value.
 * Arguments:       (int) ability hit value
 * Returns:         Nothing
 */
public void
set_ability_hit(int hit)
{
    Ability_hit = hit;
} /* set_ability_hit */
 
 
/*
 * Function name:   query_ability_hit_function
 * Description:     Queries which function to be used instead of cb_tohit.
 * Returns:         The ability hit function to be used for the spell.
 */
public function
query_ability_hit_function()
{
    return Ability_hit_function;
}
 
/*
 * Function name:   set_ability_hit_function
 * Description:     Sets which function to use instead of cb_tohit (primarily
 *                  used for spellcasting).
 * Arguments:       None
 * Returns:         (int) ability hit value
 */
public void
set_ability_hit_function(function func)
{
    Ability_hit_function = func;
} /* set_ability_hit_function */
 
 
/*
 * Function name:   query_ability_apply_resistance_function
 * Description:     Queries which function to be used instead of F_NEW_DAMAGE.
 * Returns:         The ability hit function to be used for the spell.
 */
public function
query_ability_apply_resistance_function()
{
    return Ability_apply_resistance_function;
}
 
/*
 * Function name:   set_ability_apply_resistance_function
 * Description:     Sets which function to use instead of F_NEW_DAMAGE
 *                  (primarily used for spellcasting).
 * Arguments:       None
 * Returns:         (int) ability hit value
 */
public void
set_ability_apply_resistance_function(function func)
{
    Ability_apply_resistance_function = func;
} /* set_ability_hit_function */
 
 
 
/*
 * Function name:   query_success
 * Description:     Determine if the ability is successfully used.
 * Arguments:       1. (object) actor
 *                  2. (mixed) target
 *                  3. (mixed *) items
 * Returns:         (int) the success rate from cb_tohit
 */
static nomask int
query_success(object actor, mixed target, mixed *items)
{
    if (pointerp(target))
        target = target[0];
    
    if (!objectp(target) || !objectp(actor))
        return 0;
    
    int result;
    
    if (functionp(Ability_hit_function))
        return applyv(Ability_hit_function, ({ actor, target, items }));
        
    if (!result)
    {
        object combat_obj = actor->query_combat_object();
        int value = query_ability_hit(actor, target, items);
        result = combat_obj->cb_tohit(-1, value, target);
    }
    
    return result;
} /* query_success */

/*
 * Function name:   query_ability_hit_chance
 * Description:     Returns the hit percentage from specified hit value, or
 *                  the ability hit value.
 * Arguments:       (varargs int) hit - The hit value to convert
 * Returns:         (int) The hit value converted to percentage
 */
public varargs int
query_ability_hit_chance(int hit, object actor, mixed target, object *items)
{
    if (!hit)
        hit = query_ability_hit(actor, target, items);

    return 100 - convert_tohit_to_combat_aid_reduction(hit);

} /* query_ability_hit_chance */

/************************************************************************
 *                       Ability Power Functions                        *
 ************************************************************************/

/*
 * Function name:   query_ability_base_hit
 * Description:     A function used to determine the hit value of the ability
 * Arguments:       (object) actor 
 *                  (mixed *) items - The items on which we determine hit
 * Returns:         (int) The modified or unmodified hit value
 */
public int
query_ability_base_hit(object actor, mixed *items)
{
    if (query_ability_damage_type(items) == MAGIC_DT)
    {
        // No armour penetration function, use default value.
        if (!functionp(query_ability_armour_penetration()) &&
            !functionp(query_ability_resist()))
            return 40;
    }
    
    if (sizeof(items))
    {
        int count=0;
        int total=0;
        
        foreach (mixed item : items)
        {
            if (objectp(item))
            {
                // For shield-based attacks
                if (item->check_armour())
                {
                    // Reduced until a proper calculation has been developed
                    count++;
                    total+= item->query_ac() * 45 / 55;
                }
                
                // For weapon-based attacks
                if (item->check_weapon())
                {
                    count++;
                    int hit = item->query_hit();
                    
                    if (item->query_wt() == W_KNIFE)
                    {
                        /* OLD SYSTEM:
                         * Treat 20/20 dagger as 40/40, and 40/40 dagger as 50/50
                         * hit = (hit > 20 ? 30 + (hit / 2) : hit * 2);
                         */
                         hit = (hit > 10 ? 10 + hit : hit * 2);
                    }

                    total += hit;
                }
                continue;
            }
            
            // We have an attack_loc, so we'll grab its hit
            if (intp(item))
            {
                object cob = actor->query_query_object();
                mixed at = cob->query_attack(item);
                
                if (!sizeof(at))
                    continue;
            
                count++;
                total += at[ATT_WCHIT];
            }
        }
        
        if (count > 0)
            return total / count;
    }
    
    return convert_stats_to_hit(actor);
} /* query_ability_base_hit */

/*
 * Function name:   query_ability_base_pen
 * Description:     A function used to determine the pen value of the ability
 * Arguments:       (object) actor 
 *                  (mixed *) items - The items on which we determine hit
 * Returns:         (int) The modified or unmodified hit value
 */
public nomask int
query_ability_base_pen(object actor, mixed *items)
{
    int damage_type = query_ability_damage_type(items);

    if (damage_type == MAGIC_DT)
    {
        // No armour penetration function, use default stats value.
        if (!functionp(query_ability_armour_penetration()) &&
            !functionp(query_ability_resist()))
            return 40;
        
        // Since we cant have MAGIC_DT as a type here, we default it to W_IMPALE
        damage_type = W_IMPALE;
    }
     
    if (sizeof(items))
    {
        int count=0;
        int total=0;
        foreach (mixed item : items)
        {
            if (objectp(item))
            {
                // For shield-based attacks
                if (item->check_armour())
                {
                    // Reduced until a proper calculation has been developed
                    count++;
                    total+= item->query_ac() * 45 / 55;
                }
                
                // For weapon-based attacks
                if (item->check_weapon())
                {
                    count++;
                    int pen = (item->query_modified_pen())[QUICK_FIND_EXP(damage_type)];
                    send_debug_message("debug_damage_modified", "Modified pen: "
                    + pen + " for " + damage_type + " " + file_name(item));
            
                    if (item->query_wt() == W_KNIFE)
                    {
                        /* OLD SYSTEM:
                         * Treat 20/20 dagger as 40/40, and 40/40 dagger as 50/50
                         * pen = (pen > 20 ? 30 + (pen / 2) : pen * 2);
                         */
                         pen = (pen > 10 ? 10 + pen : pen * 2);
                    }

                    total += pen;
                }
                continue;
            }
                
            // We have a attack_loc, so we'll grab its pen
            if (intp(item))
            {
                object cob = actor->query_query_object();
                mixed at = cob->query_attack(item);
                
                if (!sizeof(at))
                    continue;
            
                count++;
                total += at[ATT_WCPEN][QUICK_FIND_EXP(damage_type)];
            }
        }
        
        if (count > 0)
            return total / count;
    }
    
    return convert_stats_to_pen(actor);
} /* query_ability_base_pen */

/*
 * Function name:   query_ability_item_modifier
 * Description:     
 * Arguments:       1. (object) actor
 *                  2. (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public int
query_ability_item_modifier(object actor, mixed *items)
{
    return 100;
} /* query_ability_item_modifier */


/*
 * Function name:   query_ability_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid
 *                  that applies to the current situation
 * Arguments:       (object) actor - player executing special
 * Returns:         (int) number between 1 and 100
 */
public int
query_ability_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return 100;
} /* query_ability_combat_aid_modifier */

/*
 * Function name:   query_ability_hitloc_factor
 * Description:     This function applies the penalty for targeting a specific
 *                  hitloc.
 * Arguments:       None
 * Returns:         (int) Percentage of damage for targeted attacks
 */
public int
query_ability_hitloc_factor()
{
    return 85;
} /* query_hitloc_factor */

/*
 * Function name:   query_ability_power
 * Description:     
 * Arguments:       (object) actor
 *                  (object) target
 *                  (mixed *) items - The items used with the ability
 * Returns:         (int) 
 */
public nomask varargs int
query_ability_power(object actor, object target, mixed *items = ({}))
{
    int base_pen = query_ability_base_pen(actor, items);
    int base_hit = query_ability_base_hit(actor, items);
    int base_skill = query_ability_base_skill(actor, items);
    int stat_modifier = query_ability_stat_modifier(actor);
    int item_modifier = query_ability_item_modifier(actor, items);
    
    send_debug_message("debug_new_system",actor->query_real_name()
    + variable2string(({base_hit, base_skill, stat_modifier, item_modifier})));
    
    // Get the base penetration value
    int power = F_PENMOD(base_pen, base_skill);
    send_debug_message("debug_new_system",actor->query_real_name() + "Power: "
    + power + ", pen: " + base_pen);
    // Modify by stats
    power = power * F_STR_FACTOR(stat_modifier) / 100;
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after stats: " + power);
    // Scale depending on ability combat aid
    if (query_ability_combat_aid())
        power = power * query_ability_combat_aid() / 100;
    
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after combat aid: " + power + " combat aid: " + query_ability_combat_aid());
    // Scale the ability based on the ability time
    if (query_ability_time())
        power = (power * query_ability_time()) / 5;

    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after time: " + power + " time: " + query_ability_time());
    
    // Scale based on ability hit chance
    power = power * 100 / query_ability_hit_chance(0, actor, target, items);
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after hit chance: " + power + " chance: "
    + query_ability_hit_chance(0, actor, target, items));
    // Scale penetration based on weapon hit chance
    power *= query_ability_hit_chance(base_hit);
    power /= query_ability_hit_chance(40);
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after wep hit: " + power + ", base: " + base_hit);
    
    if (!actor->query_npc())
    {
        // NPCs don't generally have guild stat, so we don't limit
        // their abilities by guildstat.
        int gstat_result = query_guildstat_modifier(actor, power);
        if (gstat_result < power)
        {
            // We put this if-condition check here so that GM's don't
            // try and use this function to increase the aid without
            // using the correct functions.
            power = gstat_result;
        }
    }
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after gxp: " + power);

    power = power * item_modifier / 100;
    send_debug_message("debug_new_system",actor->query_real_name() + "Power "
    + "after item mod: " + power + ", mod: " + item_modifier);

    return power;
} /* query_ability_power */

/************************************************************************
 *                      Ability Resource Functions                      *
 ************************************************************************/

/*
 * Function name:   apply_costs_to_player
 * Description:     By default, a small fatigue cost is applied for the 
 *                  special. Other costs can be applied as well by a masked
 *                  function.
 * Arguments:       (object) actor - player executing the special
 * Returns:         Nothing
 */
public void
apply_costs_to_player(object actor)
{
    actor->add_fatigue(-2);
} /* apply_cost_to_player */

/************************************************************************
 *                      Ability Construct Functions                     *
 ************************************************************************/

/*
 * Function name:   set_ability_armour_penetration
 * Description:     The armour penetration function is used to handle the pen
 *                  modulation when the special is set to MAGIC_DT.
 * Arg Vectors:     ({ pen, damage_type, player, ob, hitloc, items })
 *                  (int) pen - the penetration value
 *                  (int) damage_type - the special damage type
 *                  (object) player - the player executing the special
 *                  (object) ob - the target of the special
 *                  (int) hitloc - the special hitloc
 *                  (mixed *) items - the items used by the special
 * Arguments:       (function) ap - The armour penetration function
 * Returns:         Nothing
 */
public void
set_ability_armour_penetration(function ap)
{
    Ability_armour_pen = ap;
} /* set_ability_armour_penetration */

/*
 * Function name:   query_ability_armour_penetration
 * Description:     Returns the armour penetration function used to mask the pen
 *                  modulation from armour.
 * Arguments:       None
 * Returns:         (function) Ability_armour_pen
 */
public function
query_ability_armour_penetration()
{
    return Ability_armour_pen;
} /* query_ability_armour_penetration */

/*
 * Function name:   set_ability_damage_type
 * Description:     Sets the damage type of the ability
 * Arguments:       (int) type - the damage type
 * Returns:         Nothing
 */
public void
set_ability_damage_type(int type)
{
    Ability_damage_type = type;
} /* set_ability_damage_type */

/*
 * Function name:   query_ability_damage_type
 * Description:     Checks the weapons and returns the weapon type
 * Arguments:       (object *) items - array of required items. 
 * Returns:         (int) the damage type
 */
public int 
query_ability_damage_type(object *items)
{
    return Ability_damage_type;
} /* query_ability_damage_type */

/*
 * Function name:   set_ability_combat_aid
 * Description:     
 * Arguments:       (int) aid -
 * Returns:         Nothing
 */
public void
set_ability_combat_aid(int aid)
{
    Ability_combat_aid = aid;
} /* set_ability_combat_aid */

/*
 * Function name:   query_ability_combat_aid
 * Description:     
 * Arguments:       None
 * Returns:         (int) 
 */
public nomask int
query_ability_combat_aid()
{
    int modifier;
    
    // The combat aid can change by situation. Query for
    // the modifier to change the combat aid for the
    // current situation.
    modifier = min(100, max(1, query_ability_combat_aid_modifier()));
    return (Ability_combat_aid * modifier) / 100;
} /* query_ability_combat_aid */

/*
 * Function name:   force_fail
 * Description:     This function allows the special to force a failure for
 *                  whatever reason.
 * Arguments:       1. (object)   The player
 *                  2. (object)   The targets
 *                  3. (int *)    Resistance values corresponding to each target
 *                  4. (int)      The attempt result as returned by
 *                                query_casting_success()
 * Returns:         (int) 1 for failure, 0 for not.
 */
public int 
force_fail(object actor, mixed *items, object target, int resist, int result)
{
    return 0;
} /* force_fail */

/*
 * Function name:   resolve_combat_special
 * Description:     This gets called for each target that the player's special
 *                  is hitting. It provides all the information needed in order
 *                  to determine whether it will actually hit, and what should
 *                  happen when it does.
 */
public void
resolve_combat_special(object actor, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    // Process the actual effects of the special here
} /* resolve_combat_special */

/*
 * Function name:   resolve_compound_combat_special
 * Description:     This gets called for each target that the player's special
 *                  is hitting. It provides all the information needed in order
 *                  to determine whether it will actually hit, and what should
 *                  happen when it does.
 */
public void
resolve_compound_combat_special(object actor, object *targets, int *hitlocs,
    int *random_hitlocs, int *pen, int *damage_types, mixed * items,
    int *resist, int *result)
{
    // Process the actual effects of the special here
} /* resolve_compound_combat_special */

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
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
    mixed *result)
{
    mixed  *hitresult, fail;
    
    /* First do some check if we actually attack. */
    if (pointerp(fail = actor->query_prop(LIVE_AS_ATTACK_FUMBLE)) &&
        sizeof(fail))
    {
        if (query_interactive(actor))
        {
            actor->catch_msg(fail[0]);
        }
    }
    else
    {
        mixed  *hitlocs = allocate(sizeof(targets));
        int    *pens = allocate(sizeof(targets));
        int    *damage_types = allocate(sizeof(targets));
        int    *random_hitlocs = allocate(sizeof(targets));
        mixed  *modified_pen = ({});
        
        for (int i=0; i < sizeof(targets); i++)
        {
            int hitloc = -1;
            int random_hitloc = -1;
            mixed target=targets[i];
        
            int hitloc_factor = 100;
        
            object ob;

            if (objectp(target))
            {
                ob = target;
            }
            else if (pointerp(target))
            {
                ob = target[0];
                hitloc = target[1];
                hitloc_factor = min(100, max(1, query_ability_hitloc_factor()));
                random_hitloc = select_random_hitloc(ob);
            }
            
            if (!objectp(ob))
                continue;

            if (query_ability_offensive(({ ob })) &&
                ob->query_not_attack_me(actor, -1))
                continue;

            int pen = 0;
            if (result[i]<=0)
            {
                pen = result[i];
            }
            else
            {
                pen = query_ability_power(actor,ob,items);
                pen = pen * hitloc_factor / 100;
            }

            if (force_fail(actor, items, ob, resist[i], result[i]))
                continue;
            
            int damage_type = query_ability_damage_type(items);
        
            // Penetration is modified by resistance or AC
            if (query_ability_offensive(({ ob })))
            {
                // Let us handle resistance
                if (damage_type == MAGIC_DT || functionp(query_ability_resist()))
                {
                    int old_pen = pen;
                    if (functionp(query_ability_resist()))
                    {
                        if (functionp(query_ability_apply_resistance_function()))
                        {
                            pen = (int) applyv(query_ability_apply_resistance_function(),
                                              ({pen, resist[i]}));
                        }
                        else
                        {
                            pen = F_NEW_DAMAGE(pen, random(100), resist[i]);
                        }
                    }
                    else
                    {
                        if (!functionp(query_ability_armour_penetration()))
                        {
                            // Modify pen based on default ac.
                            int armour_class = ftoi(F_AC_MOD(40));
                            pen = F_NEW_DAMAGE(pen, random(100), armour_class);
                        }
                        else
                        {
                            pen = (int) applyv(query_ability_armour_penetration(),
                                        ({ pen, damage_type, actor, ob, hitloc,
                                        items, resist[i] }));
                        }
                    }
                
                    if (pen != old_pen)
                    {
                        // Calculate the percentage
                        int pdiff = 100 * pen / old_pen;
                        mixed *mod_list = ({ 
                            ob, pen, hitloc, resist[i], result[i], pdiff
                        });
                    
                        if (!sizeof(modified_pen))
                            modified_pen = allocate(sizeof(mod_list));
                    
                        // Compound the values
                        for (int j = 0; j < sizeof(modified_pen); j++)
                        {
                            if (!pointerp(modified_pen[j]))
                                modified_pen[j] = ({});
                        
                            modified_pen[j] += ({ mod_list[j] });
                        }
                    }
                } // End of armour penetration.
            } else
            {
                pen = F_NEW_DAMAGE(pen, 100, ftoi(F_AC_MOD(40)));
            }
            
            if (functionp(query_ability_resource()))
            {
                // We should scale on resources
                //pen = ftoi(itof(pen) * query_ability_resource_factor());
            }
            
            pens[i] = pen;
            hitlocs[i] = hitloc;
            damage_types[i] = damage_type;
            random_hitlocs[i] = random_hitloc;

            resolve_combat_special(actor, ob, hitloc, random_hitloc, pen,
                damage_type, items, resist[i], result[i]);
        }
        
        resolve_compound_combat_special(actor, targets, hitlocs,
            random_hitlocs, pens, damage_types, items, resist, result);
        
        // Trigger a hook if the pen was modified.
        if (sizeof(modified_pen))
        {
            applyv(hook_ability_penetration_modification, ({ actor, items })
            + modified_pen);
        }
    }
    
    // Apply any costs to player, such as fatigue or mana
    apply_costs_to_player(actor);
} /* resolve_ability */

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_ability_hit(75);
    set_ability_time(15);
    set_ability_offensive(1);
    set_ability_visual(0);
    set_ability_damage_type(W_BLUDGEON);
    set_ability_skills(({ SS_UNARM_COMBAT }));
    set_ability_stats(TS_STR);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_ability_target_verify(verify_change_enemy);
    
    // Set the scaling functions for the ability. by default, we
    // don't know what guild stat will be used
    set_guild_stat_modifier(0, 20, 100);
} /* config_ability */


/*
 * Function name:   restart_npc_special
 * Description:     A function which repeats special abilities for NPCs.
 * Arguments:       1. (object) actor
 *                  2. (string) arg
 * Returns:         Nothing
 */
public void
restart_npc_special(object actor, string arg)
{
    if (query_ability_time() > 0)
    {
        set_alarm(0.1,0.0,&do_ability(arg));
    }
} /* restart_npc_special */