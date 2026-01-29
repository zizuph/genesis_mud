/*
 *  A file to be included if you want to make it possible for mortals
 *  to do the command 'time' in the room, and get to see what time it is.
 *
 *  Coded by Lord Elessar Telcontar of Gondor
 *
 *  Revision history:
 *  /Mercade, 30 September 1993, changed for use without /d/Gondor/defs.h
 *  /Mercade, 26 November 1993, added ROOM_I_NO_ME_SUN
 */

#include <macros.h>
#include <stdproperties.h>

#define GONDOR_CLOCK "/d/Gondor/elessar/lib/clock"
/*
 * This file doesn't include /d/Gondor/defs.h for it might cause
 * problems if other domains include this file. I hope those domains
 * will not define GONDOR_BSN and GONDOR_SAY *grin*
 *
 * /Mercade, 30 September 1993
 */
#define GONDOR_BSN(x) break_string(x, 75) + "\n"
#define GONDOR_SAY(x) say( ({                                    \
    GONDOR_BSN(this_player()->query_name() + x),                 \
    GONDOR_BSN("The " + this_player()->query_nonmet_name() + x), \
    GONDOR_BSN("Someone" + x) }) )
/*
 * Define this in a outside room to prevent a message about dusk and dawn
 * for it is too dark always. This will also mean you can only estimate the
 * time of day. GONDOR_ prefix added for use with other domains.
 */
#define GONDOR_ROOM_I_NO_ME_SUN "_room_i_no_me_sun"

int
check_time()
{
  int hour, day, month, year;
  object clock;
  string time, shour;

  clock = find_object(GONDOR_CLOCK);
  time = (string)clock->query_time_of_day();
  hour = (int)clock->query_hour();
  if(hour == 12)
  {
    shour = "noon";
  }
  else if (hour == 0)
  {
    shour = "midnight";
  }
  else
  {
    if(hour > 12)
    {
      hour -= 12;
    }
    shour = hour + " o'clock in the " + time;
  }

  if (this_object()->query_prop(ROOM_I_INSIDE))
  {
    write(GONDOR_BSN("You guess it is " + time +
      " now, but since you are inside and cannot study the sky, " +
      "you cannot estimate the time more precisely."));
    return 1;
  }
  if (this_object()->query_prop(GONDOR_ROOM_I_NO_ME_SUN))
  {
    write(GONDOR_BSN("You guess it is " + time +
      " now, but due to the darkness of the sky you cannot estimate the " +
      "time more precisely."));
    return 1;
  }

  day = (int)clock->query_day();
  month = (int)clock->query_month();
  year = (int)clock->query_year();

  write(GONDOR_BSN("It is about " + shour + " of day " +
    day + ", month " + month + " in the year " + year + "."));
  GONDOR_SAY(" studies the sky, trying to decide what time it is.");
  return 1;
}

void
init()
{
    ::init();

    add_action("check_time", "time");
}

string
tod()
{
  return ((string)find_object(GONDOR_CLOCK)->query_time_of_day());
}

int
qhour()
{
  int time;

  time = (int)find_object(GONDOR_CLOCK)->query_hour();
  return (time ? time : 12);
}


string
qstime()
{
  int hour;
  object clock;
  string time, shour;

  clock = find_object(GONDOR_CLOCK);
  time = (string)clock->query_time_of_day();
  hour = (int)clock->query_hour();
  if(hour == 12)
  {
    shour = "noon";
  }
  else if (hour == 0)
  {
    shour = "midnight";
  }
  else
  {
    if(hour > 12)
    {
      hour -= 12;
    }
    shour = hour + " o'clock in the " + time;
  }

  return shour;
}

/*
 * Just to keep it tidy.
 */
#undef GONDOR_BSN
#undef GONDOR_SAY
#undef GONDOR_CLOCK
#undef GONDOR_ROOM_I_NO_ME_SUN
