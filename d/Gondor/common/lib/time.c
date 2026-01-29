/*
 *  /d/Gondor/common/lib/time.c
 *
 *  A file to be included if you want to make it possible for mortals
 *  to do the command 'time' in the room, and get to see what time it is.
 *
 *  This file is inherited by the time code. If you want to have time
 *  in your room, you should add the following line to your code:
 *
 *  #include "/d/Gondor/common/lib/time.h"
 *
 *  Coded by Lord Elessar Telcontar of Gondor
 *
 *  Revision history:
 *  /Mercade, 30 September 1993, changed for use without /d/Gondor/defs.h
 *  /Mercade, 26 November 1993, added ROOM_I_NO_ME_SUN
 *  /Elessar, 5 June 1995, added the function int rq_stage(),
 *           for querying the current Ring Quest stage.
 */
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

#define GONDOR_CLOCK            ("/d/Gondor/common/obj/clock")
/*
 * This file doesn't include /d/Gondor/defs.h for it might cause
 * problems if other domains include this file. I hope those domains
 * will not define GONDOR_BSN and GONDOR_SAY *grin*
 *
 * /Mercade, 30 September 1993
 */
#define GONDOR_BSN(x)           (break_string(x, 75) + "\n")
#define GONDOR_SAY(x)           say( ({                          \
    GONDOR_BSN(this_player()->query_name() + x),                 \
    GONDOR_BSN("The " + this_player()->query_nonmet_name() + x), \
    "" }) )
/*
 * Define this in a outside room to prevent a message about dusk and dawn
 * for it is too dark always. This will also mean you can only estimate the
 * time of day. GONDOR_ prefix added for use with other domains.
 */
#define GONDOR_ROOM_I_NO_ME_SUN ("_room_i_no_me_sun")

string
qstime()
{
    int    hour;
    string time;

    hour = (int)GONDOR_CLOCK->query_hour();

    if (hour == 12)
    {
	return "noon";
    }

    if (hour == 0)
    {
	return "midnight";
    }

    if (hour > 12)
    {
	hour -= 12;
    }

    time = (string)GONDOR_CLOCK->query_time_of_day();

    return (hour + " o'clock in the " + time);
}

string
tod()
{
    return ((string)GONDOR_CLOCK->query_time_of_day());
}

int
rq_stage()
{
    return ((int)GONDOR_CLOCK->query_rq_stage());
}

string
qsmoon()
{
    return ((string)GONDOR_CLOCK->query_moon());
}

int
check_time(string str)
{
    int     day,
            year;
    string  month_s;

    if (strlen(str))
    {
	notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    if (this_object()->query_prop(GONDOR_ROOM_I_NO_ME_SUN))
    {
	write(GONDOR_BSN("You guess it is " + tod() +
	    " now, but due to the darkness of the sky you cannot estimate " +
	    "the time more precisely."));
	return 1;
    }

    day   = (int)GONDOR_CLOCK->query_day();
    month_s = GONDOR_CLOCK->query_month_s();
    year  = (int)GONDOR_CLOCK->query_year();

    if (this_object()->query_prop(ROOM_I_INSIDE))
    {
	write(GONDOR_BSN("You guess it is " + tod() + " on the " + LANG_WORD(day)
          + " day of the month of " + month_s + " in the year " + year
          + " now, but since you are " + "inside and cannot study the sky, "
          + "you cannot estimate the time more precisely."));
	return 1;
    }

    write(GONDOR_BSN("It is about " + qstime() + " on the " + LANG_WORD(day) +
	" day of the month of " + month_s + " in the year " + year + "."));
    GONDOR_SAY(" studies the sky, trying to decide what time it is.");
    return 1;
}

int
qhour()
{
    int time;

    time = (int)GONDOR_CLOCK->query_hour();

    return (time ? time : 12);
}

/*
 * Just to keep it tidy.
 */
#undef GONDOR_BSN
#undef GONDOR_SAY
#undef GONDOR_CLOCK
#undef GONDOR_ROOM_I_NO_ME_SUN
