inherit "/std/room";

#include "/d/Gondor/common/lib/time.h"

#include "/d/Shire/common/include/time.h"

/*
 * This file includes the following:
 *
 * object clock - The Middle Earth central clock object.
 *
 * string tod() - Returns a string telling which time of
 *		  day it is.
 *
 * int qhour()	- Returns which hour it is today.
 *
 */

/*
 * The rest of this file is convenience functions for setting of describing
 * messages for outrooms.
 */

mapping time_desc;

int
qtime()
{
    return (int)find_object(CLOCK)->query_24_hour();
}

int
is_night()
{
    return qtime() >= 21 || qtime() <= 4;
}

int
is_day()
{
    return !is_night();
}

int
query_moon()
{
    return (int)find_object(CLOCK)->query_moon() &&
	   is_night();
}

string
time_of_day()
{
    switch (qtime())
    {
	case EARLY_NIGHT   : return T_EARLY_NIGHT;
	case LATE_NIGHT    : return T_LATE_NIGHT;
	case EARLY_MORNING : return T_EARLY_MORNING;
	case MORNING	   : return T_MORNING;
	case AFTERNOON	   : return T_AFTERNOON;
	case EVENING	   : return T_EVENING;
    }
}

/*
 * Function name:   set_time_desc
 * Arguments:	    The arguments are best explained by some examples:
 *
 *	set_time_desc(
 *	    "night", "It is night in the Trollshaws now.",
 *	    "day",   "It is day time in the Trollshaws now."
 *	);
 *
 *	set_time_desc(
 *	    "early night",	"It is early night now in the forest.",
 *	    "late night",	"It is now quite late in the Trollshaws.",
 *	    "early morning",	"It is early morning in this forest.",
 *	    .
 *	    .
 *	    "late evening",	"It now gets ever more dark.");
 */
varargs
set_time_desc(mixed s, ...)
{
    int i;
    mixed args;

    if (!sizeof(argv) || !stringp(s) || !stringp(argv[0]))
	return;

    args = ({ s }) + argv;

    if (!time_desc)
	time_desc = ([]);

    for (i=0; i<sizeof(args); i+=2)
	time_desc += ([ args[i] : args[i+1] ]);
}

mapping
query_time_desc()
{
    return time_desc;
}

string
time_desc()
{
    string tod = time_of_day();

    if (!time_desc)
	return "It is " + tod + " in the Shire now.";

    if (query_moon() && time_desc[T_MOON] && random(2))
	return time_desc[T_MOON];

    if (time_desc[tod])
	return time_desc[tod];

    if (is_night() && time_desc[T_NIGHT])
	return time_desc[T_NIGHT];

    if (is_day() && time_desc[T_DAY])
	return time_desc[T_DAY];

    return "";
}
