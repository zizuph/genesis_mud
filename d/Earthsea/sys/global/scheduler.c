#pragma save_binary
#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#define USE_MULTI_ALARM
#undef  USE_MULTI_ALARM

#ifdef USE_MULTI_ALARM
inherit "/d/Genesis/lib/multi_alarm";
#endif USE_MULTI_ALARM

#include "/d/Earthsea/sys/time.h"

nomask void do_scheduled_event(object ob, function func);

/*
 * Function name: schedule
 * Description:   schedule a time-dependent event
 * Arguments:     object ob     - The object responsible for the event.  If this
 *                                object is not present at event time, the event
 *                                will not occur.
 *                function func - the function to call at event time
 *                int year      - The year the event should happen or -1 for
 *                                next appropriate year.
 *                int month     - The month the event should happen or -1 for
 *                                next appropriate month.
 *                int day       - The day the event should happen or -1 for
 *                                next appropriate day.
 *                int hour      - The hour the event should happen or -1 for
 *                                next appropriate hour.
 *                int minute    - The minute the event should happen
 * Returns:       an integer id to be used for unschedule()
 */
varargs nomask int
schedule(object ob, 
         function func, 
         int year   = 0,
         int month  = 0,
         int day    = 0,
         int hour   = 0,
         int minute = 0)
{
    int id, delay;

    /* We should set our euid in case the clock needs to be loaded */
    setuid();
    seteuid(getuid());

    /* find out how long until the scheduled event should happen */
    delay = EARTHSEA_CLOCK_FILE->seconds_until_time(year, 
        month, day, hour, minute, 0);

    if (delay < 0)
    {
        return 0;
    }

#ifdef USE_MULTI_ALARM
    id = set_multi_alarm(itof(delay), &do_scheduled_event(ob, func));
#else
    id = set_alarm(itof(delay), 0.0, &do_scheduled_event(ob, func));
#endif USE_MULTI_ALARM

    return id;
}

/*
 * Function name: do_scheduled_event
 * Desription:    execute an event that has been scheduled
 * Arguments:     object ob - The object responsible for the event;  if it is
 *                            not present, the event function will not be
 *                            called.
 *                function func - The function to call to start the event
 */
nomask void
do_scheduled_event(object ob, function func)
{
    if (ob)
    {
        func();
    }
}

/*
 * Function name: unschedule
 * Description:   Unschedule a sheduled event
 * Arguments:     int id - the id for the event as given by schedule()
 */
nomask void
unschedule(int id)
{
#ifdef USE_MULTI_ALARM
    remove_multi_alarm(id);
#else
    remove_alarm(id);
#endif USE_MULTI_ALARM
}

/*
 * Function name: remove_object
 * Description:   remove the scheduler if no events are scheduled.  If
 *                Events are scheduled, throw an exception.  If you must
 *                destroy this object, call unconditional_remove_scheduler()
 */
nomask void
remove_object()
{
#ifdef USE_MULTI_ALARM
    if (!sizeof(get_all_multi_alarms()))
#else
    if (!sizeof(get_all_alarms()))
#endif USE_MULTI_ALARM
    {
        destruct();
    }
    else
    {
        throw("Cannot destruct while events are scheduled!\n");
    }
}

/*
 * Function name: unconditional_remove_scheduler
 * Description:   Remove this object even if there are scheduled events.
 *                This shouldn't be done without good reason.
 */
nomask void
unconditional_remove_scheduler()
{
    if (this_player() && (this_interactive() == this_player()))
    {
        dump_array(get_all_alarms());
    }

    destruct();
}
