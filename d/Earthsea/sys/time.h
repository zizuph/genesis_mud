#ifndef EARTHSEA_TIME
#define EARTHSEA_TIME

#define EARTHSEA_CLOCK_FILE     "/d/Earthsea/sys/global/clock"
#define EARTHSEA_SCHEDULER_FILE "/d/Earthsea/sys/global/scheduler"

#define EARTHSEA_SECOND      EARTHSEA_CLOCK_FILE->query_second()
#define EARTHSEA_MINUTE      EARTHSEA_CLOCK_FILE->query_minute()
#define EARTHSEA_HOUR        EARTHSEA_CLOCK_FILE->query_hour()
#define EARTHSEA_DAY         EARTHSEA_CLOCK_FILE->query_day()
#define EARTHSEA_MONTH       EARTHSEA_CLOCK_FILE->query_month()
#define EARTHSEA_YEAR        EARTHSEA_CLOCK_FILE->query_year()
#define EARTHSEA_DAY_OF_WEEK EARTHSEA_CLOCK_FILE->query_day_of_week()

#define EARTHSEA_DAY_OF_WEEK_STRING \
    EARTHSEA_CLOCK_FILE->query_day_of_week_string()
#define EARTHSEA_MONTH_STRING \
    EARTHSEA_CLOCK_FILE->query_month_string()
#define EARTHSEA_TIME_STRING \
    EARTHSEA_CLOCK_FILE->query_time_string()
#define EARTHSEA_DATE_STRING \
    EARTHSEA_CLOCK_FILE->query_date_string()

#define TIME_RATE   6

#define TIME_OFFSET 0

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR   60
#define HOURS_IN_DAY      24
#define DAYS_IN_MONTH     30
#define DAYS_IN_WEEK       7
#define MONTHS_IN_YEAR    12

#define DAY_NAMES ({ "Sunday", "Monday", "Tuesday", "Wednesday", \
                     "Thursday", "Friday", "Saturday" })

#define MONTH_NAMES ({ "January",   \
                       "February",  \
                       "March",     \
                       "April",     \
                       "May",       \
                       "June",      \
                       "July",      \
                       "August",    \
                       "September", \
                       "October",   \
                       "November",  \
                       "December",  \
		     })

#define SCHEDULE_EVENT(ob, func, year, month, day, hour, minute) \
    EARTHSEA_SCHEDULER_FILE->schedule(ob, func, year, month, day, hour, minute)

#define UNSCHEDULE_EVENT(id) \
    EARTHSEA_SCHEDULER_FILE->unschedule(id)

#endif
