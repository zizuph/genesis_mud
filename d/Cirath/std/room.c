/*
 * Cirath standard room.
 *
 */
inherit "/std/room";

#include "/d/Cirath/defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

public int    time_func(string arg);

private object clock = find_object(CLOCK);

/*
 * Function name:    create_room()
 * Description  :    Creates the room. This function is called first, and
 *                   all components needed in the room should be added here.
 */
void
create_room()
{
}

void
init()
{
    ::init();
    add_action(time_func, "time");
}

string tod() { return clock->query_time_of_day(); }
string qstime() 
{ 
    string r;

    switch(clock->query_hour())
    {
    case 0:
	r = "midnight";
	break;
    case 1:
	r = "one in the night";
	break;
    case 2:
	r = "two in the night";
	break;
    case 3:
	r = "three in the night";
	break;
    case 4:
	r = "four in the night";
	break;
    case 5:
	r = "five in the morning";
	break;
    case 6:
	r = "six in the morning";
	break;
    case 7:
	r = "seven in the morning";
	break;
    case 8:
	r = "eight in the morning";
	break;
    case 9:
	r = "nine in the day";
	break;
    case 10:
	r = "ten in the day";
	break;
    case 11:
	r = "eleven in the day";
	break;
    case 12:
	r = "noon";
	break;
    case 13:
	r = "one in the afternoon";
	break;
    case 14:
	r = "two in the afternoon";
	break;
    case 15:
	r = "three in the afternoon";
	break;
    case 16:
	r = "four in the afternoon";
	break;
    case 17:
	r = "five in the afternoon";
	break;
    case 18:
	r = "six in the evening";
	break;
    case 19:
	r = "seven in the evening";
	break;
    case 20:
	r = "eight in the evening";
	break;
    case 21:
	r = "nine in the night";
	break;
    case 22:
	r = "ten in the night";
	break;
    case 23:
	r = "eleven in the night";
	break;
    case 24:
	r = "midnight";
	break;
    default:
	r = "ERROR IN CLOCK, PLEASE REPORT TO LIEGE OF CIRATH";
	break;
    }

    return r; 
}

public int
time_func(string str)
{
    int     day;
    string  year;
    string  phase_s;

    if (strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
	return 0;
    }

    day   = (int)CLOCK->query_day();
    phase_s = CLOCK->query_phase_s();
    year  = (string)CLOCK->query_year_name(CLOCK->query_year());

    if (this_object()->query_prop(ROOM_I_INSIDE))
    {
      write("You guess it is " + tod() + " on the " + LANG_WORD(day) +
	  " day of the month of " + phase_s + " in the year of " + year +
	  " in the hundred and eighty third Kings Age" +
	  " now, but since you are inside and cannot study the sky, " +
	  "you cannot estimate the time more precisely.\n");
    return 1;
  }

  write("It is about " + qstime() + " on the " + LANG_WORD(day) +
	" day of the " + phase_s + " in the year of " + year +
	" in the hundred and eighty third Kings Age.\n");
  tell_room(this_object(), QCTNAME(this_player()) + " studies the sky, " +
	    "trying to decide what time it is.\n", this_player());
  return 1;
}

