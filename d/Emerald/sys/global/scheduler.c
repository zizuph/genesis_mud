#pragma save_binary
#pragma no_clone
#pragma no_inherit
#pragma no_shadow

#include "/d/Emerald/sys/time.h"

#define EVENT_ARR_OBJ    0
#define EVENT_ARR_FUN    1
#define EVENT_ARR_MINUTE 2
#define EVENT_ARR_HOUR   3
#define EVENT_ARR_DAY    4
#define EVENT_ARR_MONTH  5
#define EVENT_ARR_YEAR   6
#define EVENT_ARR_SIZE   7

private static int *event_ids = ({});
private static mapping event_map = ([]);

nomask void
create()
{
    setuid();
    seteuid(getuid());
    REGISTER_FOR_TIME_UPDATES(this_object());
}

public int *
get_exact_date(int year, int month, int day, int hour, int minute)
{
    int flag;

    if (minute < 0)
    {
        minute = EMERALD_MINUTE + 1;
        flag = 1;
    }

    if (hour < 0)
    {
        if (!flag && (minute <= EMERALD_MINUTE))
        {
            hour = EMERALD_HOUR + 1;
        }
        else
        {
            hour = EMERALD_HOUR;
        }

        flag = 1;
    }

    if (minute >= MINUTES_IN_HOUR)
    {
        hour++;
        minute -= MINUTES_IN_HOUR;
    }
    
    if (day < 0)
    {
        if (!flag && (hour <= EMERALD_HOUR))
        {
            day = EMERALD_DAY + 1;
        }
        else
        {
            day = EMERALD_DAY;
        }

        flag = 1;
    }

    if (hour >= HOURS_IN_DAY)
    {
        day++;
        hour -= HOURS_IN_DAY;
    }

    if (month < 0)
    {
        if (!flag && (day <= EMERALD_DAY))
        {
            month = EMERALD_MONTH + 1;
        }
        else
        {
            month = EMERALD_MONTH;
        }

        flag = 1;
    }

    if (day > DAYS_IN_MONTH)
    {
        month++;
        day -= DAYS_IN_MONTH;
    }

    if (year < 0)
    {
        if (!flag && (month <= EMERALD_MONTH))
        {
            year = EMERALD_YEAR + 1;
        }
        else
        {
            year = EMERALD_YEAR;
        }

        flag = 1;
    }

    if (month > MONTHS_IN_YEAR)
    {
        year++;
        month -= MONTHS_IN_YEAR;
    }

    return ({ year, month, day, hour, minute });
}

public varargs int
compare_date(int year, int month, int day, int hour, int minute,
             int oyear = EMERALD_YEAR, int omonth = EMERALD_MONTH,
             int oday = EMERALD_DAY, int ohour = EMERALD_HOUR,
             int ominute = EMERALD_MINUTE)
{
    int *scheduled_date;

    scheduled_date = get_exact_date(year, month, day, hour, minute);
    year   = scheduled_date[0];
    month  = scheduled_date[1];
    day    = scheduled_date[2];
    hour   = scheduled_date[3];
    minute = scheduled_date[4];

#ifdef COMPARE_MINUTES
    {
        int mins = minute +
            hour * MINUTES_IN_HOUR +
            day * HOURS_IN_DAY * MINUTES_IN_HOUR +
            month * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR +
            year * MONTHS_IN_YEAR * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR;
        int omins = ominute +
            ohour * MINUTES_IN_HOUR +
            oday * HOURS_IN_DAY * MINUTES_IN_HOUR +
            omonth * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR +
            oyear * MONTHS_IN_YEAR * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR;

        return ((mins == omins) ? 0 : ((mins > omins) ? 1 : -1));
    }
#else
                   
    if (year != oyear)
    {
        return ((year > oyear) ? 1 : -1);
    }

    if (month != omonth)
    {
        return ((month > omonth) ? 1 : -1);
    }

    if (day != oday)
    {
        return ((day > oday) ? 1 : -1);
    }

    if (hour != ohour)
    {
        return ((hour > ohour) ? 1 : -1);
    }

    if (minute != ominute)
    {
        return ((minute > ominute) ? 1 : -1);
    }

    return 0;
#endif
}
       
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
    mixed *event_arr;
    int id, i, *scheduled_date;

    scheduled_date = get_exact_date(year, month, day, hour, minute);
    year   = scheduled_date[0];
    month  = scheduled_date[1];
    day    = scheduled_date[2];
    hour   = scheduled_date[3];
    minute = scheduled_date[4];

    id = (sizeof(event_ids) ? applyv(max, event_ids) + 1 : 1);

    /* We want to order the event_ids array now so that we don't
     * have to do a lot of searching for the right dates later on.
     */
    for (i = 0; i < sizeof(event_ids); i++)
    {    
        if (compare_date(year, month, day, hour, minute, 
            event_map[event_ids[i]][EVENT_ARR_YEAR],
            event_map[event_ids[i]][EVENT_ARR_MONTH],
            event_map[event_ids[i]][EVENT_ARR_DAY],
            event_map[event_ids[i]][EVENT_ARR_HOUR],
            event_map[event_ids[i]][EVENT_ARR_MINUTE]) < 1)
        {
            break;
        }
    }

    if (i < 1)
    {
        event_ids = ({ id }) + event_ids;
    }
    else if (i >= sizeof(event_ids))
    {
        event_ids += ({ id });
    }
    else
    {
        event_ids = event_ids[..(i - 1)] + ({ id }) + event_ids[i..];
    }

    event_arr = allocate(EVENT_ARR_SIZE);
    event_arr[EVENT_ARR_OBJ]    = ob;
    event_arr[EVENT_ARR_FUN]    = func;
    event_arr[EVENT_ARR_MINUTE] = minute;
    event_arr[EVENT_ARR_HOUR]   = hour;
    event_arr[EVENT_ARR_DAY]    = day;
    event_arr[EVENT_ARR_MONTH]  = month;
    event_arr[EVENT_ARR_YEAR]   = year;

    event_map[id] = event_arr;

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
    event_map = m_delete(event_map, id);
    event_ids -= ({ id });
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
    if (!sizeof(event_ids))
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
        dump_array(event_ids);
    }

    destruct();
}

/* 
 * Function name: update_time
 * Description:   Called by the Emerald clock to notify this object
 *                that time has been incremented.
 */
void
update_time()
{
    string err;
    object ob;
    function f;
    int i = 0;
    int id;

    /* Check to see if any events are scheduled for this time.  If so,
     * execute them.
     */
    while (i < sizeof(event_ids))
    {
        id = event_ids[i];
        if (compare_date(event_map[id][EVENT_ARR_YEAR],
                         event_map[id][EVENT_ARR_MONTH],
                         event_map[id][EVENT_ARR_DAY],
                         event_map[id][EVENT_ARR_HOUR],
                         event_map[id][EVENT_ARR_MINUTE]) < 1)
        {
            ob = event_map[id][EVENT_ARR_OBJ];
            f  = event_map[id][EVENT_ARR_FUN];

            unschedule(id);
            err = catch(do_scheduled_event(ob, f));

            if (strlen(err))
	    {
                log_file(TIME_ERRORS, "Error in event (" + 
                    ctime(time()) + ": " + file_name(ob) + "\n" + err);
	    }
        }
        else
        {
            break;
        }
    }
}

