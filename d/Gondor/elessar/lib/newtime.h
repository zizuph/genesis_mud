/*  A file to be included if you want to make it possible for mortals
 *  to do the command 'time' in the room, and get to see what time it is.
 */
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
string time;
object clock;

check_time()
{
  int hour, day, month, year;
  clock = find_object("/d/Gondor/elessar/lib/clock");
  time = clock->query_time_of_day();
  hour = clock->query_hour();
  day = clock->query_day();
  month = clock->query_month();
  year = clock->query_year();
  if (this_object()->query_prop(ROOM_I_INSIDE))
    {
      write("You guess it is "+time+" now, but since you're inside, and can't\n"+
	    "study the sky, you can't estimate the time more precisely.\n");
      return 1;
    }
  write("It is about "+hour+" o'clock in the "+time+" of day "+day+", month "+month+" in the year "+year+".\n");
  say(QCTNAME(this_player())+" studies the sky, trying to decide what time it is.\n",this_player());
  return 1;
}

init()
{
  ::init();
  add_action("check_time","time");
}

tod()
{
  clock = find_object("/d/Gondor/elessar/lib/clock");
  time = clock->query_time_of_day();
  return time;
}

