/* The master clock of Middle-earth.
 * Modifications made by Elessar from Oct '91 to May '92.
 */
inherit "/std/object";
#include "/sys/stdproperties.h"

#define REALTOGAME 1            /* seconds to a game minute */
#define SAVETIME 1800           /* seconds between saves of clock */
#define CLOCK_DATA "/d/Gondor/elessar/lib/clockdata"

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
#define DAWN_LENGTH 2           /* Lenght in hours */
#define DUSK_LENGTH 2

#define MINUTES 60
#define HOURS 24
#define DAYS 30
 
/* If you change the number of months, you MUST change the query_month_s()
   function, or else things will not always work correctly.
*/

#define MONTHS 12

int month, day, year, hours, minutes, war;
object gondor_master;
static int summer_midth, winter_midth, winter_midth2;
static int winter_start, spring_start, fall_start, summer_start;

/* SYSTEM ROUTINES */
 
create_object() {
	  year = 3018;
	  month = 4;
	  day = 14;
	  hours = HOURS;
	  summer_midth = convert_months_days(SUMMER_PEAK_MONTH,
					     SUMMER_PEAK_DAY);
	  winter_midth = convert_months_days(WINTER_PEAK_MONTH,
					     WINTER_PEAK_DAY);
	  winter_midth2 = winter_midth + MONTHS * DAYS;
	  winter_start = ((summer_midth + winter_midth2)/2 + winter_midth2)/2;
	  spring_start = ((summer_midth + winter_midth)/2 + winter_midth)/2;
	  summer_start = ((summer_midth + winter_midth)/2 + summer_midth)/2;
	  fall_start =   ((summer_midth + winter_midth2)/2 + summer_midth)/2;
          restore_object(CLOCK_DATA);
	  call_out("upd_time",REALTOGAME);
	  dump();
	  gondor_master = find_object("/d/Gondor/common/master");
}

upd_time() {
    minutes += 1;
    if(minutes > (MINUTES-1))
    {
	minutes = 0;
	hours += 1;
	if(hours == HOURS) midnight();
	if(hours == query_dawn()) dawn();
	if(hours == query_dusk()) dusk();
	if(hours > HOURS)
	{
	    hours = 1;
	    day += 1;
	    if(day > DAYS)
	    { 
		day = 1;
		month += 1;
		if(month > MONTHS)
		{
		    month = 1;
		    year += 1;
		}
	    }
	}
    }
    call_out("upd_time",(REALTOGAME - 1));
}

dump() {
    save_object(CLOCK_DATA);
    call_out("dump",SAVETIME);
}

convert_hours_minutes(h, m) {
    if(h == HOURS) h = 0;
    return (h*MINUTES + m) * REALTOGAME;
}

convert_months_days(m,d) {
    return (m - 1) * DAYS + d;
}

/* QUERY ROUTINES */

query_month_s(val) {
    int test;
     
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

query_month() { 
    return month;
}

query_day() { 
    return day;
}

query_year() {
    return year;
}

query_war() {
    return war;
}

set_war(int i) {
    war = i;
}

query_date() { 
    return day + "/" + month + "/" + year;
}

query_date_b() { 
    return "Today is the " + day + "." + month +
	   ". of year " + year + ", Third Age. "+
	   "Current game time: " + query_time()+"\n";
}

query_date_s() { 
    return query_month_s() + " " + day + ", " + year;
}

query_24_hour() { 
    if(hours == HOURS) return 0;
    return hours;
} 
query_minute() { 
    return minutes;
}

query_12_hour() {
    if(hours > HOURS/2) return hours - HOURS/2;
    return hours;
}

query_hour() { 
    return query_24_hour();
}

query_am() { 
    return (hours < HOURS/2) || ((hours == HOURS) && minutes);
}

query_pm() { 
    return (hours > HOURS/2) || ((hours == HOURS/2) && minutes);
}

query_midnight() { 
    return (hours == HOURS) && !minutes;
}

query_noon() { 
    return (hours == HOURS/2) && !minutes;
}

query_am_pm() {
    if(query_am()) return "am";
    else if(query_pm()) return "pm";
    else if(query_noon()) return "noon";
    else return "midnight";
}

query_time() { 
    int hour;
    string tmp;

    hour = query_24_hour();
    if(hour < 10) tmp = "0";
    tmp = tmp + hour + ":";
    if(minutes < 10) tmp = tmp + "0";
    tmp = tmp + minutes;
    return tmp;
}

query_time_24() { 
    return query_time();
}

query_time_12() {
    int hour;
    string tmp;

    hour = query_12_hour();
    if(hour < 10) tmp = "0";
    tmp = tmp + hour + ":";
    if(minutes < 10) tmp = tmp + "0";
    tmp = tmp + minutes + " " + query_am_pm();
    return tmp;
}

query_moon(arg) {
    int val1;
    
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

query_season(arg1, arg2) {
    int val1, val2,now;
     
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

query_dawn(m,d) {
    int val1,val2,now;

    if(m) val1 = m;
    else val1 = month;
    if(d) val2 = d;
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

query_dusk(m,d) {
    int val1,val2,now;

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

query_time_of_day(m,d,h) {
    int val1,val2,val3,dusk,dawn;

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

query_in_middle_earth(object player)
{
  string roomstr,s1,s2;
  roomstr = file_name(environment(player));
  if (sscanf(roomstr,"%sGondor%s",s1,s2)==2 || sscanf(roomstr,"%sShire%s",s1,s2)==2
    || sscanf(roomstr,"%sAlchar%s",s1,s2)==2 || sscanf(roomstr,"%sLaoth%s",s1,s2)==2 
    || sscanf(roomstr,"%sEa%s",s1,s2)==2)
      return 1;
  else return 0;
}

dawn()
{
  object *player;
  int n;
  player = users();
  while (n<sizeof(player)) {
    if (query_in_middle_earth(player[n])) {
      if (!environment(player[n])->query_prop(ROOM_I_INSIDE))
        tell_object(player[n],"The sun rises above the eastern horizon.\n");
      }
    n++;
    }
  /*
  gondor_master->sunrise();
  */
}

dusk()
{
  object *player;
  int n;
  player = users();
  while (n<sizeof(player)) {
    if (query_in_middle_earth(player[n])) {
      if (!environment(player[n])->query_prop(ROOM_I_INSIDE))
        tell_object(player[n],"The sun disappears behind the western horizon.\n");
      }
    n++;
    }
  /*
  gondor_master->sunset();
  */
}

midnight()
{
  /*
  gondor_master->midnight();
  */
}
