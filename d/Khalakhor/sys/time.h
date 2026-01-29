/*
 *   Khalakhor time defines
 */
#ifndef _KHALAKHOR_TIME_
#define _KHALAKHOR_TIME_

// Number of Khalakhor seconds that pass in 1 second of real time
#define TIMECONST       4.0

// Some conversion defines.  Remember t is in seconds.
#define REAL2KHALTIME(t)    (itof(t) * TIMECONST)
#define KHAL2REALTIME(t)    (itof(t) / TIMECONST)

// Seconds in a minute
#define SECONDS             60
// Minutes in an hour
#define MINUTES             60
// Hours in a day
#define HOURS               24
// Days in a month
#define DAYS                28
// Months in a year
#define MONTHS              12

//  The actual ticking of the clock... for sanity's sake we only
//  keep track of minutes, seconds would be too much of a drain.
#define TICK  (itof(SECONDS) / TIMECONST)

// A shortcut to the actual clock object
#define CLOCK  "/d/Khalakhor/sys/global/clock"


#define STARTING_YEAR  201

#define MONTH_NAMES ({"Faoilteach", "Gearran", "Mart", "Ghiblinn", \
        "Ceitean", "Og-Mhios", "Iuchar", "Lunasdal", "Sultainn", \
        "Damhar", "Samhainn", "Dudlachd"})

#define GOBLIN_MONTHS ({"Garg-Mhios", "Farmad-Mhios", "Mas-Mhios", \
        "Amadan-Mhios", "Marbh-Mhios", "Grannda-Mhios", "Grod-Mhios", \
        "Airc-Mhios", "Sealg-Mhios", "Ord-Mhios", "Naraich-Mhios", \
        "Dorcha-Mhios"})
#define GOBLIN_YEAR_DIFF   14

#define ELVEN_MONTHS ({"Geall", "Eolas", "Cianail", "Iriosal", \
        "Ionnsaich", "Feith", "Dearbh", "Socair", \
        "Measail", "Pailteas", "Samhach", "Duin"})
#define ELVEN_YEAR_DIFF 3269

#endif
