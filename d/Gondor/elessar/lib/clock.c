/*
 *	The master clock of Middle-earth.
 *
 *	/d/Gondor/elessar/lib/clock.c
 *
 *	Modifications made by Elessar from Oct '91 to May '92.
 *
 *	Ring Quest support by Olorin.
 *
 *      This file is obsolete and has been replaced by /d/Gondor/common/obj/clock.c
 *      BUG_MSG will log each call to a function in this object in the "clock" logfile.
 */
#pragma strict_types

inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

#define OBSOLETE 1
#ifdef  OBSOLETE
#define BUG_MSG(x)      bug_msg(x)
#else
#define BUG_MSG
#endif

#undef DEBUG
#ifdef DEBUG
#define DEBUG_MSG(x) find_player("olorin")->catch_msg("###clock### "+x+"\n");
#else
#define DEBUG_MSG(X)
#endif

#define REALTOGAME 2.0           /* seconds to a game minute */
#define SAVETIME 1800.0          /* seconds between saves of clock */
#define CLOCK_DATA "/d/Gondor/elessar/lib/clockdata"

/* Define the time in which we are */
/* Start: September 22nd, 3017 TA, one year before Frodo's 50th birthday */
#define ME_START_YEAR		3017
#define ME_START_MONTH		9
#define ME_START_DAY		22
/* End: March 25h, 3019 TA, Fall of Sauron */
#define ME_END_YEAR		3019
#define ME_END_MONTH		3
#define ME_END_DAY		25

/* Winter must peak before summer */

#define WINTER_PEAK_MONTH 1     /* Winter peaks 12/1 */
#define WINTER_PEAK_DAY   12
#define SUMMER_PEAK_MONTH 7     /* Summer peaks 26/7 */
#define SUMMER_PEAK_DAY   26

#define DARKMOON 3
#define WAXING_CRES 6
#define WAXING_GIB 11
#define FULLMOON 17
#define WANING_GIB 20
#define WANING_CRES 25

#define DAWN_SUMMER 4           /* Dawn at 5:00 and dusk at 21 */
#define DUSK_SUMMER 20
#define DAWN_WINTER 6           /* Dawn at 7:00 and dusk at 19 */
#define DUSK_WINTER 18
#define DAWN_LENGTH 2           /* Length in hours */
#define DUSK_LENGTH 2

#define MINUTES 60
#define HOURS 24
#define DAYS 30
// If you change the number of months, you MUST change the query_month_s()
// function, or else things will not always work correctly.
#define MONTHS 12
#define ME_TA_DAYS(y,m,d)	((((y)*MONTHS)+(m))*DAYS+(d))

/* Ring Quest time definitions */
#define RQ_STAGE_DATE	({ RQ_GANDALF_IN_BAGEND,     ({ 3018,  4, 12, }),\
                           RQ_OSGILIATH_ATTACK,      ({ 3018,  6, 20, }),\
                           RQ_LEFT_HOBBITON,         ({ 3018,  9, 23, }),\
                           RQ_ARRIVED_IN_RIVENDELL,  ({ 3018, 10, 20, }),\
                           RQ_LEFT_RIVENDELL,        ({ 3018, 12, 25, }),\
                           RQ_ARRIVED_IN_LOTHLORIEN, ({ 3019,  1, 16, }),\
                           RQ_LEFT_LOTHLORIEN,       ({ 3019,  2, 16, }),\
                           RQ_LEFT_HENNETH_ANNUN,    ({ 3019,  3,  8, }),\
                           RQ_ENTERED_MORDOR,        ({ 3019,  3, 15, }),\
                           RQ_QUEST_ENDED,           ({ 3019,  3, 25, }),\
                        })

/* prototypes */
varargs int     query_dawn(int m, int d);
varargs int     query_dusk(int m, int d);
int     convert_months_days(int m, int d);
void    dump();
int     query_midnight();
string  query_time();
string  query_date();
void    dawn();
void    dusk();
void    midnight();
private void    reset_rq_stage();
void    check_rq_stage();
int     query_rq_stage();

int     month,
        day,
        year,
        hours,
        minutes,
        rq_stage;       // Stage of the Ring Quest
                        // Stage <=  0:                       quest not started
			// Stage >= RQ_GANDALF_IN_BAGEND:     Gandalf in Bag End      (begins Apr 12th, 3018)
                        // Stage >= RQ_OSGILIATH_ATTACK:      Attack on Osgiliath     (begins Jun 20th, 3018)
                        // Stage >= RQ_LEFT_HOBBITON:         Ring left Hobbiton      (begins Sep 23rd, 3018)
                        // Stage >= RQ_ARRIVED_IN_RIVENDELL:  Ring in Rivendell       (begins Oct 20th, 3018)
                        // Stage >= RQ_LEFT_RIVENDELL:        Ring left Rivendell     (begins Dec 25th, 3018)
                        // Stage >= RQ_ARRIVED_IN_LOTHLORIEN: Ring in Lothlorien      (begins Jan 16th, 3019)
                        // Stage >= RQ_LEFT_LOTHLORIEN:       Ring left Lothlorien    (begins Feb 16th, 3019)
                        // Stage >= RQ_LEFT_HENNETH_ANNUN:    Ring left Henneth Annun (begins Mar  8th, 3019)
                        // Stage >= RQ_ENTERED_MORDOR:        Ring has entered Mordor (begins Mar 15th, 3019)
                        // Stage >= RQ_QUEST_ENDED:           Ring Quest solved       (     = Mar 25th, 3019)

string  gondor_master_file,
        rhovanion_master_file,
        shire_master_file;

static object  gondor_master,
               shire_master,
               rhovanion_master,
                RingQuest_Master;
static int     summer_midth,
               winter_midth,
               winter_midth2,
               winter_start,
               spring_start,
               fall_start,
               summer_start,
               war;		// War in Middle Earth (0/1), corresponds to rq_stage >= 40.

/* SYSTEM ROUTINES */
 
private void
bug_msg(string fname)
{
    object  po = previous_object();

    if (previous_object() == TO)
        po = previous_object(-2);

    log_file("clock", file_name(po) + " (" + calling_function() + 
        ") calling " + (fname) + " in " + MASTER + "!\n");
    if (objectp(po) && (po->query_domain() == "Gondor"))
        log_file("bugs", file_name(po) + " (" + calling_function() +
            ") calling " + (fname) + " in " + MASTER + "!\n");
}

private void
create_object()
{
    int     ta_days;

    set_short("the master clock of Gondor");

    summer_midth = convert_months_days(SUMMER_PEAK_MONTH,
  				     SUMMER_PEAK_DAY);
    winter_midth = convert_months_days(WINTER_PEAK_MONTH,
  				     WINTER_PEAK_DAY);
    winter_midth2 = winter_midth + MONTHS * DAYS;
    winter_start = ((summer_midth + winter_midth2)/2 + winter_midth2)/2;
    spring_start = ((summer_midth + winter_midth)/2 + winter_midth)/2;
    summer_start = ((summer_midth + winter_midth)/2 + summer_midth)/2;
    fall_start =   ((summer_midth + winter_midth2)/2 + summer_midth)/2;

    seteuid(getuid(this_object()));
    restore_object(CLOCK_DATA);

    log_file("rq_stage", "Clock initialized at "+ctime(time())
      + " to Ring Quest Stage " + rq_stage + " at "
      + query_time() + " on " + query_date() + ".\n");
    // Reset time when end time has been reached or Ring Quest was solved
    ta_days = ME_TA_DAYS(year,month,day);
    if ((rq_stage >= 100) ||
        (ta_days > (ME_TA_DAYS(ME_END_YEAR, ME_END_MONTH, ME_END_DAY))) ||
        (ta_days < (ME_TA_DAYS(ME_START_YEAR, ME_START_MONTH, ME_START_DAY))))
    {
        log_file("rq_stage", "Clock and Ring Quest Stage reset at "
          + ctime(time()) + " from Ring Quest Stage " + rq_stage
          + " at " + query_time() + " on " + query_date() + ".\n");
        year  = ME_START_YEAR;
        month = ME_START_MONTH;
        day   = ME_START_DAY;
        rq_stage = 0;
        reset_rq_stage();
    }

    check_rq_stage();
    set_alarm(REALTOGAME, REALTOGAME, "upd_time");
    set_alarm(0.0, SAVETIME, "dump");
}

public void
upd_time()
{
    minutes += 1;
    if (minutes > (MINUTES-1))
    {
        minutes = 0;
        hours += 1;
        if (hours == HOURS) midnight();
        if (hours == query_dawn()) dawn();
        if (hours == query_dusk()) dusk();
        if (hours > HOURS)
        {
            hours = 1;
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
            }
        }
    }
}

public void
dump()
{
    object  dummy;
    if (strlen(gondor_master_file))
    {
        gondor_master_file->load_me();
        if (objectp(dummy = find_object(gondor_master_file)))
            gondor_master = dummy;
        else log_file("clock","Failed to load Gondor master-file.\n");
    }
    else log_file("clock","No Gondor master-file.\n");
    if (strlen(shire_master_file))
    {
        shire_master_file->load_me();
        if (objectp(dummy = find_object(shire_master_file)))
            shire_master = dummy;
    }
    if (strlen(rhovanion_master_file))
    {
        rhovanion_master_file->load_me();
        if (objectp(dummy = find_object(rhovanion_master_file)))
            rhovanion_master = dummy;
    }

    RING_QUEST_MASTER->load_me();
    if (objectp(dummy = find_object(RING_QUEST_MASTER)))
        RingQuest_Master = dummy;

    FIX_EUID;
    save_object(CLOCK_DATA);
}

private int
convert_hours_minutes(int h, int m)
{
    if (h == HOURS) h = 0;
    return (h*MINUTES + m) * REALTOGAME;
}

private int
convert_months_days(int m, int d)
{
    return (m - 1) * DAYS + d;
}

/* QUERY ROUTINES */

varargs string
query_month_s(int val)
{
    int test;

    BUG_MSG("query_month_s");

    if(!val) test = month;
    else test = val;
     
    if(test == 1) return "Narvinye";       /* "January";   */
    if(test == 2) return "Nenime";         /* "February";  */
    if(test == 3) return "Sulime";         /* "March";     */
    if(test == 4) return "Viresse";        /* "April";     */
    if(test == 5) return "Lotesse";        /* "May";       */
    if(test == 6) return "Narie";          /* "June";      */
    if(test == 7) return "Cermie";         /* "July";      */
    if(test == 8) return "Urime";          /* "August";    */
    if(test == 9) return "Yavannie";       /* "September"; */
    if(test == 10) return "Narquelie";     /* "October";   */
    if(test == 11) return "Hisime";        /* "November";  */
    if(test == 12) return "Ringare";       /* "December";  */
    return "error";
}

int
query_month()
{ 
    BUG_MSG("query_month");
    return month;
}

int
query_day()
{ 
    BUG_MSG("query_day");
    return day;
}

int
query_year()
{
    BUG_MSG("query_year");
    return year;
}

int
query_war()
{
    BUG_MSG("query_war");
    if (query_rq_stage() >= RQ_STAGE_WAR)
        war = 1;
    else
        war = 0;
    return war;
}

int
set_war(int i)
{
    war = i;
}

string
query_date()
{ 
    BUG_MSG("query_date");
    return day + "/" + month + "/" + year;
}

string
query_date_b()
{ 
    BUG_MSG("query_date_b");
    return "Today is the " + day + "." + month +
       ". of year " + year + ", Third Age. "+
       "Current game time: " + query_time()+"\n";
}

string
query_date_s()
{ 
    BUG_MSG("query_date_s");
    return query_month_s() + " " + day + ", " + year;
}

int
query_24_hour()
{ 
    BUG_MSG("query_24_hour");
    if(hours == HOURS) return 0;
    return hours;
}
 
int
query_minute() 
{ 
    BUG_MSG("query_minute");
    return minutes;
}

int
query_12_hour()
{
    BUG_MSG("query_12_hour");
    if(hours > HOURS/2) return hours - HOURS/2;
    return hours;
}

int
query_hour()
{ 
    BUG_MSG("query_hour");
    return query_24_hour();
}

int
query_am()
{ 
    BUG_MSG("query_am");
    return (hours < HOURS/2) || ((hours == HOURS) && minutes);
}

int
query_pm()
{ 
    BUG_MSG("query_pm");
    return (hours > HOURS/2) || ((hours == HOURS/2) && minutes);
}

int
query_midnight()
{ 
    BUG_MSG("query_midnight");
    return (hours == HOURS) && !minutes;
}

int
query_noon()
{
    BUG_MSG("query_noon");
    return (hours == HOURS/2) && !minutes;
}

string
query_am_pm()
{
    BUG_MSG("query_am_pm");
    if(query_am()) return "am";
    else if(query_pm()) return "pm";
    else if(query_noon()) return "noon";
    else return "midnight";
}

string
query_time()
{
    int hour;
    string tmp;

    BUG_MSG("query_time");
    hour = query_24_hour();
    if(hour < 10) tmp = "0";
    tmp = tmp + hour + ":";
    if(minutes < 10) tmp = tmp + "0";
    tmp = tmp + minutes;
    return tmp;
}

string
query_time_24()
{
    BUG_MSG("query_time_24");
    return query_time();
}

string
query_time_12()
{
    int hour;
    string tmp;

    BUG_MSG("query_time_12");
    hour = query_12_hour();
    if(hour < 10) tmp = "0";
    tmp = tmp + hour + ":";
    if(minutes < 10) tmp = tmp + "0";
    tmp = tmp + minutes + " " + query_am_pm();
    return tmp;
}

string
query_moon(int arg)
{
    int val1;
    
    BUG_MSG("query_moon");
    if(arg) val1 = arg;
    else val1 = day;
     
    if(val1 >= DARKMOON && val1 < WAXING_CRES) return "dark";
    if(val1 >= WAXING_CRES && val1 < WAXING_GIB) return "waxing crescent";
    if(val1 >= WAXING_GIB && val1 < FULLMOON) return "waxing gibbous";
    if(val1 >= FULLMOON && val1 < WANING_GIB) return "full";
    if(val1 >= WANING_GIB && val1 < WANING_CRES) return "waning gibbous"; 
    if(val1 >= WANING_CRES || val1 < DARKMOON) return "waning crescent"; 
    return "error";
}

string
query_season(int arg1, int arg2)
{
    int val1, val2,now;
     
    BUG_MSG("query_season");
    if(arg1) val1 = arg1;
    else val1 = month;
    if(arg2) val2 = arg2;
    else val2 = day;
    now = convert_months_days(val1,val2);

    if(now < spring_start) return "winter";
    if(now < summer_start) return "spring";
    if(now < fall_start) return "summer";
    if(now < winter_start) return "autumn";
    return "winter";
}

/* Returns the hour of dawn */

varargs int
query_dawn(int m, int d)
{
    int val1,val2,now;

    BUG_MSG("query_dawn");
    if (m) val1 = m;
    else val1 = month;
    if (d) val2 = d;
    else val2 = day;
        now = convert_months_days(val1,val2);
    if(now < winter_midth) now = now + MONTHS * DAYS;
    
    if(now < summer_midth) {
    now = now - winter_midth;
    return DAWN_WINTER - (now * (DAWN_WINTER - DAWN_SUMMER + 1)) /
           (summer_midth - winter_midth + 1);
    }
    else {
    now = now - summer_midth;
    return DAWN_SUMMER + (now * (DAWN_WINTER - DAWN_SUMMER + 1)) /
           (winter_midth2 - summer_midth + 1);
    }
}

/* Returns the hour of dusk */

varargs int
query_dusk(int m, int d)
{
    int val1,val2,now;

    BUG_MSG("query_dusk");
    if(m) val1 = m;
    else val1 = month;
    if(d) val2 = d;
    else val2 = day;
    now = convert_months_days(val1,val2);
    if(now < winter_midth) now = now + MONTHS * DAYS;
    
    if(now < summer_midth) {
    now = now - winter_midth;
    return DUSK_WINTER + (now * (DUSK_SUMMER - DUSK_WINTER + 1)) /
           (summer_midth - winter_midth + 1);
    }
    else {
    now = now - summer_midth;
    return DUSK_SUMMER - (now * (DUSK_SUMMER - DUSK_WINTER + 1)) /
           (winter_midth2 - summer_midth + 1);
    }
}

string
query_time_of_day(int m, int d, int h)
{
    int val1,val2,val3,dusk,dawn;

    BUG_MSG("query_time_of_day");
    if(m) val1 = m;
    else val1 = month;
    if(d) val2 = d;
    else val2 = day;
    if(h) val3 = h;
    else val3 = hours;

    dawn = query_dawn(val1,val2);
    dusk = query_dusk(val1,val2);

    if(val3 < dawn) return "night";
    if(val3 < dawn + DAWN_LENGTH) return "early morning";
    if(val3 < HOURS/2) return "morning";
    if(val3 == HOURS/2) return "noon";
    if(val3 < dusk) return "afternoon";
    if(val3 < dusk + DUSK_LENGTH) return "evening";
    return "night";
}

int
set_gondor_master(string masterfile)
{
  if (!masterfile || !stringp(masterfile) || !find_object(masterfile))
  {
    return 0;
  }
  gondor_master_file = masterfile;
  return 1;
}

int
set_shire_master(string masterfile)
{
  if (!masterfile || !stringp(masterfile) || !find_object(masterfile))
  {
    return 0;
  }
  shire_master_file = masterfile;
  return 1;
}

int
query_in_middle_earth(object player)
{
  string roomstr,s1,s2;

    BUG_MSG("query_in_middle_earth");
  if (!environment(player) || !file_name(environment(player))) return 0;
  roomstr = file_name(environment(player));
  if (sscanf(roomstr,"%sGondor%s",s1,s2)==2 ||
      sscanf(roomstr,"%sShire%s",s1,s2)==2 ||
      sscanf(roomstr,"%sRhovanion%s",s1,s2)==2)
  {
    return 1;
  }
  return 0;
}

void
dawn()
{
  object *player;
  int n;
  player = users();

    // Disable messages from this version of the clock:
    return;
  while (n<sizeof(player))
  {
    if (query_in_middle_earth(player[n]))
    {
      if ((!environment(player[n])->query_prop(ROOM_I_INSIDE)) &&
          (!environment(player[n])->query_prop(ROOM_I_NO_ME_SUN)))
      {
        tell_object(player[n], "The darkness seems to creep back east, " +
          "and day begins.\n");
      }
    }
    n++;
  }
  seteuid(getuid());
  if (gondor_master)
    gondor_master->sunrise();
  if (shire_master)
    shire_master->sunrise();
}

void
dusk()
{
  object *player;
  int n;
  player = users();

    // Disable messages from this version of the clock:
    return;

  while (n<sizeof(player))
  {
    if (query_in_middle_earth(player[n]))
    {
      if ((!environment(player[n])->query_prop(ROOM_I_INSIDE)) &&
          (!environment(player[n])->query_prop(ROOM_I_NO_ME_SUN)))
      {
        tell_object(player[n], "Darkness rolls in over the land of " +
          "Middle-earth from the east.\n");
      }
    }
    n++;
  }
  if (gondor_master)
    gondor_master->sunset();
  if (shire_master)
    shire_master->sunset();
}

private void
reset_rq_stage()
{
    object  dummy;

    seteuid(getuid());

    log_file("rq_stage", "Trying to load the Gondor Master File "
      + gondor_master_file + " now! " + ctime(time()) + ".\n");

    if (strlen(gondor_master_file))
    {
        gondor_master_file->load_me();
        if (objectp(dummy = find_object(gondor_master_file)))
        {
            log_file("rq_stage", file_name(dummy) + " loaded!\n");
            gondor_master = dummy;
        }
    }

    if (objectp(gondor_master))
    {
        log_file("rq_stage", "Going to call reset_rq_stage() in "
          + file_name(gondor_master) + " now!\n");
        gondor_master->reset_rq_stage();
    }
}

void
midnight()
{
  /*
  gondor_master->midnight();
  */
}

/*
 *  Ring Quest functions
 */
int
query_rq_stage()
{
    BUG_MSG("query_rq_stage");
    check_rq_stage();
    return rq_stage;
}

int
set_rq_stage(int i)
{
    BUG_MSG("set_rq_stage");
    // We can only increase the counter
    if (i <= rq_stage)
        return 0;

    // Only the Ring Quest Master Object can increase the counter
    if (previous_object() != RingQuest_Master)
        return 0;

    log_file("rq_stage", "Ring Quest Stage advanced from "+rq_stage
      + " to " + i + " at " + query_time() + " on " + query_date()
      + ". (" + ctime(time()) + ").\n");
    rq_stage = i;
    dump();
    return 1;
}

void
check_rq_stage()
{
    int     i;
    mixed  *dates = RQ_STAGE_DATE;

DEBUG_MSG(rq_stage + ", "+dates[i]+", "+ME_TA_DAYS(year, month, day)+", "+ME_TA_DAYS(dates[i+1][0], dates[i+1][1], dates[i+1][2]));
    BUG_MSG("check_rq_stage");

    for (i = 0; i < sizeof(dates); i += 2)
    {
        if ((rq_stage < dates[i]) && (ME_TA_DAYS(year, month, day) >=
            ME_TA_DAYS(dates[i+1][0], dates[i+1][1], dates[i+1][2])))
        {
            seteuid(getuid());
            log_file("rq_stage", "Ring Quest Stage updated to "+dates[i]
              + " at " +query_time() + " of " + query_date()
              + ". (" + ctime(time()) + ").\n");
            rq_stage = dates[i];
            dump();
        }
    }

}

int
query_third_age_days()
{
    BUG_MSG("query_third_age_days");
    return ME_TA_DAYS(year,month,day);
}

void
remove_object()
{
    dump();
    ::remove_object();
}


