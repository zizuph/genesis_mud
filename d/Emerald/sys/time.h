#ifndef EMERALD_TIME
#define EMERALD_TIME

#define EMERALD_CLOCK_FILE     "/d/Emerald/sys/global/clock"
#define EMERALD_SCHEDULER_FILE "/d/Emerald/sys/global/scheduler"
#define TIME_ERRORS            "time_errors"

#define EMERALD_MINUTE      EMERALD_CLOCK_FILE->query_minute()
#define EMERALD_HOUR        EMERALD_CLOCK_FILE->query_hour()
#define EMERALD_QUARTER     EMERALD_CLOCK_FILE->query_quarter()
#define EMERALD_DAY         EMERALD_CLOCK_FILE->query_day()
#define EMERALD_MONTH       EMERALD_CLOCK_FILE->query_month()
#define EMERALD_YEAR        EMERALD_CLOCK_FILE->query_year()

/* Get a string describing the standard Emerald time (early/mid/late quarter) */
#define EMERALD_TIME_STRING \
    EMERALD_CLOCK_FILE->query_time_string(0)

#define EMERALD_TIME_STRING_VBFC \
    ("@@query_general_time_string:" + EMERALD_CLOCK_FILE + "@@")

/* Get a string describing the exact time (hours and minutes) */
#define EMERALD_EXACT_TIME_STRING \
    EMERALD_CLOCK_FILE->query_time_string(1)

#define EMERALD_EXACT_TIME_STRING_VBFC \
    ("@@query_exact_time_string:" + EMERALD_CLOCK_FILE + "@@")

/* Emerald time passes at a 6:1 ratio relative to real time */
#define TIME_RATE   6

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR   60
#define HOURS_IN_DAY      20
#define DAYS_IN_MONTH     30
#define MONTHS_IN_YEAR    10

#define FIRST_QUARTER     0
#define SECOND_QUARTER    5
#define THIRD_QUARTER     10
#define FOURTH_QUARTER    15

/*
 * Name:        SCHEDULE_EVENT
 * Description: Use this to register a callback to a particular object at a
 *              given Emerald time.
 * Arguments:   object ob - the object responsible for the event.  If this
 *                          object is no longer around at the registered event
 *                          time, the callback will not occur.
 *              function func - The function to call to start the event.
 *              int year   - The year the event should start
 *              int month  - The month the event should start
 *              int day    - The day the event should start
 *              int hour   - The hour the event should start
 *              int minute - The minute the event should start
 * 
 *              Note: Any of the time arguments can be set to -1, meaning
 *                    that the particular time value is unspecified, and
 *                    the next appropriate time will be used.
 *
 * Returns:     An id value which can be used to unschedule the event BEFORE
 *              IT HAPPENS.  THIS ID SHOULD NOT BE USED AFTER THE EVENT HAS
 *              STARTED since it may be reused for a new event.
 *
 * Examples:
 *              SCHEDULE_EVENT(this_object(), start_event, 2, 4, 8, 0, 0);
 *              will cause the start_event function to be called at midnight
 *              on the eighth day of the fourth month of the second year.
 *
 *              SCHEDULE_EVENT(this_object(), start_event, -1, -1, 3, 2, 0);
 *              will cause the start_event function to be called at 02:00
 *              on the third of the month (this month if we haven't already
 *              passed the appropriate time; next month if we have)
 */
#define SCHEDULE_EVENT(ob, func, year, month, day, hour, minute) \
    EMERALD_SCHEDULER_FILE->schedule(ob, func, year, month, day, hour, minute)

/*
 * Name:        UNSCHEDULE_EVENT
 * Description: Cancel a scheduled event.
 * Arguments:   int id - the event id as returned by SCHEDULE_EVENT.  See the
 *                       warnings about event ids above.
 */
#define UNSCHEDULE_EVENT(id) \
    EMERALD_SCHEDULER_FILE->unschedule(id)

/*
 * Use this to register an object with the clock.  The object will then
 * have update_time() called in it whenever the clock updates the
 * the time (every Emerald minute).
 */
#define REGISTER_FOR_TIME_UPDATES(ob) (EMERALD_CLOCK_FILE->register(ob))

#endif
