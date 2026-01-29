/*
 * regeneration_obj_base
 *
 * This is the new standard code for the regeneration object, it has been
 * re-balanced and converted to work for fighters as well as casters. This
 * new version scales with stats and skills. It can be affected by haste and
 * you can now alter the frequency at which it heals.
 *
 * Created by Carnak - 2019-04-25
 *
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/effect_obj_base";

#include <tasks.h>
#include <files.h>
#include <ss_types.h>
#include <formulas.h>

// Prototypes
// Global Variables
static int          gHealAlarm,
                    gPeacefulHeal,
                    gHealInterval;
static status       gRandomHeal,
                    gHastedHeal;

/*
 * Function Name:   hook_describe_regeneration
 * Description:     Mask this to give messages for when the target gets healed
 *                  by the regeneration effect.
 * Arguments:       (object) target - The regenerating target
 *                  (int) amount - The amount healed.
 * Returns:         Nothing
 */
public void
hook_describe_regeneration(object target, int amount)
{
    if (amount)
        target->catch_tell("You feel healthier from your quick healing.\n");
} /* hook_describe_regeneration */

/*
 * Function Name:   query_regeneration_skills
 * Description:     Returns the skills that are used in calculating the strength
 *                  of the regeneration.
 * Arguments:       None
 * Returns:         (mixed) - Returns the regeneration skills
 */
public mixed
query_regeneration_skills()
{
    return query_effect_skills();
} /* query_regeneration_skills */

/*
 * Function Name:   set_regeneration_skills
 * Description:     Sets the skills that will be used in calculating the 
 *                  strength of the regeneration.
 * Arguments:       (mixed) skills - 
 * Returns:         Nothing
 */
public nomask void
set_regeneration_skills(mixed skills)
{
    set_effect_skills(skills);
} /* set_regeneration_skills */

/*
 * Function Name:   query_regeneration_stats
 * Description:     Returns the stats that are used in calculating the strength
 *                  of the regeneration.
 * Arguments:       None
 * Returns:         (mixed) - Returns the regeneration stats
 */
public mixed
query_regeneration_stats()
{
    return query_effect_stats();
} /* query_regeneration_stats */

/*
 * Function Name:   set_regeneration_stats
 * Description:     Sets the stats that will be used in calculating the strength
 *                  of the regeneration.
 * Arguments:       (mixed) stats - 
 * Returns:         Nothing
 */
public nomask void
set_regeneration_stats(mixed stats)
{
    set_effect_stats(stats);
} /* set_regeneration_stats */

/*
 * Function Name:   query_regeneration_combat_aid
 * Description:     Returns the combat aid for the regeneration.
 * Arguments:       None
 * Returns:         (int) - amount of combat aid
 */
public int
query_regeneration_combat_aid(object player)
{
    return query_effect_combat_aid(player);
} /* query_regeneration_combat_aid */

/*
 * Function Name:   set_regeneration_combat_aid
 * Description:     Sets the combat aid for the regeneration
 * Arguments:       (mixed) caid - amount of combat aid
 * Returns:         Nothing
 */
public nomask void
set_regeneration_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
} /* set_regeneration_combat_aid */

/*
 * Function Name:   set_regeneration_interval
 * Description:     Sets the percent with which we wish to modify the alarm
 *                  interval. This is capped between 20-250% of the standard
 *                  F_INTERVAL_BETWEEN_HP_HEALING.
 * Arguments:       (int) interval - the modifying percentage
 * Returns:         Nothing
 */
public nomask void
set_regeneration_interval(int interval)
{
    gHealInterval = max(F_INTERVAL_BETWEEN_HP_HEALING, min(250, interval));
} /* set_regeneration_interval */

/*
 * Function Name:   query_regeneration_interval
 * Description:     Returns the interval at which the alarm repeats.
 * Arguments:       None
 * Returns:         (int) - the interval
 */
public nomask int
query_regeneration_interval()
{
    return F_INTERVAL_BETWEEN_HP_HEALING * gHealInterval / 100;
} /* query_regeneration_interval */

/*
 * Function Name:   query_regeneration_peaceful
 * Description:     Returns the peaceful value, which determines how the ability
 *                  behaves in and out of combat.
 * Arguments:       None
 * Returns:         (int)  -1 - Can only heal in combat.
 *                          0 - Unhindered by combat.
 *                          1 - Half heal during combat.
 *                          2 - Can only heal outside of combat.
 */
public int
query_regeneration_peaceful()
{
    return gPeacefulHeal;
} /* query_regeneration_peaceful */

/*
 * Function Name:   set_regeneration_peaceful
 * Description:     Sets the peaceful value, which determines how the ability
 *                  behaves in and out of combat.
 * Arguments:       (int) state - The degree of combat orientation.
 * Returns:         Nothing
 */
public int
set_regeneration_peaceful(int state)
{
    gPeacefulHeal = state;
} /* set_regeneration_peaceful */

/*
 * Function Name:   set_regeneration_random
 * Description:     Sets whether the regeneration heal value is randomized or
 *                  fixed.
 * Arguments:       (status) state - The state of the value randomization.
 * Returns:         Nothing
 */
public status
set_regeneration_random(status state)
{
    gRandomHeal = state;
} /* set_regeneration_random */

/*
 * Function Name:   query_regeneration_random
 * Description:     This queries whether the regeneration heal value is random
 *                  or a fixed value.
 * Arguments:       None
 * Returns:         (status) 1 - The healing is randomized.
 *                           0 - The healing is a fixed value.
 */
public status
query_regeneration_random()
{
    return gRandomHeal;
} /* query_regeneration_random */

/*
 * Function Name:   query_regeneration_hasted
 * Description:     Returns the state of the haste status.
 * Arguments:       None
 * Returns:         (status) 1 - The ability is hasted
 *                           0 - The ability is not hasted 
 */
public status
query_regeneration_hasted()
{
    return gHastedHeal;
} /* query_regeneration_hasted */

/*
 * Function Name:   set_regeneration_hasted
 * Description:     Set whether the regeneration is affected by haste or not.
 * Arguments:       (status) state - the state of the haste status
 * Returns:         Nothing
 */
public status
set_regeneration_hasted(status state)
{
    gHastedHeal = state;
} /* set_regeneration_hasted */

/*
 * Function Name:   query_regeneration_valid
 * Description:     Validation function to see whether this regeneration object
 *                  is valid in the current situation
 * Arguments:       (object) player - player who is regenerating
 * Returns:         (status) 0 - invalid
 *                  (status) 1 - valid
 */
public status
query_regeneration_valid(object player)
{
    return 1;
} /* query_regeneration_valid */

/*
 * Function Name:   create_regeneration
 * Description:     The create function called for objects that inherit this
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_regeneration()
{
} /* create_regeneration */

/*
 * Function Name:   create_effect
 * Description:     The create function called for objects that inherit this
 * Arguments:       None
 * Returns:         Nothing
 */
public nomask void
create_effect()
{
    setuid();
    seteuid(getuid());
    
    set_name("_regeneration_object_");
    set_short("regeneration object");    
    set_long("This is the standard regeneration object. It continuously "
        + "heals the target.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the regeneration spell.\n");
    
    set_regeneration_hasted(0);
    set_regeneration_combat_aid(50);
    set_regeneration_interval(150);
    set_regeneration_peaceful(1);
    set_regeneration_skills(({ SS_DEFENCE }));
    set_regeneration_stats(({ TS_CON }));
    set_regeneration_random(0);
    create_regeneration();
} /* create_effect */

/*
 * Function Name:   calculate_heal_amount
 * Description:     This calculate how much should be healed based on stat,
 *                  skill and combat.
 * Arguments:       (object) target - The target of the healing
 * Returns:         (int) adjusted amount of healing
 */
public nomask int
calculate_heal_amount(object target)
{
    /*
     * The healing works the same way as damage would, you start by getting
     * your penetration from a base pen value of 40.
     *    F_PENMOD(40, skill) - using your skill to scale the value
     *
     * Next you would need to modify this by a set of stats.
     *    penetration * F_STR_FACTOR(stat) / 100
     * 
     * After this we need to figure out how much health we can get from the
     * penetration we have generated. If we want a random value, we would need
     * to follow the following formula.
     *    phit = pen / 4;
     *    phit += random(phit) + random(phit) + random(phit);
     *    F_NEW_DAMAGE(phit, random(100), 40);
     * If we want to avoid random generation, we can just divide the pen in two
     * as the phit in the previous formula randomizes to an average of 62.5% of
     * the penetration and the random(100) on 40 ac is another 20% reduction.
     * This results in 62.5 * 0.8 = 50%
     *    F_NEW_DAMAGE(pen / 2, 40, 40);
     *
     * Next we account for the time of the ability, it uses the Healing interval
     * which is currently set to 20. We divide this by 5 to make sure that the
     * initial caid is at 100, as 280pen over 5sec is 100caid.
     *    heal amount * F_INTERVAL_BETWEEN_HP_HEALING / 5;
     * 
     * We adjust for the ability caid.
     *    heal amount * query_regeneration_combat_aid() / 100;
     *
     * Then we optionally allow the effect of haste.
     *    heal amount * ftoi(target->query_speed(100)) / 100
     *
     * Lastly we optionally alter the amount healed in combat.
     */
    
    int pen, stat, skill, healing;
    
    skill = calc_base_skill(target, query_regeneration_skills());
    stat = calc_stat_modifier(target, query_regeneration_stats());
    pen = F_PENMOD(40, skill) * F_STR_FACTOR(stat) / 100;
    
    if (query_regeneration_random())
    {
        int phit = pen / 4;
        phit += random(phit) + random(phit) + random(phit);
        healing = F_NEW_DAMAGE(phit, random(100), 40);
    } else
        healing = F_NEW_DAMAGE(pen / 2, 40, 40);
        
    // Adjust healing for actual interval
    healing = healing * query_regeneration_interval() / 5;
    
    // Adjust healing for combat aid
    healing = query_regeneration_combat_aid(target) * healing / 100;
    
    // Adjust healing based on combat aid modifier
    healing = healing * query_combat_aid_modifier(target) / 100;
    
    if (query_regeneration_hasted())
    {
        // Adjust the healing based on haste
        healing = healing * 100 / ftoi(target->query_speed(100));
    }
    
    // Adjust healing for if the player is in combat or not relaxed. If that's
    // the case, then we reduce the regeneration by a factor.
    int relaxed = target->query_relaxed_from_combat();
    switch (query_regeneration_peaceful())
    {
        case -1:
        /* Can only heal in combat */
            if (relaxed)
                healing = 0;
            break;
        case 0:
        /* Heals the same no matter state of combat */
            break;
        case 1:
        /* Halves healing while in combat */
            if (!relaxed)
                healing /= 2;
            break;
        case 2:
        /* Can not heal while in combat */
            if (!relaxed)
                healing = 0;
            break;
    }
    
    if (!query_regeneration_valid(target))
        return 0;
    
    // Return the final result
    return healing;
} /* calculate_heal_amount */

/*
 * Function Name:   do_regeneration
 * Description:     The function that gets called every interval to heal the
 *                  target.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
do_regeneration()
{
    object target = query_effect_target();
    if (!objectp(target) || !IS_LIVING_OBJECT(target)
        || target->query_linkdead() || target->query_linkdead_in_combat())
        return;

    int max_hp = target->query_max_hp();
    int cur_hp = target->query_hp();
    
    // No need for regeneration
    if (max_hp == cur_hp)
        return;
    
    int heal_amount = calculate_heal_amount(target);
    int adjusted_heal_amount = min(heal_amount, max_hp - cur_hp);
    
    target->heal_hp(adjusted_heal_amount);
    
    hook_describe_regeneration(target, heal_amount);
} /* do_regeneration */

/*
 * Function Name:   start
 * Description:     Start up the effect. We override this method so that we can
 *                  start the healing alarm.
 * Arguments:       None
 * Returns:         (int) 1 - effect started
 *                  (int) 0 - effect did not start
 */
public int
start()
{
    int result = ::start();
    if (!result)
        return result;
    
    // Set the actual alarm that will perform the regeneration  
    float interval = itof(query_regeneration_interval());
    remove_alarm(gHealAlarm);
    gHealAlarm = set_alarm(interval, interval, do_regeneration);

    return result;
} /* start */