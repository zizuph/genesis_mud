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
#include "defs.h"
inherit LIB_DIR + "grid.c";

static function follow_callback;
static int follow_alarm;
static object follow_target;

void
stop_following()
{
    if (get_alarm(follow_alarm))
    {
        remove_alarm(follow_alarm);
        if (follow_target && follow_callback)
            follow_callback(follow_target);

        follow_target = 0;
        follow_callback = 0;
    }
}

void
do_follow()
{
    object here = E(TO);

    if (follow_target && E(follow_target) == here)
        return;

    if (!step_towards(follow_target) || E(TO) == here)
        stop_following();
}

void
follow(object target, float delay = 2.0, function callback = 0)
{
    remove_alarm(follow_alarm);
    follow_target = target;
    follow_callback = callback;
    follow_alarm = set_alarm(delay, delay, do_follow);
}

object
query_following()
{
    if (get_alarm(follow_alarm))
        return follow_target;
    return 0;
}
