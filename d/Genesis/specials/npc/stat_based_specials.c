/*
 * Stat Based Specials Support for NPCs
 *
 * This module should be inherited in an npc that wants to
 * base their specials on preset values dependent on their
 * average stats.
 *
 * 
 * Created by Petros, May 2009
 */

#include <formulas.h>

/*
 * Function:    query_skill_by_stat
 * Description: This is the skill value that will be used for
 *              skills that the NPC has. It returns a slightly
 *              random value, so each invocation for the same
 *              stat may give different results.
 */
public int
query_skill_by_stat(int avg_stat)
{
    int skill;
    
    switch (avg_stat)
    {
    case 0..25:
        skill = 30;
        break;
    
    case 26..50:
        skill = 40;
        break;
    
    case 51..75:
        skill = 50;
        break;
    
    case 76..100:
        skill = 60;
        break;
    
    case 101..125:
        skill = 70;
        break;
    
    case 126..150:
        skill = 80;
        break;
    
    case 151..175:
        skill = 90;
        break;
    
    default:
        skill = 100;
        break;
    }
    
    return min(100, skill + random(10));
}

/*
 * Function:    query_tohit_by_stat
 * Description: This determines their default to-hit values to be used
 *              in the calculation of their combat specials.
 */
public int
query_tohit_by_stat(int avg_stat)
{
    int skill;
    
    switch (avg_stat)
    {
    case 0..25:
        skill = 60;
        break;
    
    case 26..50:
        skill = 70;
        break;
    
    case 51..75:
        skill = 80;
        break;
    
    case 76..100:
        skill = 90;
        break;
    
    case 101..125:
        skill = 100;
        break;
    
    case 126..150:
        skill = 110;
        break;
    
    case 151..175:
        skill = 120;
        break;
    
    default:
        skill = 130;
        break;
    }
    
    return skill;
}

/*
 * Function:    query_pen_by_stat
 * Description: This actually returns the result of using F_PENMOD
 *              with the pen, and tohit values. So for example, this
 *              would return 280 if pen was 40 and skill was 100.
 */
public int
query_pen_by_stat(int avg_stat)
{
    int pen;
    
    switch (avg_stat)
    {
    case 0..25:
        pen = 25;
        break;
    
    case 26..50:
        pen = 29;
        break;
    
    case 51..75:
        pen = 33;
        break;
    
    case 76..100:
        pen = 37;
        break;
    
    case 101..125:
        pen = 40;
        break;
    
    case 126..150:
        pen = 44;
        break;
    
    case 151..175:
        pen = 48;
        break;
    
    default:
        pen = 50;
        break;
    }
    
    // Add a random factor averaging 100 on top of the pen.
    // Range is from 112-336 (depending on stats). With the random,
    // the maximum average pen is 436 for the highest npcs.
    pen = F_PENMOD(pen, query_skill_by_stat(avg_stat)) 
          + random(100) + random(100);
    
    return pen;
}

/*
 * Function:    query_special_did_hit
 * Description: This checks to see if the NPC special can actually
 *              hit or not.
 */
public int
query_special_did_hit(object player, object target)
{
    object combat_obj;
    
    if (!objectp(target))
    {
        return 0;
    }

    combat_obj = player->query_combat_object();
    if (combat_obj->cb_tohit(-1, 
        query_tohit_by_stat(player->query_average_stat()), target) > 0)
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    do_stat_based_attack
 * Description: This takes into account multiple factors when executing
 *              an npc attack. It will ensure that evade abilities are
 *              accounted for, check against the tohit, and also finally
 *              execute the attack based on the stat based formulas.
 *              If the attack is evaded, then no messages should be printed.
 *              If the attack is missed, then a miss message should be printed
 *              If the attack succeeds, then the appropriate hit message should be printed.
 * Arguments:   player - the npc doing the attack
 *              enemy  - the target receiving the special attack
 *              dt     - the damage type
 * Returns:     0      - means that the attack was evaded or enemy cannot be attacked
 *              hitresult - array of hitresults from the hit_me function.
 *                          if hitresult is all -1 values, then attack missed.
 */
public mixed
do_stat_based_attack(object player, object enemy, int dt)
{
    mixed hitresult = ({ -1, -1, -1, -1, -1 });
    // Make sure that we can actually attack the target
    if (enemy->query_not_attack_me(player, -1))
    {
        return 0;
    }

    if (query_special_did_hit(player, enemy))
    {
        int avg_stat = player->query_average_stat();
        hitresult = enemy->hit_me(query_pen_by_stat(avg_stat), 
            dt, player, -1);
    }
    
    return hitresult;
}
