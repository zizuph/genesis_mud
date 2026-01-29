/*
 * These functions are used in conjunction with the mapped domain grid
 * located at "/d/Raumdor/common/std/grid.c" to allow NPCs in the domain
 * to hunt fleeing enemies by moving through the domain to their location.
 * This is an alternative to auto-hunt that causes the NPCs to move more
 * naturally through the domain rather than just auto-hunting or using
 * move() to teleport them.
 *
 * Updated 2018.02.07 (Shanoga)
 */
 
#pragma strict_types
#include "/d/Raumdor/defs.h"
inherit "/d/Raumdor/lib/grid.c";

void follow_target(object target, float delay);

/*
 * Function name: step_towards_target 
 * Description  : This function finds a target location relative to an object.
 *              : It may be called to find a target that has fled from battle
 *              : and should be chased by an NPC.
 * Arguments    : object enemy - the most recent weakest_link enemy
 */

int
step_towards_target(object target)
{
    int i, result;
    string *directions = query_grid_directions(environment(this_object()),
            environment(target));

    for (i = sizeof(directions) - 1; i >= 0; i--)
    {
        result = command("$" + directions[i]);
        if (result)
            break;
    }
    if (i < 0)
        return 0;
    return 1;
}

void
do_follow_target(object target, float delay)
{
    // If we failed to follow, we give up
    if (step_towards_target(target))
        follow_target(target, delay);
}

void
follow_target(object target, float delay)
{
    set_alarm(delay, 0.0, &do_follow_target(target, delay));
}
