/*  A file to be included if you want to make it possible for mortals
 *  to do the command 'time' in the room, and get to see what time it is.
 */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

int
check_time(string str)
{
  int hour, day, month, year;
  object clock;
  string time, shour;

  clock = find_object("/d/Gondor/elessar/lib/clock");
  time = (string)clock->query_time_of_day();
  hour = (int)clock->query_hour();
  if(hour == 12) shour = "noon";
  else if (hour == 0) shour = "midnight";
  else
  {
    if(hour > 12)
      hour -= 12;
    shour = hour + " o'clock in the " + time;
  }
  day = (int)clock->query_day();
  month = (int)clock->query_month();
  year = (int)clock->query_year();
  if (this_object()->query_prop(ROOM_I_INSIDE))
  {
    write(BSN("You guess it is " + time + " now, but since you are inside " +
      "and cannot study the sky, you cannot estimate the time " +
      "more precisely."));
    return 1;
  }
  write(BSN("It is about " + shour + " of day " +
    day + ", month " + month + " in the year " + year + "."));
  SAY(" studies the sky, trying to decide what time it is.");
  return 1;
}

string
tod()
{
  return (find_object("/d/Gondor/elessar/lib/clock")->query_time_of_day());
}

int
qhour()
{
  int time;

  time = (int)find_object("/d/Gondor/elessar/lib/clock")->query_hour();

  return (time ? time : 12);
}

