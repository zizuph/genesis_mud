#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types
#pragma no_shadow

#include "/d/Emerald/sys/time.h"

#include <language.h>

#define SAVE_TIME 1800

#ifdef SAVE_TIME
#define SAVE_FILE "/d/Emerald/log/time"
#endif

private int minute;
private int hour;
private int day;
private int month;
private int year;

static private object *registered = ({});

#ifdef SAVE_TIME
static private int save_time;
#endif

nomask int
query_minute()
{
    return minute;
}

nomask int
query_hour()
{
    return hour;
}

nomask int
query_quarter()
{
    return (query_hour() / (HOURS_IN_DAY / 4)) + 1;
}

nomask int
query_day()
{
    return day;
}

nomask int
query_month()
{
    return month;
}

nomask int
query_year()
{
    return year;
}

nomask string
query_time_string(int exact)
{
    int m;

    if (exact)
    {
        return query_hour() + ":" +
            (((m = query_minute()) < 10) ? "0" : "") + m;
    }
    
    return ({ "early", "mid", "late" })[min(2, (query_hour() %
       (HOURS_IN_DAY / 4)) * 3 / 2)] + " in the " + 
        LANG_WORD(query_quarter()) + " quarter";
}

nomask string
query_exact_time_string()
{
    return query_time_string(1);
}

nomask string
query_standard_time_string()
{
    return query_time_string(0);
}

nomask string
query_date_string()
{
}

static nomask int
update_time(object ob)
{
    string err;

    if (!ob)
    {
        return 0;
    }

    if (strlen(err = catch(ob->update_time())))
    {
        log_file(TIME_ERRORS, "Error in update_time (" + ctime(time()) + 
            ": " + file_name(ob) + "\n" + err);
        return 0;
    }

    return 1;
}

static nomask void
increment_time()
{
    if (++minute >= MINUTES_IN_HOUR)
    {
        minute = 0;

        if (++hour >= HOURS_IN_DAY)
        {
           hour = 0;

           if (++day > DAYS_IN_MONTH)
           {
              day = 1;

              if (++month > MONTHS_IN_YEAR)
              {
                  month = 1;
                  year++;
              }
           }
        }
    }

#ifdef SAVE_TIME
    if ((save_time += 60 / TIME_RATE) > SAVE_TIME)
    {
        setuid();
        seteuid(getuid());

        save_time = 0;
        save_object(SAVE_FILE);
    }
#endif

    registered = filter(registered, update_time);
}

nomask void
create()
{
    float interval = 60.0 / itof(TIME_RATE);

#ifdef SAVE_TIME
    setuid();
    seteuid(getuid());
    restore_object(SAVE_FILE);
#else
    minute = time() * TIME_RATE / SECONDS_IN_MINUTE;
    hour   = minute / MINUTES_IN_HOUR;
    day    = hour / HOURS_IN_DAY;
    month  = day / DAYS_IN_MONTH;
    year   = month / MONTHS_IN_YEAR;

    minute = minute % MINUTES_IN_HOUR;
    hour   = hour   % HOURS_IN_DAY;
    day    = day    % DAYS_IN_MONTH;
    month  = month  % MONTHS_IN_YEAR;
#endif

    set_alarm(interval, interval, increment_time);
}

void
register(object ob)
{
    registered += ({ ob });
}

void
unregister(object ob)
{
    registered -= ({ ob });
}

#ifdef SAVE_TIME
void
remove_object()
{
    setuid();
    seteuid(getuid());
    save_object(SAVE_FILE);
    destruct();
}
#endif
