/*
 * Faerun clock.
 * Modifications made from Lucius clock.c
 * See the notes below.
 */

/*
 * Changes
 * -------
 * Date       Who        What
 * --------------------------------------------------------------
 * 2004-03-26 Mozart     Copied Lucius clock /w/lucius/open/clock
 * 2004-03-27 Mozart     Removed
 *                           Timezones, Clouds, Quarters (15 mins)
 *                       Added
 *                          year_types mapping for text representation
 *                                     of years
 *                       Changed
 *                          query_year to give text descs as well
 * 2004-03-28 Mozart     Added
 *                          part_of_day mapping for night,morning,day,evening
 *                          query_day_part
 * 2004-03-29 Mozart     Added
 *                          Special time calcs for special days
 *                          Shieldmeet that occurs once every fourth year
 *                          is a full RL day long
 *                          Other special days are a half RL day long
 *                       Removed
 *                          query_moon_phase, query_am
 *                          part_of_day mapping
 *                       Changed
 *                          query_day_part: switch instead of mapping
 *                          time calculations updated for 10 day weeks
 *                          and 3 week months
 * 2004-04-03 Lucius     Changed
 *                 Special time calcs and workings of various
 *                 functions to better facilitate them.
 * 2004-04-06 Mozart     Changed
 *                          Special day constants were wrong
 *                          Julian set to julian = 1 as default
 * 2004-04-09 Lucius     Added
 *                 Special day initialization so that
 *                 time factoring will be correct on a reset.
 * 2016-06-08 Finwe     Cleaned up code
 *                      Changed query_time_room_desc() so it calls
 *                          query_part_of_day() for description
 * 2016-06-08 Finwe     Added Horizon code
 * 2016-06-25 Finwe     Extended day length fro 4 hrs in realtime to 6 hrs.
 *                          Change was made in clock.h to 900.
 *                      Updated hour descriptions 
 */


/*
 * Real-Life Time Calcs:
 *
 *  1 Min  =  60 secs.
 * 15 Mins = 900 secs.
 * 
 *  1 Hour = 60 Mins  =  3,600 secs.
 *  1 Day  = 24 Hours = 86,400 secs.
 *
 *  1 Week   = 7 Days    =    604,800 secs.
 *  1 Month  = 4 Weeks   =  2,419,200 secs.
 *  1 Year   = 12 Months = 29,030,400 secs.
 */  
/*
 * FaerunTime Calcs:
 *
 *  1 Faerun-day  = 24 Faerun-hours = 4 rl hours = 240 rl mins = 14,400 rl secs
 *  1 Faerun-hour = 10 rl mins = 600 rl secs.
 *  1 Faerun-min  = 10 rl secs.
 *
 *  1 Faerun-week   =  10 Faerun-days   =  144,000 rl secs = 40.0 rl hours.
 *  1 Faerun-month  =  3 Faerun-weeks  =   432,000 rl secs = 5.0  rl days.
 *  1 Faerun-season =  3 Faerun-months = 1,296,000 rl secs = 15.0 rl days.
 *  1 Faerun-year   = 12 Faerun-months = 5,184,000 rl secs = 60.0 rl days.
 */
/* CLOCK NOTES:
 *
 * The clock runs on an hour scale.  It does not do seconds or minutes.
 * Such granularity is not necessary and would be too large a drag on
 * resources.
 *
 * The clock is self-contained and is configurable.
 * It runs in a point a to point b timeslice.
 * Meaning, there is a start and reset point to most values.
 * This handles clock resets, it does not continue on to infinity
 * although doing so could easily be done by commenting out the year
 * reset check.
 *
 * All defines are located in faerun_clock.h and only the clock should
 * #include it. A separate define should be created for inclusion of
 * other files to query the clock (i.e. faerun_time.h).
 *
 * The clock itself does not check if a room is indoor or outdoor, any code you
 * use should check for that itself and return appropriate information.
 */
#pragma no_inherit
#pragma no_clone
#pragma no_shadow
#pragma save_binary
#pragma strict_types

#include <language.h>
#include "clock.h"


/* Prototype function declarations. */
private void stop_clock(void);
private varargs void start_clock(float factor);
public varargs string query_time_room_desc(int mil, int full);
/*
 * This HAS to be mixed to prevent errors as this is
 * a nested array and you'll get type errors otherwise.
 */
// A julian date counter to track special days easier.
private int julian;
// Denotes whether this is a special day or not.
private int special_day;
// Contains all the clock variables.
private mixed *faeruntime;
// The alarm-id for the clock's heartbeat.
private static int ticker_id;
// Just an array that holds pointers to event-needing objects.
private static mixed *events;

/*
 * There is no reason to save these.
 * It should be faster to initialize then to save/load to/from disk.
 * Never use defined arrays/mappings inside functions, it's horribly inefficint.
 */
private static  mapping season_types = SEASON_TYPES,
                special_days = SPECIAL_DAYS,
                year_types = YEAR_TYPES,
                month_types = MONTH_TYPES,
                common_month_types = COMMON_MONTH_TYPES,
                day_types = DAY_TYPES;

/* Don't need people shadowing our clock. */
public int
query_prevent_shadow(void)  { return 1; }

/********************************************************************
 * The various clock query functions
 */

/*
 * The current hour.
 * 24hr format by default, specify 'std' argument for 12hr.
 */
public varargs int
query_hour(int std)
{
    int hour = HOUR;

    return (std ? (hour > 12 ? hour - 12 : hour) : hour);
}

/*
 * The current day of the month / week.
 * Argument: desc:
 *     int 0 - return the day number of the current month.
 *     int 1 - return textform of the current day of the month.
 *     int 2 - return the day name of the current week.
 *      int 3 - return the day number of the current year (1-365)
 */
public varargs mixed 
query_day(int desc)
{
    int day = DAY;

    switch(desc)
    {
    case 1:
    return LANG_WORD(day);
    case 2:
    return day_types[day % WEEK_LENGTH];
    case 3:
    return julian;
    default:
    return day;
    }
}

/*
 * The current week.
 * Argument: desc:
 *     int 0 - return what week it is in decimal form.
 *     int 1 - return the textform of the current week.
 *     int 2 - return a small string indication what Tenday it is.
 */
public varargs mixed
query_week(int desc)
{
    int week = (query_day() / (WEEK_LENGTH + 1)) + 1;

    switch(desc)
    {
    case 1:
    return LANG_WORD(week);
    case 2:
    return capitalize(LANG_WORD(week)) + " Tenday";
    default:
    return week;
    }
}

/*
 * The current month.
 * Argument: desc - return the name of the month
 *     int 0 - return what week it is in decimal form.
 *     int 1 - return the textform of the current week.
 *     int 2 - return the common name for the month.
 */
public varargs mixed
query_month(int desc)
{
    int month = MONTH;

        switch(desc)
    {
    case 1:
    return month_types[month];
    case 2:
    return common_month_types[month];
    default:
    return month;
    }
}

/*
 * The current season.
 * Argument: desc - return a textual season name.
 */
public varargs mixed
query_season(int desc)
{
    int season = SEASON;

    return (desc ? season_types[season][0] : season);
}

/*
 * The current year.
 * desc 0 - return the current year
 * desc 1 - return the name of the current year
 * desc 2 - return full name of the current year
 */
public varargs mixed
query_year(int desc)
{
    int year = YEAR;

    switch(desc)
    {
    case 1:
    return year_types[year];
    case 2:
    return year_types[year] + ", " + year + " DR";
    default:
    return year;
    }
}

/*
 * Give a composite long-form date string.
 */
public string
query_date(void)
{
    return sprintf("%s, %s %d, %d",
    query_day(2), query_month(1), query_day(), query_year());
}

/*
 * Is it night?
 * Results are timeshifted and affected by season.
 */
public int
query_night(void)
{
    int hour = query_hour();

    return ((hour >= SUN_DOWN) || (hour < SUN_UP));
}

/*
 * Returns what part of the day it is
 */
public string
query_part_of_day(void)
{/*
  * Changed descriptions to be more inline with FR names
  * - Finwe June 2016
  */
/*
    switch(query_hour())
    {
    case 1..3:
        return "late night";        // 12am- 3am 
    case 4..7:
        return "early morning";     //  4am- 7am 
    case 8..11:
        return "morning";           //  8am-11am 
    case 12:
        return "noon";              // Noon      
    case 13..17:
        return "afternoon";         //  1pm- 5pm 
    case 18..21:
        return "evening";           //  6pm- 9pm 
    case 22..24:
        return "night";             // 10pm-12am 
    default:
        return "day";
    }
*/

    switch(query_hour())
    {
        case 1..3:
            return "moondark";          // 1am - 3am
        case 4:
            return "night's end";       // 4am
        case 5:
            return "dawn";              // 5am
        case 6..8:
            return "early morning";     // 6am - 8am
        case 9..11:
            return "morning";           // 9am - 11am
        case 12:
            return "highsun";           // 12pm noon
        case 13..16:
            return "afternoon";         // 1pm - 4pm
        case 17..21:
            return "evening";           // 5pm - 9pm
        case 22..23:
            return "night";             // 10pm - 11pm
        case 24:
            return "midnight";          // 12am midnight
        default:
            return "day";
    }

}

/*
 * Returns light type in the part of the day
 */
public string
query_light_type(void)
{
    switch(query_hour())
    {
    case 1..3:
        return "starlight";                 /* 12am- 3am */
    case 4..7:
        return "early morning light";       /*  4am- 7am */
    case 8..11:
        return "gentle, morning sunlight";  /*  8am-11am */ 
    case 12:
        return "bright sunlight";           /* Noon      */
    case 13..17:
        return "blazing sunlight";          /*  1pm- 5pm */
    case 18..21:
        return "evening sunlight";          /*  6pm- 9pm */
    case 22..24:
        return "moonlight";                 /* 10pm-12am */
    default:
    return "daylight";
    }
}


/*
 * Return 12hr time format by default.
 * 24hr time format if specify 'mil' argument.
 */
public varargs string
query_time(int mil)
{
    string time = "";
    int hour = query_hour();

    if (!mil && hour > 12)
    {
        hour -= 12;
    }

    if (mil && hour < 10)
    {
        time += "0";
    }

    time += hour;

    return time;
}

/*
 * Return a 'fancy text' descriptive time output.
 * 12hr time by default, 24hr time if 'mil' argument specified.
 * Results are timeshifted.
 */

// revised version 
public varargs string
query_time_desc(int mil, int full)
{
    int hour = query_hour();
    string hour_str, time_str;


    if (!mil && hour > 12)
    {
        hour -= 12;
    }

    time_str = "It is around ";
    switch(hour)
    {
        case 12:
        hour_str = (query_night() ? "midnight" : "highsun");
        time_str += hour_str + ", on";
        break;
        
    case 24:
        time_str += "midnight, in";
    break;
        
    default:
        time_str += hour + " o'clock in the " + query_part_of_day();
        break;
    }
/*
    if (!full)
    {
        return time_str + ".";
    }
    else 
*/
if (special_day)
    {
        time_str += ", " + special_days[julian][SD_DESC];
    }
    else
    {
        time_str += ", the "+ query_day(1) + " day of "+ query_month(1);
    }

    return time_str += ", in " + query_year() + " DR";
}

/*
 * Returns 1 if it is a special day
 */
public int
is_special_day(void)
{
    if(special_day)
        return 1;
    return 0;
}

/*
 * Returns the name of the spcial day.
 */
public string
query_special_day(void)
{
    if (special_day)
        return special_days[julian][SD_DESC];
    return "";
}

/*
 * Return a 'fancy text' descrioption of the horizon
 */
public varargs string query_horizon()
{
    int hour = query_hour();
    string hour_str, horizon_str;

    horizon_str = "It is where the sky meets the earth. ";

// set rising sun, stars, etc.
    switch(query_hour())
    {
    case 1..3:
        horizon_str += "Stars dust the edge of the horizon while the " +
        "moon slowly rises.";
        break;
    case 4..7:
        horizon_str += "Streaks of pink, orange, and magenta fill the " +
        "eastern horizon as the sun slowing rises.";
        break;
    case 8..11:
        horizon_str += "Puffy clouds drift from the horizon in the " +
        "early morning sky.";
        break;
    case 12:
        horizon_str += "The horizon is a white line in the distance " +
        "in the mid-day light.";
        break;
    case 13..17:
        horizon_str += "The horizon is blue like the rest of the sky.";
        break;
    case 18..21:
        horizon_str += "As the sun sets in the west, the horizon is " +
        "painted gold, yellow, and orange.";
        break;
    case 22..24:
        horizon_str += "The sky is dark with stars twinkling above " +
        "and along the horizon.";
        break;
    default:
        horizon_str += "daytime.";
        break;
    }

    return horizon_str;
}


/*
// Original clock
public varargs string
query_time_desc(int mil, int full)
{
    int hour = query_hour();
    string hour_str, time_str;

    if (!mil && hour > 12)
    {
        hour -= 12;
    }

    switch(hour)
    {
    case 12:
    hour_str = (query_night() ? "midnight" : "noon");
        break;
        
    case 24:
        hour_str = "midnight";
    break;
        
    default:
        hour_str = LANG_WNUM(hour);
        break;
    }

    time_str = "It is around " + hour_str + " in the " +
      query_part_of_day();

    if (!full)
    {
    return time_str + ".";
    }
    else if (special_day)
    {
    time_str += ", " + special_days[julian][SD_DESC];
    }
    else
    {
    time_str += ", the "+ query_day(1) + " of "+ query_month(1);
    }

    return time_str + " in the " + query_year(2) + ".";
}
*/


/*
 * Return a 'fancy text' descriptive time output.
 * 12hr time by default, 24hr time if 'mil' argument specified.
 * Results are timeshifted.
 */
public varargs string query_time_room_desc(int mil, int full)
{
    int hour = query_hour();
    string hour_str, time_str;
    

    if (!mil && hour > 12)
    {
        hour -= 12;
    }

    time_str = "It is ";

// set rising sun, stars, etc.
    switch(query_hour())
    {
    case 1..3:
        time_str += query_part_of_day() + ". A light dusting of stars " +
        "twinkle in the sky. The moon slowly moves in the night sky, bathing " +
        "the land in moonlight.";
        break;
    case 4..7:
        time_str += query_part_of_day() + ", and the sun is rising in the " +
        "east. It peeks over the horizon, bathing the sky in streaks of red, " +
        "pink, magenta, and orange.";
        break;
    case 8..11:
        time_str += query_part_of_day() + ". The sun begins to warm the land " +
        "as it moves through the sky.";
        break;
    case 12:
        time_str += query_part_of_day() + ". The sun is at its peak, filling " +
        "the sky with hot light.";
        break;
    case 13..17:
        time_str += query_part_of_day() + ". The sun is beating down, " +
        "filling the sky with bright light.";
        break;
    case 18..21:
        time_str += query_part_of_day() + ". The sun is setting in the " +
        "west, slowly sinking in the horizon. It paints the sky with " +
        "orange, red, and yellow colors.";
        break;
    case 22..24:
        time_str += query_part_of_day() + ". The moon begins to rise in " +
        "the sky. Stars begin to dot the night sky.";
        break;
    default:
        time_str += "daytime.";
        break;
    }

    return time_str;
}


/********************************************************************
 * The event handling semantics
 */
/*
 * Register an event.
 */
public void
add_event(mixed ob)
{
    if (member_array(ob, events) == -1)
    events += ({ ob });
}

/*
 * Remove a registered event.
 */
public void
rem_event(mixed ob)    { events -= ob; }

/*
 * What events are waiting?
 */
public void
query_events(void)    { return secure_var(events); }

/*
 * Run through events
 * Events that wish to remain running should return a 'true' value.
 * Otherwise, false '0' should be returned so it gets filtered out.
 */
private void
clock_events(void)    { events = filter(events, &->mudtime_event()); }

/********************************************************************
 * The clock mechanics 
 */
/*
 * Advance the clock.
 */
private void
tick_tock(void)
{
    /* Increment the hour. */
    if (HOUR < R_HOUR)
    {
        HOUR += 1;
    clock_events();
    return;
    }
    else
    {
        HOUR = B_HOUR;
    clock_events();
    }

    /* There is where a new day would begin, we need to intercept
     * special occasion days as time is handled differently then. */
    if (special_days[++julian])
    {
    if (!special_day ||
        (special_day && (YEAR == SHIELD_MEET_YEAR)))
    {
        special_day++;
        stop_clock();
        start_clock(special_days[julian][SD_FACTOR]);
        return;
    }
    }

    if (special_day)
    {
    /* Shieldmeet does not count as a calander day. */
    if (special_day == 2)
        julian--;

    /* Reset the clock to normal timeflow. */
    special_day = 0;
    stop_clock();
    start_clock();
    }

    /* Update what day it is. */
    if (DAY < R_DAY)
    {
    DAY += 1;
    return;
    }
    else
    {
        DAY = B_DAY;
    }

    /* Save every faerun-day so we don't lose too much in a crash. */
    save_object(CLOCK_SAVE);

    /* Update what month we are in. */
    if (MONTH < R_MONTH)
    {
        MONTH += 1;
    SEASON = MONTH % NUM_SEASONS;
        return;
    }
    else
    {
    SEASON = MONTH % NUM_SEASONS;
        MONTH  = B_MONTH;
    }

    /* Reset the julian date back to the first day of the year. */
    julian = 1;

    /* Update the current Faerun year. */
    if (YEAR < R_YEAR)
    {
        YEAR += 1;
        return;
    }
    else
    {
        YEAR = B_YEAR;
    }
}

/*
 * Query if the clock is truly running.
 */
public mixed
query_clock_alarm(void)
{
    if (!ticker_id)
    return "The clock has not been started.\n";
    else
    return sprintf("%O", get_alarm(ticker_id));
}

/*
 * Start the clock running.
 */
private varargs void
start_clock(float factor = 1.0)
{
    float interval;

    // Check if the clock is already started ?
    if (ticker_id)
        return;

    interval  = TIME_INTERVAL * factor;
    ticker_id = set_alarm(interval, interval, tick_tock);
}

/*
 * Stop a running clock.
 */
private void
stop_clock(void)
{
    if (!ticker_id)
        return;

    catch(rename(CLOCK_SAVE, CLOCK_SAVE + ".bak"));
    save_object(CLOCK_SAVE);
    remove_alarm(ticker_id);
    ticker_id = 0;
}

/*
 * Unload the clock.
 */
public void
remove_object(void)
{
    stop_clock();
    destruct();
}

/*
 * Load the clock.
 */
static void
create(void)
{
    setuid();
    seteuid(getuid());

    // Initialize the clock's values.
    julian = 1; 
    special_day = 0; 
    events = ({ });
    faeruntime = ({ B_HOUR, B_DAY, B_MONTH, B_YEAR, B_SEASON });
    restore_object(CLOCK_SAVE);

    /* We ended during a 'special' day so we need to
     * initialize the clock with the correct time factor. */
    if (special_day && special_days[julian])
        start_clock(special_days[julian][SD_FACTOR]);
    else
        start_clock();
}

/*****************************************************************************/
/* DEBUG STUFF */

/*
 * Arugments are optional, if you specify '0' in any of the slots
 * the current value will be unchanged.  If you specify an invalid
 * value, an error code will be returned letting you know which arg
 * is wrong. */
public varargs int
set_date(int year, int month, int day, int hour)
{
    int nr_of_days, shield_meet_day;

    switch(year)
    {
        case 0: 
            break;
        case B_YEAR..R_YEAR: 
            YEAR = year; 
            break;
        default: 
            return 1;
    }

    switch(month)
    {
        case 0:
            break;
        case 1..12:
            MONTH = month; 
            break;
        default:
            return 2;
    }

    switch(day)
    {
        case 0:
            break;
        case 1..30:
            DAY = day; 
            break;
        default:
            return 3;
    }

    switch(hour)
    {
        case 0:
            break;
        case 1..24:
            HOUR = hour; 
            break;
        default:
            return 4;
    }

    // This is to update the 'julian' date.
    nr_of_days = (MONTH - 1) * 30;
    shield_meet_day = ((YEAR == SHIELD_MEET_YEAR) ? 1 : 0);
    
    switch(MONTH)
    {
        case 1:
            julian = DAY;
            break;
        case 2..4:
            julian = nr_of_days + 1 + DAY;
            break;
        case 5..7:
            julian = nr_of_days + 2 + DAY;
            break;
        case 8..9:
            julian = nr_of_days + 3 + DAY + shield_meet_day;
            break;
        case 10..11:
            julian = nr_of_days + 4 + DAY + shield_meet_day;
            break;
        case 12:
            julian = nr_of_days + 5 + DAY + shield_meet_day;
            break;
    }

    /* If we changed the date during a 'special' day,
     * then reset back to normal time. 
     */
    if (special_day)
    {
        special_day = 0;
        stop_clock();
        start_clock();
    }

    return 0;
}
