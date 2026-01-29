#pragma strict_types

#include "defs.h"
#include <tasks.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit TIMED_ABILITY_LIB;


// Prototypes
public nomask int calc_hitme_modifier();

// Global Variables
static int      gAbility_tohit,
                gAbility_aid = 135, 
                gAbility_gstat_type = 0,
                gAbility_gstat_min_pct = 20,
                gAbility_gstat_cap = 100;

static mixed    gAbility_skills,
                gAbility_stats,
                gDebuffEffect;
            
public mixed
query_debuff_effect()
{
    return gDebuffEffect;
}

public void
set_debuff_effect(mixed effect)
{
    gDebuffEffect = effect;
}

/*
 * Function name:   apply_costs_to_player
 * Description:     By default, a small fatigue cost is applied for the special.
 *                  Other costs can be applied as well by a masked function.
 * Arguments:       (object) actor - actor executing the special
 * Returns:         Nothing
 */
public void
apply_costs_to_player(object actor)
{
    actor->add_fatigue(-2);
} /* apply_costs_to_player */

/*
 * Function name:   select_random_hitloc
 * Description:     This returns a random hitloc on the target.
 * Arguments:       (object) target - the target of the ability
 * Returns:         (int) The hitloc ID or -1 if no target
 */
public int
select_random_hitloc(object target)
{
    int    *hitloc_ids,
            j, tmp;
    object  cobj;
    
    if (!objectp(target))
        return -1;
    
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
 * Function name:   query_tohit
 * Description:     Calculates the tohit for the actor.
 * Arguments:       None
 * Returns:         (int) The special hit value
 */
public int
query_tohit()
{
    return gAbility_tohit;
} /* query_tohit */

public void
set_tohit(int i)
{
    gAbility_tohit=i;
} /* set_tohit */

/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Arguments:       (object) actor - actor executing special
 * Returns:         (int) value between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the actor
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    return 100;
} /* query_combat_aid_modifier */

public void
set_combat_aid(int aid)
{
    gAbility_aid = aid;
} /* set_combat_aid */

public nomask int
query_combat_aid()
{
    int modifier;
    
    // The combat aid can change by situation. Query for
    // the modifier to change the combat aid for the
    // current situation.
    modifier = max(1, min(100, query_combat_aid_modifier()));
    return (gAbility_aid * modifier) / 100;
} /* query_combat_aid */
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
        gAbility_gstat_type = guild_type;
        break;
    default:
        gAbility_gstat_type = 0;
    }
    
    if (min_pct < 0)
    {
        min_pct = 0;
    }
    else if (min_pct > 100)
    {
        min_pct = 100;
    }
    
    gAbility_gstat_min_pct = min_pct;
    gAbility_gstat_cap = cap;
}

public int
query_guild_stat_minimum_percentage(object player)
{
    return gAbility_gstat_min_pct;
}

public int
query_guild_stat_type(object player)
{
    return gAbility_gstat_type;
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
    return gAbility_gstat_cap;
}

/*
 * Function name:   calc_guildstat_modifier_helper
 * Description:     This is the helper function for calc_guild_stat_modifier
 *                  It takes in the values and does a standard set of
 *                  calculations to determine the modifier for the special.
 * Arguments:       1. (object) player - the player executing the special
 *                  2. (int) caid - the current value to be modified
 *                  3. (int) gstat_type -
 *                  4. (int) gstat_min_pct -
 *                  5. (int) gstat_cap -
 * Returns:         (int) The modified value
 */
static nomask int
calc_guildstat_modifier_helper(object player, int caid, int gstat_type,
                               int gstat_min_pct, int gstat_cap)
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

            caid = caid * gstat_modifier / 100;
            
            send_debug_message("debug_damage", "Res after gstat modifier "
            + gstat_modifier + " applied: " + caid + "\n");
        }
    }
    
    return caid;
} /* calc_guildstat_modifier_helper */

/*
 * Function name:   calc_guildstat_modifier
 * Description:     This function by default takes the values that are set
 *                  during set_guild_stat_modifier, and calculates a scaling
 *                  mechanism for the special. It should return a value that
 *                  modifies the input "caid" down if the person does not have
 *                  sufficient guild stat.
 * Arguments:       1. (object) player - the player executing the special
 *                  2. (int) caid - the current damage value to be modified
 * Returns:         (int) The modified value
 */
static int
calc_guildstat_modifier(object player, int caid)
{
    // Now we modify based on guild stat if it has been set
    int gstat_type = query_guild_stat_type(player);
    int gstat_min_pct = query_guild_stat_minimum_percentage(player);
    int gstat_cap = query_guild_stat_cap(player);
    
    return calc_guildstat_modifier_helper(player, caid, gstat_type,
                                          gstat_min_pct, gstat_cap);
}

/*
 * Function name:   query_skills
 * Description:     Returns the skills used for the special.
 * Arguments:       None
 * Returns:         (mixed) The list of skills
 */
public mixed
query_skills()
{
    return gAbility_skills;
} /* query_skills */

/*
 * Function name:   set_skills
 * Description:     Sets the skills used for the special.
 * Arguments:       (mixed) The list of skills
 * Returns:         Nothing
 */
public void
set_skills(mixed skills)
{
    gAbility_skills = skills;
} /* set_skills */

/*
 * Function name:   query_stats
 * Description:     Returns the stats used for the special.
 * Arguments:       None
 * Returns:         (int) The list of stats
 */
public mixed
query_stats()
{
    return gAbility_stats;
} /* query_stats */

/*
 * Function name:   set_stats
 * Description:     Sets the stats used for the special.
 * Arguments:       (mixed) The list of stats
 * Returns:         Nothing
 */
public void
set_stats(mixed stats)
{
    gAbility_stats = stats;
} /* set_stats */

/*
 * Function name:   query_success
 * Description:     Determine if the ability successfully hit.
 * Arguments:       1. (object) actor - The one executing the special
 *                  2. (mixed) target - The target of the special
 * Returns:         (int) The result as an integer indicating success or
 *                        failure (0 indicating failure, positive integer
 *                        indicating % success, possibly > 100)
 */
static nomask int
query_success(object actor, mixed target)
{
    object ob;
    object combat_obj;
    int result;
    
    if (pointerp(target))
        ob = target[0];
    
    if (objectp(target))
        ob = target;
    
    if (!objectp(ob))
        return 0;
    
    combat_obj = actor->query_combat_object();
    result = combat_obj->cb_tohit(-1, query_tohit(), ob);
    
    return result;
} /* query_success */

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
    set_ability_prep_time(5);
    set_ability_cooldown_time(30);
    set_ability_name("debuff");
    set_ability_offensive(1);
    set_ability_stationary(1);
    set_ability_visual(1);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_ability_allow_hunting(1);
    set_ability_hasted(0);
    
    set_tohit(110);
    set_stats(({ SKILL_VALUE, 100 }));
    set_skills(({ SKILL_VALUE, 100 }));
    set_combat_aid(135);
    set_debuff_effect(BLIND_OBJ_BASE);
} /* config_ability */

public nomask object
setup_debuff_effect(object actor, object target, mixed *items, int resist)
{
    int     caid;
    object  effect;
    mixed   obj;

    obj = query_debuff_effect();
    
    if (functionp(obj))
    {
        function f = obj;
        effect = f(actor, target, items, resist);
    }
    else if (stringp(obj))
        effect = clone_object(obj);
    else
        effect = obj;
    
    if (!objectp(effect))
        return 0;
    
    caid = query_combat_aid() * 100 / (100 - calc_hitme_modifier());
    caid = caid * (100 - resist) / 100;
                           
    if (!actor->query_npc())
    {
        // NPCs don't generally have guild stat, so we don't limit
        // their abilities by guildstat.        
        int gstat_result = calc_guildstat_modifier(actor, caid);
        if (gstat_result < caid)
        {
            // We put this if-condition check here so that GM's don't
            // try and use this function to increase the aid without
            // using the correct functions.
            caid = gstat_result;
        }
    }
    
    effect->set_effect_skills(gAbility_skills);
    effect->set_effect_stats(gAbility_stats);
    effect->set_effect_combat_aid(caid);
    effect->set_dispel_time(query_ability_time());
    
    return effect;
} /* setup_debuff_effect */

/*
 * Function name:   resolve_debuff_ability
 * Description:     This function is called from resolve_ability to finalize
 *                  the special.
 *
 * Arguments:       1. (object)   The actor
 *                  2. (object *) The targets
 *                  3. (int *)    Resistance values corresponding to each target
 *                  4. (int)      The attempt result as returned by
 *                                query_casting_success()
 *
 * Returns:         Nothing
 */
public void
resolve_debuff_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *result)
{
    // Messages for the hit here.
} /* resolve_debuff_ability */

/*
 * Function name:   resolve_ability
 * Description:     This function is responsible for performing the routines
 *                  necessary to produce the special effect(s). All specials
 *                  that manifest any effect whatsoever need to redefine this
 *                  and implement those.
 *                  NB: _live_i_attack_delay is treated as a partial stun, and
 *                  does not block these specials
 *
 * Arguments:       1. (object)   The actor
 *                  2. (object *) The targets
 *                  3. (int *)    Resistance values corresponding to each target
 *                  4. (int)      The attempt result as returned by
 *                                query_casting_success()
 * Returns:         Nothing
 */
public nomask void
resolve_ability(object actor, mixed *items, mixed *targets, int *resist,
                mixed *result)
{
    mixed *effects, fail;

    effects = allocate(sizeof(targets));
    
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
        resolve_debuff_ability(actor, items, targets, resist, result);
        
        for (int i = 0; i < sizeof(targets); i++)
        {
            mixed   effect,
                    target = targets[i];
            int     hitloc = -1,
                    random_hitloc = -1;
            
            if (pointerp(target))
            {
                target = target[0];
                hitloc = target[1];
                random_hitloc = select_random_hitloc(target);
            }
            
            if (!objectp(target))
                continue;
            
            /* The ability failed so we do not wish to add an effect */
            if (result[i] < 0)
                continue;
            
            if (target->query_not_attack_me(actor, -1))
                continue;
            
            effect = setup_debuff_effect(actor, target, items, resist[i]);
            
            if (!objectp(effect))
                continue;
            
            effects[i] = make_ability_effect_object(effect, actor, targets[i],
                                                    resist[i], result[i]);
        }
    }
    
    // Apply any costs to actor, such as fatigue
    apply_costs_to_player(actor);
} /* resolve_ability */

public nomask int
calc_hitme_modifier()
{
    switch ((query_tohit() - 1) / 5)
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
        case 17: return 18;
        case 18: return 16;
        case 19: return 13;
        case 20: return 11;
        case 21: return 10;
        default: return 0;
    }
    
    return 0;
}