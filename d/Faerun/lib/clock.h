/*
 * These are defines that are used by the global clock.
 */

/*
 * Changed clock so that time now starts in 1484
 * -- Finwe, June 6, 2016
 */

#ifndef __FAERUN_CLOCK_DEFS__
#define __FAERUN_CLOCK_DEFS__

/* Where to save the clock info. */
#define CLOCK_SAVE "/d/Faerun/private/faerun_clock"

/* The float value for the alarm ticker.
 * This should be the value you derive for 1 mud hour
 */
#define TIME_INTERVAL 900.0

/* Shortcuts to the values named */
#define HOUR    faeruntime[0]
#define DAY     faeruntime[1]
#define MONTH   faeruntime[2]
#define YEAR    faeruntime[3]
#define SEASON  faeruntime[4]

/* Base / Beginning values for the clock */
#define B_HOUR    1
#define B_DAY     1
#define B_MONTH   1
#define B_YEAR    1484
#define B_SEASON  0

/* These are the reset limits, when once reached, set back to base
 * Only variables that need it are represented.
 * Set the values to the last 'real'
 */
#define R_HOUR    24
#define R_DAY     30
#define R_MONTH   12
#define R_YEAR    1487

/* Season: ({ "season name", sunrise hour, sunset hour }) */
#define SEASON_TYPES ([        \
    0: ({ "winter", 8, 17 }),  \
    1: ({ "spring", 6, 19 }),  \
    2: ({ "summer", 5, 20 }),  \
    3: ({ "fall",   7, 18 }), ])

#define NUM_SEASONS 4

/* The daytime hours. */
#define SUN_UP    season_types[SEASON][1]
#define SUN_DOWN  season_types[SEASON][2]

#define WEEK_LENGTH  10

/* Day descriptors (day_types[DAY % WEEK_LENGTH]) */
#define DAY_TYPES ([  \
    0: "Tenth day",   \
    1: "First day",   \
    2: "Second day",  \
    3: "Third day",   \
    4: "Fourth day",  \
    5: "Fifth day",   \
    6: "Sixth day",   \
    7: "Seventh day", \
    8: "Eighth day",  \
    9: "Ninth day",  \
   10: "Tenth day",  ])

/* Month descriptors */
#define MONTH_TYPES ([ \
    1: "Hammer",       \
    2: "Alturiak",     \
    3: "Ches",         \
    4: "Tarsakh",      \
    5: "Mirtul",       \
    6: "Kythorn",      \
    7: "Flamerule",    \
    8: "Elasis",       \
    9: "Eleint",       \
   10: "Marpenoth",    \
   11: "Uktar",        \
   12: "Nightal",     ])

#define COMMON_MONTH_TYPES ([ \
    1: "Deepwinter",              \
    2: "The Claw of Winter",      \
    3: "The Claw of the Sunsets", \
    4: "The Claw of the Storms",  \
    5: "The Melting",             \
    6: "The Time of Flowers",     \
    7: "Summertide",              \
    8: "Highsun",                 \
    9: "The Fading",              \
   10: "Leaffall",                \
   11: "The Rotting",             \
   12: "The Drawing Down",     ])

/* Year descriptors */
#define YEAR_TYPES ([ \
    1484: "Year of the Awakened Sleepers",    \
    1485: "Year of the Iron Dwarf's Vengeance",   \
    1486: "Year of the Nether Mountain Scrolls",   \
    1487: "Year of the Rune Lords Triumphant", ])

/* Special days (special_day[julian])
 * There are 365 days to a year (shieldmeet does not count)
 *
 * special_days = ([
 * 	(int)julian day :
 * 		(mixed *)({ (string)Description, (float)Time Factor }), ])
 */
#define SPECIAL_DAYS ([ \
     31: ({         "Midwinter", 3.0 }),  \
    122: ({        "Greengrass", 3.0 }),  \
    213: ({         "Midsummer", 3.0 }),  \
    214: ({        "Shieldmeet", 6.0 }),  \
    274: ({   "Highharvesttide", 3.0 }),  \
    335: ({ "Feast of the Moon", 3.0 }), ])

#define SD_DESC    0
#define SD_FACTOR  1

#define SHIELD_MEET_YEAR 1484

#endif __FAERUN_CLOCK_DEFS__
