// Revision history
// April 18/2000 by Boron - Added 1 year to the time period
//                          so it starts in 347 and not 348, this
//                          is to allow two years of peace before
//                          each war (we include 348)
///////////// Notes for the time module:
//
// Each year takes 6 rl days days

#ifndef _CLOCK_
#define _CLOCK_

#ifndef CLOCK
#define CLOCK "/d/Krynn/common/clock/clock"
#endif

#define REALTOGAME       2.0 /*2.0*/ /* real seconds to a Krynn minute */
#define SAVE_CLOCK       1800.0      /* Number of seconds between saves */

#define DAYLIGHT         ((gMonths[gMonth - 1][DAYLIGHT_H] * 60 + \
                           gMonths[gMonth - 1][DAYLIGHT_M]) / 2)

#define THE_SUNRISE      (12 * MINUTESTOHOURS - DAYLIGHT)
#define THE_SUNSET       (12 * MINUTESTOHOURS + DAYLIGHT)

/* time/date conversion */
#define MINUTESTOHOURS   60
#define HOURSTODAYS      24
#define DAYSTOMONTHS     30
#define MONTHSTOYEARS    12
#define DAYSTOYEARS      360

#define TOTAL_MINUTE(y,m,d,h,mi)   (y * 518400 + \
				    (m - 1) * 43200 + \
				    (d - 1) * 1440 + \
				    h * 60 + mi)

/* mobilization of the armies started in spring 348 */
/* time should start here once Ansalon needs it. */
/* We will start here once the warfare module is installed.
 * This is before the first battle of the War of the Lance
 * has been fought.*/
#define START_YEAR       347
#define START_MONTH        1
#define START_DAY          1
#define START_HOUR         0
#define START_MINUTE       0

/* companions set out on Sept. 9th, 351 */
/* for now, we begin time around here
#define START_YEAR       351
#define START_MONTH        7
#define START_DAY          1
#define START_HOUR         0
#define START_MINUTE       0
*/
/* Time should end on the day Neraka falls (March 26th, 352)
 * This is done by default from the time_master, other events
 * can influence the actual ending time though.
 * Check and update /d/Krynn/common/flow/clock.c as well, if you
 * change the start (or end) time!!
 */

#define MONTH_NAME       0  /* The name of the month */
#define SEASON_TYPE      1  /* Winter, Spring, Summer, Autumn */
#define DAYLIGHT_H       2  /* Hours */
#define DAYLIGHT_M       3  /* Minutes */

/* To be used together with query_time() */
/* There can be problems with another include file (/sys/time.h i think) */
/* To be on the safe side, use the definitions with the K prepended. */
#ifndef YEAR
#define YEAR             0
#endif
#ifndef MONTH
#define MONTH            1
#endif
#ifndef DAY
#define DAY              2
#endif
#ifndef HOUR
#define HOUR             3
#endif
#ifndef MINUTE
#define MINUTE           4
#endif
#define KYEAR             0
#define KMONTH            1
#define KDAY              2
#define KHOUR             3
#define KMINUTE           4


#define WINTER           0
#define SPRING           1
#define SUMMER           2
#define AUTUMN           3

#define MONTH_DATA       ({ ({ "Aelmont",   0, 12, 0 }), \
			    ({ "Rannmont",  0, 12, 0 }), \
			    ({ "Mishamont", 1, 12, 0 }), \
			    ({ "Chislmont", 1, 12, 0 }), \
			    ({ "Bran",      1, 12, 0 }), \
			    ({ "Corij",     2, 12, 0 }), \
			    ({ "Argon",     2, 12, 0 }), \
			    ({ "Sirrimont", 2, 12, 0 }), \
			    ({ "Reorxmont", 3, 12, 0 }), \
			    ({ "Hiddumont", 3, 12, 0 }), \
			    ({ "H'rarmont", 3, 12, 0 }), \
			    ({ "Phoenix",   0, 12, 0 }) })

/* Defines for the moons */
#define SOLINARI         "solinari"
#define LUNITARI         "lunitari"
#define NUITARI          "nuitari"
#define SOL_CYCLE        36
#define LUN_CYCLE        28
#define NUI_CYCLE         8
#define CYCLE           ([                                                     \
                            SOLINARI : SOL_CYCLE,                              \
                            LUNITARI : LUN_CYCLE,                              \
                            NUITARI : NUI_CYCLE                                \
                        ])
#define MOON_PHASES     ({                                                     \
                            ({ "new",           "waxing crescent" }),          \
                            ({ "waxing half",   "waxing gibbous"}),            \
                            ({ "full",          "waning gibbous" }),           \
                            ({ "waning half",   "waning crescent" })           \
                        })

/* A few handy functions */
#define GET_MOON_PHASE(x) (CLOCK->query_moon_phase(x))
#define GET_TIME_OUTSIDE (CLOCK->query_time_string_outside())
#define GET_TIME_INSIDE  (CLOCK->query_time_string_inside())
#define GET_TIME         (CLOCK->query_time())
#define GET_SEASON       (CLOCK->query_season())

/* Yet another handy function with a few extra defines */
#define GET_TIME_STRING  (CLOCK->query_estimate_time_of_day_string())
#define MIDNIGHT         "midnight"
#define NIGHT            "night"
#define EARLY_MORNING    "early morning"
#define MORNING          "morning"
#define NOON             "noon"
#define AFTERNOON        "afternoon"
#define EVENING          "evening"

/* Another handy function with a few extra defines */
#define GET_TIMEOFDAY    (CLOCK->query_time_of_day())
#define TOD_DAWN         "dawn"
#define TOD_TWILIGHT     "twilight"
#define TOD_DAY          "day"
#define TOD_NIGHT        "night"

#endif _CLOCK_






