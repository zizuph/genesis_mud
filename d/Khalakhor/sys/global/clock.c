/* File         : /d/Khalakhor/sys/global/clock.c
 * Creator      : Igneous@Genesis
 * Copyright    : Chad Richardson    
 * Date         : March 31 1999         
 * Purpose      : This is the Khalakhor clock
 *                It is how we tell what time it is in Khalakhor
 * Comments     : This is a VERY important piece of code here
 *                in Khalakhor and must always load or there will
 *                be domainwide trouble.
 * Modifications: August 2004 -Igneous
 *                Removed all referances to the weather system.
 */
#pragma no_clone
#pragma save_binary
#pragma no_inherit

#include <language.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/time.h"

#define CLOCK_SAVE "/d/Khalakhor/sys/global/clockdata" 

// Global Vars
private string * Filenames = ({});

private int minute,
hour,
day,
month,
year;

// Prototypes
void    update_time();
void    save_clock();
void    restore_clock();

/* Function name: create()
 * Description  : The create function... we use it to
 *                initalize the clock
 */
void
create()
{
    restore_clock();
    // No year so the save must not have worked.
    if (!year)
    {
	year = STARTING_YEAR;
	month = 1;
	day = 1;
	hour = 1;
	minute = 1;
    }
    if (!pointerp(Filenames))
	Filenames = ({});

    set_alarm(TICK, TICK, update_time);
}

/* Function name: add_time_keeper
 * Description:   adds the filename to the list of files this
 *                object notifies when the hour changes so
 *                thoose files and trigger events.
 * Arguements:    string file: The filename to be added
 */
int
add_time_keeper(string file)
{
    if (!file || !stringp(file))
	return 0;
    if (!pointerp(Filenames) || !sizeof(Filenames))
    {
	Filenames = ({file});
	return 1;
    }
    if (member_array(file, Filenames) != -1)
	return 0;
    Filenames += ({file});
    save_object(CLOCK_SAVE);
    return 1;
}

/* Function name: remove_time_keeper
 * Description:   removes filenames from the time keeper list
 * Arguements:    string file: The filename to be removed
 */
int
remove_time_keeper(string file)
{
    if (!file || !stringp(file))
	return 0;
    if (!pointerp(Filenames) || !sizeof(Filenames))
	return 0;
    if (member_array(file, Filenames) == -1)
	return 0;
    Filenames -= ({file});
    save_object(CLOCK_SAVE);
    return 1;
}

/* Function name: query_time_keeper
 * Description:   returns a list of files which the
 *                clock notifies about the change in
 *                hour
 */
string *
query_time_keeper()
{
    return Filenames;
}

/* Function name: change_hour
 * Description:   Notifies files that the hour has changed
 * Arguements:    int hour: The current hour
 */
void
change_hour(int hour)
{
    int i;
    object ob;

    if (!pointerp(Filenames) || !sizeof(Filenames))
	return;

    i = -1;
    while(++i < sizeof(Filenames))
    {
	catch(call_other(Filenames[i], "??"));
	if (!objectp(ob = find_object(Filenames[i])))
	{
	    setuid(); seteuid(getuid());
	    log_file("clock_error", ctime(time()) + " Failed "+
	      "to load "+ Filenames[i]+">\n");
	    if (remove_time_keeper(Filenames[i]))
		log_file("clock_error", Filenames[i] + " was "+
		  "removed from time keeper array.\n");
	}
	else
	    ob->change_hour(hour);
    }
}


/* Function name: update_time
 * Description  : This function is used to update and increment
 *                the time on this clock.  It also takes care of
 *                changing the weather and any events which are
 *                time based.
 */
void
update_time()
{
    minute += 1;
    if (minute > MINUTES)
    {
	minute = 1;
	hour += 1;
	if (hour > HOURS)
	{
	    hour = 1;
	    day += 1;
	    if (day > DAYS)
	    {
		day = 1;
		month += 1;
		if (month > MONTHS)
		{
		    month = 1;
		    year += 1;
		}
		// Save the clock every new day
		save_clock();
	    }
	    //  After all the time keeping is done notify files 
	    // about the new hour.
	    change_hour(hour);
	}
    }
}

/* Function name: query_minute
 * Returns      : the current minute
 */
int
query_minute()
{
    return minute;
}

/* Function name: query_hour
 * Returns      : the current hour
 */
int
query_hour()
{
    return hour;
}

/* Function name: query_time_of_day
 * Returns      : a description of the current time of day
 */
string
query_time_of_day()
{
    switch(hour)
    {
    case 1..6:
	return "early morning";
    case 7..10:
	return "morning";
    case 11..14:
	return "afternoon";
    case 15..17:
	return "late afternoon";
    case 18..21:
	return "evening";
    case 22..24:
	return "late evening";
    }
}

/* Function name: query_12hour
 * Returns      : the current hour in a 12 hour format
 */
int
query_12hour()
{
    return (hour % 12 == 0 ? 12 : hour % 12);
}

/* Function name: query_day
 * Returns      : the current day
 */
int
query_day()
{
    return day;
}

/* Function name: query_month
 * Returns      : the current month
 */
int
query_month()
{
    return month;
}

/* Function name: query_month_string
 * Description  : The name of the actual month is produced from
 *                this function.  There are 3 calendars in Khalakhor
 *                so we have to figure out which one we are after.
 * Arguments    : int type: 1 for elven caldendar
 *                          0 for the human or common caldendar
 *                         -1 for the goblin caldendar
 * Returns      : the name of the current month
 */
string
query_month_string(int type)
{
    if (!type)
	return MONTH_NAMES[month-1];
    if (type == 1)
	return ELVEN_MONTHS[month-1];
    if (type == -1)
	return GOBLIN_MONTHS[month-1];
}

/* Function name: query_year
 * Returns      : the current common year
 */
int
query_year()
{
    return year;
}

/* Function name: query_year_string()
 * Description  : Since we have 3 different years in Khalakhor
 *                (one for each calendar) we have to figure out
 *                which one we want and produce a string explaining
 *                what year it is.
 * Arguments    : int type: 1 for elven caldendar
 *                          0 for the human or common caldendar
 *                         -1 for the goblin caldendar
 * Returns      : a string containing the current year for the 
 *                appropriate calendar.
 */
string
query_year_string(int type)
{
    if (!type)
	return LANG_WORD(year) +" year after the Fall of Braynt";
    if (type == 1)
	return LANG_WORD(year + ELVEN_YEAR_DIFF) +
	" year after the Birth of Dessidhean";
    if (type == -1)
	return LANG_WORD(year + GOBLIN_YEAR_DIFF) +
	" year after the Second Retreat";
}

/* Function name: describe_the_time
 * Description  : Desccribes to time to a player who checks it
 *                with the check ti/d/Khalakhor/n_speir/clachdun/adminme command.
 * Arguments    : object room: The room in which this_player() is
 *                             checking the time in.
 * Returns      : 1
 */
int
describe_the_time(object room)
{
    string to_write, region;
    int type;

    // Are we able to check the time here?
    if (room->query_prop(ROOM_I_NO_TIME))
	return 0;
    // First figure out what calendar we are using.
    type = this_player()->query_prop(LIVE_I_KHALAKHOR_CALENDAR);

    // You need to see the sun outside to get an accurate
    // hour of the time.
    if (!room->query_prop(ROOM_I_INSIDE))
    {
	to_write = "It is currently "+LANG_WNUM(query_12hour())+" in the "+
	query_time_of_day()+", of the "+LANG_WORD(query_day())+
	" day of "+query_month_string(type)+", in the "+
	query_year_string(type);
    }
    else
    {
	to_write = "You can not accurately tell the time here, but "+
	"you guess that it is sometime during the "+query_time_of_day()+
	" of the "+ LANG_WORD(query_day()) +" day of "+
	query_month_string(type) +", in the "+query_year_string(type); 
    }
    write(to_write + ".\n");
    return 1;
}

/* Function name: remove_object
 * Description  : a clean up function
 */
void
remove_object() 
{
    save_clock();
    destruct();
}

/* Function name: save_clock
 * Description  : saves the clock data.
 */
void
save_clock()
{
    setuid(); seteuid(getuid());
    save_object(CLOCK_SAVE);
}

/* Function name: restore_clock
 * Description  : restores the clock data.
 */
void
restore_clock()
{
    setuid(); seteuid(getuid());
    restore_object(CLOCK_SAVE);
}
