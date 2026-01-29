#pragma strict_types
#include "defs.h"
inherit LIB_DIR + "grid.c";

static function locate_callback;
static int locate_alarm;
static object locate_target;

void
stop_locating(int result)
{
    if (get_alarm(locate_alarm))
    {
        remove_alarm(locate_alarm);
        if (locate_callback)
            locate_callback(result);
    }
}

void
do_locate()
{
    object here = E(TO);

    if (E(locate_target) == here)
        stop_locating(1);
    else if (!step_towards(locate_target) || E(TO) == here)
        stop_locating(0);
}

void
locate(object target, float delay = 2.0, function callback = 0)
{
    remove_alarm(locate_alarm);
    locate_target = target;
    locate_callback = callback;
    locate_alarm = set_alarm(delay, delay, do_locate);
}

object
query_locating()
{
    if (get_alarm(locate_alarm))
        return locate_target;
    return 0;
}
