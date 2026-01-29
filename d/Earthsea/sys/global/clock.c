#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types
#pragma no_shadow

#include "/d/Earthsea/sys/time.h"

#include <language.h>

static private string *days = DAY_NAMES;
static private string *months = MONTH_NAMES;
static private int diddle;

nomask int
query_time()
{
    return (time() + TIME_OFFSET) * TIME_RATE + diddle;
}

nomask int
query_second()
{
    return query_time() % SECONDS_IN_MINUTE;
}

nomask int
query_minute()
{
    return query_time() / SECONDS_IN_MINUTE % MINUTES_IN_HOUR;
}

nomask int
query_hour()
{
    return query_time() / SECONDS_IN_MINUTE / MINUTES_IN_HOUR % HOURS_IN_DAY;
}

nomask int
query_day()
{
    return query_time() / SECONDS_IN_MINUTE / MINUTES_IN_HOUR /
                          HOURS_IN_DAY % DAYS_IN_MONTH;
}

nomask int
query_month()
{
    return query_time() / SECONDS_IN_MINUTE / MINUTES_IN_HOUR /
                          HOURS_IN_DAY / DAYS_IN_MONTH % MONTHS_IN_YEAR;
}

nomask string
query_month_string()
{
    return months[query_month()];
}

nomask int
query_year()
{
    return query_time() / SECONDS_IN_MINUTE / MINUTES_IN_HOUR / 
                          HOURS_IN_DAY / DAYS_IN_MONTH / MONTHS_IN_YEAR;
}

nomask int
query_day_of_week()
{
    return query_day() % DAYS_IN_WEEK;
}

nomask string
query_day_of_week_string()
{
    return days[query_day_of_week()];
}

nomask int *
query_date_arr()
{
    return ({ 
              query_year(),
              query_month(),
              query_day(),
              query_hour(),
              query_minute(),
	      query_second(),
           });
}

nomask string
query_time_string()
{
    int min;

    return query_hour() + ":" +
        (((min = query_minute()) < 10) ? "0" : "") + min;
}

nomask string
query_date_string()
{
    return query_day_of_week_string() + " the " + LANG_WORD(query_day()) + 
        " of " + query_month_string() + ", " + query_year();
}

nomask int
seconds_until_time(int year,
                   int month,
                   int day,
                   int hour,
                   int minute,
                   int second)
{
    int t, 
        clock_year   = query_year(), 
        clock_month  = query_month(),
        clock_day    = query_day(),
        clock_hour   = query_hour(),
        clock_minute = query_minute(),
        clock_second = query_second();

    if (second < 0)
    {
        second = clock_second;
    }

    if (minute < 0)
    {
        if (second < clock_second)
        {
            minute = clock_minute + 1;
        }
        else
        {
            minute = clock_minute;
        }
    }

    if (hour < 0)
    {
        if (minute < clock_minute)
        {
            hour = clock_hour + 1;
        }
        else
        {
            hour = clock_hour;
        }
    }

    if (day < 0)
    {
        if (hour < clock_hour)
        {
            day = clock_day + 1;
        }
        else
        {
            day = clock_day;
        }
    }

    if (month < 0)
    {
        if (day < clock_day)
        {
            month = clock_month + 1;
        }
        else
        {
            month = clock_month;
        }
    }

    if (year < 0)
    {
        if (month < clock_month)
        {
            year = clock_year + 1;
        }
        else
        {
            year = clock_year;
        }
    }

    t += year * MONTHS_IN_YEAR * DAYS_IN_MONTH * HOURS_IN_DAY *
        MINUTES_IN_HOUR * SECONDS_IN_MINUTE;

    t += month * DAYS_IN_MONTH * HOURS_IN_DAY * MINUTES_IN_HOUR *
        SECONDS_IN_MINUTE;

    t += day * HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;

    t += hour * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;

    t += minute * SECONDS_IN_MINUTE;

    t += second;

    return (t - query_time()) / TIME_RATE;
}

void
diddle_time(int t)
{
    diddle += t;
}
