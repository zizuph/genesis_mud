/*
 * Task Modifiers Library
 * 
 * Tasks can be modified with skills and stats. This module contains
 * the base code to calculate the correct modifiers for the skills
 * and stats.
 *
 * Created by Petros, June 2008
 */
 
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "../debugger/debugger_tell.h"

/*
 * Function name: find_drm
 * Description  : Converts the stat list/skill list to an actual number
 * Arguments    : player - player executing special
 *                tasks - resolve_task style list of tasks
 * Returns      : actual stat/skill value
 */
public nomask int find_drm(object actor, mixed tasks)
{
    int result = actor->find_drm(tasks);
    result /= 2; 
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
 * Function name: calc_stat_modifier
 * Description  : Obtains a modifier based on the players stats
 * Arguments    : player - player evading
 * Returns      : modifier
 */
public nomask int 
calc_stat_modifier(object player, mixed stats)
{
    if (intp(stats))
    {
        return find_drm(player, ({ stats }));
    }
    return find_drm(player, stats);
}

/*
 * Function name: calc_base_skill
 * Description  : Obtains a modifier based on the players skills
 * Arguments    : player - player with the effect
 * Returns      : modifier
 */
public nomask int 
calc_base_skill(object player, mixed skills)
{
    if (intp(skills))
    {
        return max(15, find_drm(player, ({ skills })));
    }
    return max(15, find_drm(player, skills));
}
