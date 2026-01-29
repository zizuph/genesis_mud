/* This is the Clock for the Cirath domain.
 * Its a mayor reconstruction of the Clock from
 * the Swordcoast domain. Instead of months we have
 * 3 phases of the year. The year is 372 days.
 * The Dark Sun setting has 375 days but I neaded
 * to be able to devide it by 6 so I changed it.
 * The names of the years runs in a cycle of 2
 * arrays of names. You can find the yearnames in
 * the year_names.c file.
 *
 * Athas has 2 moons aswell, but I left that out.
 *
 * Azazel 2002
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/d/Cirath/obj/year_names.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Cirath/defs.h"

#undef DEBUG 1
#ifdef DEBUG
#define DEBUG_MSG(x) find_player("azazel")->catch_msg("###clock### "+x+"\n");
#else
#define DEBUG_MSG(X)
#endif

/* seconds to a game minute */
#define REALTOGAME    10.0           
/* seconds between saves of clock */
#define SAVETIME   1800.0
#define CLOCK_DATA MASTER

/* Define the time in which we are */
/* Need to find a proper timeline for Cirath */
#define CIR_START_YEAR		1
#define CIR_START_PHASE		1
#define CIR_START_DAY		1

#define CIR_END_YEAR		77
#define CIR_END_PHASE		3
#define CIR_END_DAY		124

/* High sun must peak before Low sun */
#define SUN_HIGH_PEAK_PHASE 1     /* High sun peaks 63/1 */
#define SUN_HIGH_PEAK_DAY   63
#define SUN_LOW_PEAK_PHASE 3     /* Low sun peaks 1/3 */
#define SUN_LOW_PEAK_DAY   1

#define DAWN_HIGH 4           /* Dawn at 5:00 and dusk at 23 */
#define DUSK_HIGH 22
#define DAWN_LOW 6           /* Dawn at 7:00 and dusk at 21 */
#define DUSK_LOW 20
#define DAWN_LENGTH 1           /* Length in hours */
#define DUSK_LENGTH 1

#define MINUTES 60
#define HOURS   24
#define DAYS    125
// If you change the number of phases, you MUST change the query_phase_s()
// function, or else things will not always work correctly.
#define PHASES 3
#define CIR_TA_DAYS(y,p,d)	((((y)*PHASES)+(p))*DAYS+(d))

/*
 *      Prototypes:
 */
varargs int     query_dawn(int p, int d);
varargs int     query_dusk(int p, int d);
        int     convert_phases_days(int p, int d);
        void    dump();
        int     query_midnight();
        string  query_time();
        string  query_date(); 
        void    dawn();
        void    dusk();
	void    change_hour(int h);
        void    midnight();

/*
 * Global variables:
 */
private object  Cirath_Master;

private int     Phase,
                Day,  
                Year,
                Hours,
                Minutes;

static int     High_Midth,
               Low_Midth,
               High_Midth2,
               High_Start,
               Low_Start;

/* SYSTEM ROUTINES */
 
public void
create_object()
{
    int     ta_days;

    set_short("the master clock of Cirath");

    High_Midth = convert_phases_days(SUN_HIGH_PEAK_PHASE,
  	SUN_HIGH_PEAK_DAY);
    Low_Midth = convert_phases_days(SUN_LOW_PEAK_PHASE,
        SUN_LOW_PEAK_DAY);

    High_Midth2 = High_Midth + PHASES * DAYS;
    High_Start = ((Low_Midth + High_Midth2)/2 + High_Midth2)/2;
    Low_Start = ((Low_Midth + High_Midth)/2 + Low_Midth)/2;

    seteuid(getuid(this_object()));
    restore_object(CLOCK_DATA);

    ta_days = CIR_TA_DAYS(Year, Phase, Day);
    if ((ta_days > (CIR_TA_DAYS(CIR_END_YEAR, CIR_END_PHASE, CIR_END_DAY))) ||
        (ta_days < (CIR_TA_DAYS(CIR_START_YEAR, CIR_START_PHASE, CIR_START_DAY))))
    {
        Year  = CIR_START_YEAR;
        Phase = CIR_START_PHASE;
        Day   = CIR_START_DAY;
    }

    set_alarm(REALTOGAME, REALTOGAME, "upd_time");
    set_alarm(0.0, SAVETIME, "dump");
}

public void
upd_time()
{
    Minutes += 5;
    if (Minutes > (MINUTES-1))
    {
        Minutes = 0;
        Hours += 1;
        if (Hours == HOURS) 
	    midnight();
        else if (Hours == query_dawn()) 
	    dawn();
        else if (Hours == query_dusk()) 
	    dusk();
        if (Hours > HOURS)
        {
            Hours = 1;
            Day += 1;
            if (Day > DAYS)
            { 
                Day = 1;
                Phase += 1;
                if (Phase > PHASES)
                {
                    Phase = 1;
                    Year += 1;
                }
            }
        }
	change_hour(Hours);
    }
}

public void
dump()
{
    object  dummy;

    save_object(CLOCK_DATA);
}

public int
convert_hours_minutes(int h, int p)
{
    if (h == HOURS) 
	h = 0;
    return (h*MINUTES + p) * REALTOGAME;
}

public int
convert_phases_days(int p, int d)
{
    return (p - 1) * DAYS + d;
}

/* QUERY ROUTINES */

public varargs string
query_phase_s(int val)
{
    int test;
     
    if (!val) 
	test = Phase;
    else 
	test = val;

    switch (test)
    {
    case 1:
        return "High Sun";
    case 2:
        return "Descending Sun";
    case 3:
        return "Ascending Sun";
    default:
        return "error";
    }
}

public int
query_phase()
{ 
    return Phase;
}

public int
query_day()
{ 
    return Day;
}

public int
query_year()
{
    return Year;
}

public string
query_date()
{ 
    return Day + "/" + Phase + "/" + Year;
}

public string
query_date_b()
{ 
    return "Today is the " + Day + " of the " + Phase +
       " in the year of the " + query_year_name(Year) +
       ". In the hundred and eighty third Kings Age."+
       "Current game time: " + query_time()+"\n";
}

public string
query_date_s()
{ 
    return query_phase_s() + " " + Day + ", " + Year;
}

public int
query_24_hour()
{ 
    if (Hours == HOURS) 
	return 0;
    return Hours;
}
 
public int
query_minute() 
{ 
    return Minutes;
}

public int
query_12_hour()
{
    if (Hours > HOURS/2) 
	return Hours - HOURS/2;
    return Hours;
}

public int
query_hour()
{ 
    return query_24_hour();
}

public int
query_am()
{ 
    return (Hours < HOURS/2) || ((Hours == HOURS) && Minutes);
}

public int
query_pm()
{ 
    return (Hours > HOURS/2) || ((Hours == HOURS/2) && Minutes);
}

public int
query_midnight()
{ 
    return (Hours == HOURS) && !Minutes;
}

public int
query_noon()
{
    return (Hours == HOURS/2) && !Minutes;
}

public string
query_am_pm()
{
    if (query_am()) 
	return "am";
    else if (query_pm()) 
	return "pm";
    else if(query_noon()) 
	return "noon";
    else 
	return "midnight";
}

public string
query_time()
{
    int     hour;
    string  tmp;

    hour = query_24_hour();
    if (hour < 10) 
	tmp = "0";
    tmp = tmp + hour + ":";
    if (Minutes < 10) 
	tmp += "0";
    tmp = tmp + Minutes;
    return tmp;
}

public string
query_time_24()
{
    return query_time();
}

public string
query_time_12()
{
    int     hour;
    string  tmp;

    hour = query_12_hour();
    if (hour < 10) 
	tmp = "0";
    tmp = tmp + hour + ":";
    if (Minutes < 10) 
	tmp += "0";
    tmp = tmp + Minutes + " " + query_am_pm();
    return tmp;
}


/* Returns the hour of dawn */

public varargs int
query_dawn(int p, int d)
{
    int     now;

    if (!p)
	p = Phase;
    if (!d)
	d = Day;
    now = convert_phases_days(p, d);

    if (now < High_Midth) 
	now += PHASES * DAYS;
    
    if (now < High_Midth)
    {
	now -= Low_Midth;
	return DAWN_LOW - (now * (DAWN_HIGH - DAWN_LOW + 1)) /
           (Low_Midth - High_Midth + 1);
    }
    else 
    {
	now -= Low_Midth;
	return DAWN_LOW + (now * (DAWN_HIGH - DAWN_LOW + 1)) /
	    (High_Midth2 - Low_Midth + 1);
    }
}

/* Returns the hour of dusk */

public varargs int
query_dusk(int p, int d)
{
    int     now;

    if (!p)
	p = Phase;
    if (!d)
	d = Day;
    now = convert_phases_days(p, d);
    if (now < Low_Midth) 
	now += PHASES * DAYS;
    
    if (now < High_Midth) 
    {
	now -= Low_Midth;
	return DUSK_LOW + (now * (DUSK_HIGH - DUSK_LOW + 1)) /
	    (High_Midth - Low_Midth + 1);
    }
    else 
    {
	now -= Low_Midth;
	return DUSK_LOW - (now * (DUSK_LOW - DUSK_HIGH + 1)) /
	    (High_Midth2 - Low_Midth + 1);
    }
}

public string
query_time_of_day(int p, int d, int h)
{
    int     dusk,
            dawn;

    if (!p) 
	p = Phase;
    if (!d)
	d = Day;
    if (!h)
	h = Hours;

    dawn = query_dawn(p, d);
    dusk = query_dusk(p, d);

    if (h < dawn) 
	return "night";
    else if (h < dawn + DAWN_LENGTH) 
	return "early morning";
    else if (h < HOURS/2) 
	return "morning";
    else if (h == HOURS/2) 
	return "noon";
    else if (h < dusk) 
	return "afternoon";
    else if (h < dusk + DUSK_LENGTH) 
	return "evening";
    return "night";
}

public int
query_in_cirath(object player)
{
    object  room;
    string  domain;

    if (!objectp(player) || !objectp(room = environment(player)))
	return 0;
    domain = room->query_domain();

    if (member_array(domain, ({ "Cirath" }) ) > -1)
	return 1;
    return 0;
}

private void
dawn()
{
    object *player = users();
    int     n = -1;

    while (++n < sizeof(player))
    {
        if (query_in_cirath(player[n]) &&
	    !environment(player[n])->query_prop(ROOM_I_INSIDE))
	        tell_object(player[n],
		    "The crimson sun rises over the horizont, and" +
		    " its scorching rays yet again burns Athas as" +
		    " a new day begins.\n");
    }
    seteuid(getuid());
    Cirath_Master->sunrise();
}

private void
dusk()
{
    object *player = users();
    int     n = -1;

    while (++n < sizeof(player))
    {
        if (query_in_cirath(player[n]) &&
	    !environment(player[n])->query_prop(ROOM_I_INSIDE))
	    tell_object(player[n], 
		"The crimson sun sets in the west leaving Athas" +
		" and it's inhabitants to the cold of night and" +
		" the perils of the darkness.\n");
    }

    Cirath_Master->sunset();
}


private void
change_hour(int h)
{
    Cirath_Master->change_hour(h);
}

public void
midnight()
{
    Cirath_Master->midnight();
}

public void
remove_object()
{
    dump();
    ::remove_object();
}
