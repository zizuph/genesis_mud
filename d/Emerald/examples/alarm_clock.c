/* /d/Emerald/examples/clock.c
 * 
 * This simple example demonstrates the basics of making a clock
 * and also how to use the event scheduler.
 */
inherit "/std/object";

#include <macros.h>
#include "/d/Emerald/sys/time.h"

void ring_bell();

void
create_object()
{
    if (!IS_CLONE)
    {
        /* This is particularly important since we don't want the master
         * object adding an unnecessary scheduled event.
         */
        return;
    }

    set_name("clock");
    set_adj("alarm");

    /* Set the long desc and include the current time. */
    set_long("This alarm clock is set to go off at the start of " +
        "the second quarter, daily.\n@@clock_time@@");

    /* Schedule the alarm for the second quarter (05:00) */
    SCHEDULE_EVENT(this_object(), ring_bell, -1, -1, -1, SECOND_QUARTER, 0);
}

public string
clock_time()
{
    /* Note that we use the standard time string, not the exact one.
     * This is the case for most Emerald clocks.
     */
    return "The hand indicates that it is " + EMERALD_TIME_STRING + ".\n";
}

void
ring_bell()
{
    tell_room(environment(), "The alarm clock rings loudly!\n");

    /* Reschedule the alarm for the second quarter (05:00) */
    SCHEDULE_EVENT(this_object(), ring_bell, -1, -1, -1, SECOND_QUARTER, 0);
}
    
