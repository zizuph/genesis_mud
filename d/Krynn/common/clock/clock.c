/* The Krynn clock. */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "clock.h"
#include TIME_FLOW

#define SAVE_FILE        "/d/Krynn/common/clock/clocksave"

int gMonth,
    gDay,
    gYear,
    gHour,
    gMinute,
    gTwilight,
    gNight;

string *gMasters = ({}),
       *gFullMoons = ({});

static int gSunRise, gSunSet, gTotal, gSizeEvents;
static mixed gMonths = MONTH_DATA; 
static mixed gEvents = ({});
    
/* prototype */
void check_moon();
public void save_clock();
static void check_sun();
static void check_events();
static void do_dusk_info();
static void do_dawn_info();
static void do_twilight_day_info();
static void do_twilight_night_info();
static void update_clock();
static int filter_krynn(object pl);
static int filter_krynn_underwater(object pl);
public int query_total_minute();
public string query_moon_phase(string moon);
public string * twilight_day_string();
public string * twilight_night_string();
public string * dusk_string();
public string * dawn_string();

/*
 * Function name: reset_clock
 * Description:   Reset the clock
 */
public void
reset_clock()
{
    gYear = START_YEAR;
    gMonth = START_MONTH;
    gDay = START_DAY;
    gHour = START_HOUR;
    gMinute = START_MINUTE;
    gNight = 1;

    gTotal = query_total_minute();

    save_clock();
}

public void
create_object()
{
    int when;

    set_name("clock");
    add_name("Krynn clock");
    set_adj("Krynn");
    add_adj("krynn");
    set_short("Krynn clock");
    set_long("This is the clock of Krynn.\n");

    seteuid(getuid(this_object()));

    restore_object(SAVE_FILE);

    gSunRise = THE_SUNRISE;
    gSunSet = THE_SUNSET;

    gTotal = query_total_minute();

    set_alarm(REALTOGAME, REALTOGAME, update_clock);
}

/*
 * Function name: update_clock
 * Description:   This function is called every REALTOGAME second.
 *                It makes the clock tick.
 */
static void
update_clock()
{
    gMinute += 1;
    gTotal += 1;

//    find_player("rastlin")->catch_msg(sprintf("QUERY: %d TOTAL: %d Year: %d Month: %d Day: %d Hour: %d Min: %d\n", query_total_minute(), gTotal, gYear, gMonth, gDay, gHour, gMinute));

    if (gMinute >= MINUTESTOHOURS)
    {
        gMinute = 0;
        gHour += 1;

        if (gHour >=  HOURSTODAYS)
        {
            gHour = 0;
            gDay += 1;

            if (gDay > DAYSTOMONTHS)
            {
                gDay = 1;
                gMonth += 1;

                if (gMonth > MONTHSTOYEARS)
                {
                    gMonth = 1;
                    gYear += 1;
                }

                gSunRise = THE_SUNRISE;
                gSunSet = THE_SUNSET;
            }
        }
    }

    check_sun();
    check_moon();
    
    if (gSizeEvents && (gTotal == gEvents[0][2]))
        check_events();
}

/*
 * Function name: query_time_of_day
 * Returns:       The time of day.
 */
public string
query_time_of_day()
{
    switch (gTwilight | gNight)
    {
        case 0 : return TOD_DAY;
                 break;
        case 1 : return TOD_NIGHT;
                 break;
        case 2 : return TOD_TWILIGHT;
                 break;
        case 3 : return TOD_DAWN;
                 break;
    }    
}

/*
 * Function name: check_events
 * Description:   Check and trigger events
 */
static void
check_events()
{
    while (gSizeEvents && (gEvents[0][2] == gTotal))
    {
        INTERRUPT_PERIOD(gEvents[0][0], gEvents[0][1]);
        gEvents = exclude_array(gEvents, 0, 0);
	gSizeEvents--;
    }
}

/*
 * Function name: check_sun
 * Description:   Check and see if the sun is about to rise or sink.
 *                If so, give out a message about it.
 */
static void
check_sun()
{
    int now = gHour * 60 + gMinute;

    if ((gSunSet - 60) == now)
    {
        do_twilight_night_info();
        gTwilight = 2;
        return;
    }

    if ((gSunRise - 60) == now)
    {
        do_twilight_day_info();
        gTwilight = 2;
        return;
    }

    if (gSunRise == now)
    {
        do_dawn_info();
        gNight = 0;
        gTwilight = 0;
        save_clock();
    }
    else if (gSunSet == now)
    {
        do_dusk_info();
        gNight = 1;
        gTwilight = 0;
        save_clock();
    }
}

/*
 * Function name:   check_moon
 * Description:     Called from update_clock to check if we should print any
 *                  messages concerning the moons.
 * Arguments:       None
 * Returns:         Nothing
 */
void
check_moon()
{
    object *players;
    string *gNew, *moons, message, message2;
    
    moons = filter(m_indexes(CYCLE), &operator(==)(,"full") @ 
            &query_moon_phase());
    gNew  = filter(moons, &operator(<)(,0) @ &member_array(,gFullMoons));
    
    if (!sizeof(gNew))
        return;
    
    switch(sizeof(gFullMoons = moons))
    {
        case 1: // One full moon
        message = "";
        message2 = "";
            break;
            
        case 2: // Two full moons
        message = "";
        message2 = "";
            break;
            
        case 3: // Night of the Eye
        message = "Your sensitivity to magic notices the air suddenly " +
                  "charge with mystical energy, as if a portentous event " +
                  "had begun.\n";
        message2 = "Your sensitivity to magic notices the air suddenly " +
                  "charge with mystical energy as the three moons of magic - " +
                  "Solinari, Lunitari, and Nuitari - align in high sanction, " +
                  "the momentous conjunction event know as the Night of the " +
                  "Eye.\n";
            break;
            
        default: // No full moons
        message = "";
        message2 = "";
            break;
    }
    
    if (!strlen(message))
        return;
    
    /* Filters all the players in krynn */
    players = filter(users(), &filter_krynn());
    
    foreach(object player: players)
    {
        /* Add conditions here */
        if (player->query_guild_member("Wizards of High Sorcery"))
            player->catch_msg(message2);
        else if (player->query_skill(SS_SPELLCRAFT) > 70)
            player->catch_msg(message);
    }
} /* check_moon */

public int
query_sunlight_level()
{
    int now = gHour * 60 + gMinute;

    if (now < gSunRise || now > gSunSet)
      return 0;
    
    return ((now - gSunRise) * (gSunSet - now) * (MAX_SUNLIGHT) / 129600);
}

/*
 * Function name: remove_object
 * Description:   Remove the clock from the game, save it first.
 */
public void
remove_object()
{
    save_clock();

    ::remove_object();
}

/*
 * Function name: save_clock
 * Description:   Save the clock
 */
public void
save_clock()
{
    save_object(SAVE_FILE);
}

/*
 * Function name: add_master
 * Description:   Add a master object to the clock. The object will
 *                be called at Dawn, Dusk, Night and Day.
 *                The function that get called is:
 *                  public object *clock(string tod, object *pl);
 *                'clock' should return those players that _GOT_ a message.
 * Arguments:     master - The filename to the object, with complete path.
 * Returns:       True if everything went ok, false otherwise.
 */
public int
add_master(string master)
{
    if (member_array(master, gMasters) != -1)
        return 0;

    gMasters += ({ master });

    save_clock();

    return 1;
}

/*
 * Function name: remove_master
 * Description:   Remove a master object from the clock
 * Arguments:     master - The master file to remove
 * Returns:       True if everything went ok, false otherwise
 */
public int
remove_master(string master)
{
    if (member_array(master, gMasters) == -1)
        return 0;

    gMasters -= ({ master });

    save_clock();

    return 1;
}

/*
 * Function name: add_event
 * Description:   Add an event that will trigger the time_master
 *                at a certain Krynn time.
 * Arguments:     thread - The name of the thread in the time_master
 *                event - The name of the event in the time_master
 *                time - The time the event will happen
 * Returns:       True if everything went ok, false otherwise.
 */
public int
add_event(string thread, string event, int time)
{
    int size = gSizeEvents;

    while (size--)
        if ((gEvents[size][0] == thread) && (gEvents[size][1] == event))
	    return 0; 

    gEvents += ({ ({ thread, event, time }) });
    gSizeEvents++;

    if (gSizeEvents > 1)
        gEvents = sort_array(gEvents, "sort_func", this_object());

    return 1;
}

/*
 * Function name: remove_event
 * Description:   Remove an event
 * Arguments:     thread - The name of the thread
 *                event - The name of the event
 * Returns:       True if everything went ok, false otherwise
 */
public int
remove_event(string thread, string event)
{
    int size = gSizeEvents;

    while (size--)
        if ((gEvents[size][0] == thread) && (gEvents[size][1] == event))
	{
	    gEvents = exclude_array(gEvents, size, size);
	    gSizeEvents--;
	    return 1;
	}
    return 0;
}

/*
 * Function name: query_night
 * Returns:       True if it is night.
 */
public int
query_night() { return gNight; }

/*
 * Function name: query_twilight
 * Returns:       True if it is twilight.
 */
public int
query_twilight() { return gTwilight; }

/*
 * Function name: query_time
 * Returns:       An array containing the year, month, day, hour and minute.
 */
public int *
query_time()
{
    return ({gYear, gMonth, gDay, gHour, gMinute});
}

/*
 * Function name: query_estimate_time_of_day_string
 * Description:   Estimate the time of day-
 * Returns:       The proper time of day string.
 */
public string
query_estimate_time_of_day_string()
{
    int time = (gHour * MINUTESTOHOURS) + gMinute;

    if (gHour == 0)
        return MIDNIGHT;
    if (gHour < 5)
        return NIGHT;
    if (gHour < 8)
        return EARLY_MORNING;
    if (gHour < 12)
        return MORNING;
    if (gHour == 12)
        return NOON;
    if (gHour < 18)
        return AFTERNOON;
    if (gHour < 22)
        return EVENING;
    return NIGHT;
}

/*
 * Function name: query_time_of_day_string
 * Description:   Get the proper time of day.
 * Returns:       The proper string.
 */
public string
query_time_of_day_string()
{
    if (gHour == 0)
        return "midnight";
    if (gHour == 12)
        return "noon";

    return "" + (gHour % 12) + " o'clock in the " + 
        query_estimate_time_of_day_string();
}

/*
 * Function name: query_month_name
 * Arguments:     val - The month number
 * Returns:       The name of the month
 */
public varargs string
query_month_name(int val = gMonth)
{
    return gMonths[val - 1][MONTH_NAME];
}

/*
 * Function name: query_time_string_outside
 * Description:   Build the string seen when using 'time'
 *                in an outside room.
 * Returns:       The proper string
 */
public string
query_time_string_outside()
{
    return ("It is about " + 
	    query_time_of_day_string() + " on the " +
	    LANG_WORD(gDay) + " day of " + query_month_name() +
	    " in the year " + gYear + " after the Cataclysm.\n");
}

/*
 * Function name: query_time_string_inside
 * Description:   Build the string as seen when using
 *                'time' in an inside room.
 * Returns:       The proper string.
 */
public string
query_time_string_inside()
{
    return ("You guess it is " + query_estimate_time_of_day_string() +
	    " on the " + LANG_WORD(gDay) + " day of " + query_month_name() +
	    " in the year " + gYear + " after the Cataclysm, but since you " +
	    "are inside and cannot study the sky, you cannot estimate the " +
	    "time more precisely.\n");
}

/*
 * Function name: query_date_string
 * Returns:       The date in the form: month/day/year
 */
public string
query_date_string()
{
    return "" + gMonth + "/" + gDay + "/" + gYear;
}

/*
 * Function name: query_time_string
 * Returns:       The current time.
 */
public string
query_time_string()
{
    string tmp = "";

    if (gHour < 10)
        tmp = "0";
    tmp = tmp + gHour + ":";
    if (gMinute < 10)
        tmp = tmp + "0";
    tmp = tmp + gMinute;
    return tmp;
}

/*
 * Function name: query_time12_string
 * Returns:       Returns the time using am/pm
 */
public string
query_time12_string()
{
    string tmp = "";
    int h;

    h = gHour;
    if (h == 0)
        h = 12;
    else
        h %= 12;

    if (gHour < 10)
        tmp = "0";
    tmp = tmp + gHour + ":";
    if (gMinute < 10)
        tmp = tmp + "0";
    tmp = tmp + gMinute;
    if (gHour < 13)
        tmp += "am";
    else
        tmp += "pm";
    return tmp;
}

/*
 * Function name: query_time_date_string
 * Returns:       Returns the time + date.
 */
public string
query_time_date_string()
{
    return query_time_string() + ", " + query_date_string();
}

/*
 * Function name: query_total_minute
 * Returns:       The number of minutes since year 0.
 */
public int
query_total_minute()
{
    return TOTAL_MINUTE(gYear, gMonth, gDay, gHour, gMinute);
}

/*
 * Function name: query_minute
 * Returns:       The current minute.
 */
public int
query_minute()
{
    return gMinute;
}

/*
 * Function name: query_hour
 * Returns:       The cuurent hour.
 */
public int
query_hour()
{
    return gHour;
}

/*
 * Function name: query_day
 * Returns:       The current day.
 */
public int
query_day()
{
    return gDay;
}

/*
 * Function name: query_month
 * Returns:       The current month.
 */
public int
query_month()
{
    return gMonth;
}

/*
 * Function name: query_year
 * Returns:       The current year.
 */
public int
query_year()
{
    return gYear;
}

/*
 * Function name: query_season
 * Returns:       The current season.
 */
public int
query_season()
{
    return gMonths[gMonth - 1][SEASON_TYPE];
}

/*
 * Function name: query_moon_phase
 * Description:   Calculate the phase of the moon
 * Arguments:     moon - The name of the moon.
 * Returns:       The current phase.
 */
public string
query_moon_phase(string moon)
{
    int     days, phase, quarter;
    status  state;
    
    days = gYear * DAYSTOYEARS + gMonth * DAYSTOMONTHS + gDay; 

    /* Change the moon phase at noon (it was previously seen at midnight) */
    if (days > 1 && gHour < 12)
        days--;
    
    /* Get the amount of days in the current cycle */
    phase = days % CYCLE[moon];
    /* Determine which quarter the moon is currently in */
    quarter = phase / (CYCLE[moon] / sizeof(MOON_PHASES));
    /* Determine the amount of days that have passed since the last quarter */
    phase %= (CYCLE[moon] / sizeof(MOON_PHASES));
    
    /* Set if its the first or second moon in the quarter */
    state = (phase >= (CYCLE[moon] / (sizeof(MOON_PHASES) * 2)) ? 1 : 0);
    
    /* Forcing full and new moon to remain longer */
    if (!(quarter % 2) && phase > 1)
        state = (phase > (CYCLE[moon] / (sizeof(MOON_PHASES) * 2)) ? 1 : 0);
    
    return MOON_PHASES[quarter][state];
}

/*
 * Function name: filter_krynn
 * Description:   Check and see if a player is anywhere with
 *                the world of Krynn.
 * Arguments:     pl - The player object
 * Returns:       True, false if not.
 */
static int
filter_krynn(object pl)
{
    object env = environment(pl);

    if (!env || !objectp(env))
        return 0;

    return (!(wildmatch("/d/Krynn/*", file_name(env)) |
              wildmatch("/d/Ansalon/*", file_name(env))) ? 0 :
	      (!(env->query_prop(ROOM_I_INSIDE)) && !(env->query_no_time())));
}

/*
 * Function name: filter_krynn_underwater
 * Description:   Check and see if a player is anywhere with
 *                the world of Krynn underwater.
 * Arguments:     pl - The player object
 * Returns:       True, false if not.
 */
static int
filter_krynn_underwater(object pl)
{
    object env = environment(pl);

    if (!env || !objectp(env))
        return 0;

    return (!(wildmatch("/d/Krynn/*", file_name(env)) |
              wildmatch("/d/Ansalon/*", file_name(env))) ? 0 :
	      ((env->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) && 
              !(env->query_no_time())));
}

/*
 * Function name: do_info
 * Description:   Filter the players, to see who should get the
 *                message.
 * Arguments:     str - The message.
 *                tod - The time of day, using TOD_xxx
 */
static void
do_info(string * str, string tod)
{
    object *oblist, *uwlist, *tmp;
    int i;
    
    i = sizeof(gMasters);
    
    oblist = filter(users(), &filter_krynn());
    uwlist = filter(users(), &filter_krynn_underwater());

    // Remove players underwater from message list.
    oblist -= uwlist;

    /* What does this while loop do??? can't it be done in one go, since you
     * already pass all of oblist to the call_other???? 
     */
    while (i--)
    {
        tmp = call_other(gMasters[i], "clock", tod, oblist);

	if (!pointerp(tmp))
	    tmp = ({ tmp });

	oblist -= tmp;
    }  

    oblist->catch_msg(str[0]);  
    uwlist->catch_msg(str[1]);  
    
    /* Here, all players currently in Krynn should be informed about
     * dawn or dusk (or whatever :), notify people only in outside rooms
     * of course.
     */
}

public void
test2()
{
    add_event("flint", "Enter Solace forest", query_total_minute() + 10);
}

public string *
twilight_day_string()
{
    return ({ "Dawn breaks upon the sky.\n",
        "Light begins to filter down to these watery depths " +
        "as dawn approaches.\n" });
}

static void
do_twilight_day_info()
{
    string * str = twilight_day_string();
    do_info(str, TOD_DAWN);
}

public string *
twilight_night_string()
{
    return ({ "The day seemingly starts to dim.\n", 
        "The watery depths begin to darken as night " +
        "approaches.\n" });
}

static void
do_twilight_night_info()
{
    string * str = twilight_night_string();
    do_info(str, TOD_TWILIGHT);
}

public string *
dawn_string()
{
    return ({ "A new day begins as light touches the land of " +
        "Krynn again.\n", "Light filters down to these watery " +
        "depths as dawn breaks and a new day begins.\n" });
}

static void
do_dawn_info()
{
    string * str = dawn_string();
    do_info(str, TOD_DAY);
}

public string *
dusk_string()
{
    return ({ "Another day ends as the light withdraws from the " +
      "land of Krynn.\n", "Another day ends as the light withdraws " +
      "from these watery depths.\n" });
}

static void
do_dusk_info()
{
    string * str = dusk_string();
    do_info(str, TOD_NIGHT);
}

public int
sort_func(mixed a, mixed b)
{
    return (a[2] == b[2] ? 0 : (a[2] > b[2] ? 1 : -1));
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */








