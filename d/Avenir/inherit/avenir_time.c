// Avenir Time Clock (/d/Avenir/inherit/avenir_time.c)
// creator(s):   Elwing 16 Aug 1998
// last update:  Lilith 19 Dec 1998
// purpose:      To be inherited by any object that needs to know Avenir time
// note:         See avenir_time_callout and other functions, below.
// Updates:
//     10/2011 Zizuph - initial set_alarm was miscalculated, leading to
//                      clock skew between avenir_time objects.


#define RL_SECONDS_PER_AVENIR_HOUR 3600
#define SYSTIME_OFFSET  20
#define YEAR_BASE       771

#include <language.h>        


/* 
 * Global Variables 
 */
private
int av_year, av_week_of_year, av_hour, av_dow;

private
int my_alarm_id;
     
public             /* The twelve sybarite weeks */ 
string AvWeek = ({ "null", "t'aeris", "hla'jeran", "tsa-dara", "ilaris", 
                   "m'tenit", "ry'alt", "flar-Idrys", "hl'endh", 
                   "pr'aith", "chrai'ni", "st'aeris", "maedon"});

/*
 * Function name: update_time
 * Description  : Calculate the Avenir time based upon system time.
 */
public void
update_time()
{
    int num;

    num=(time()-SYSTIME_OFFSET)/RL_SECONDS_PER_AVENIR_HOUR;
    av_hour=num % 12; /* avenirian day = 12 hours */
    num=num / 12;     /* days */
    av_dow=num % 12;  /* day of (avenirian) week 0..11 */
    num=num / 12;     /* weeks */
    av_week_of_year=num % 12;
    av_year=(num / 12)+YEAR_BASE; /* years */
}

/*
 * Function name: get_avenir_year
 * Description  : Get the current Year
 * Returns      : The int Year.
 */
public int get_avenir_year() {    return av_year;    }

/*
 * Function name: get_avenir_hour
 * Description  : Get the current Hour
 * Returns      : The int for the Hour.
 */
public int get_avenir_hour() {    return av_hour+1 ; }

/*
 * Function name: get_avenir_day
 * Description  : Get the current Day
 * Returns      : The int Day.
 */
public int get_avenir_day()  {    return av_dow+1;   }

/*
 * Function name: get_avenir_week
 * Description  : Get the current week
 * Returns      : The int week.
 *                For the week name, see get_week_name, below.
 */
public int get_avenir_week() {    return av_week_of_year+1;  }

/*
 * Function name: get_week_name
 * Description  : Get text name for the week: week number 1 -> "t'aeris".
 * Returns      : string for the int week.
 */
public string 
get_week_name(int week) 
{   
    mixed m;
    m = AvWeek[week];
    return m;
}

/*
 * Function name: avenir_time_callout
 * Description  : Mask this function to get notification of avenir time.
 *                See /d/Avenir/common/obj/clock.c for example usage.
 */
public void
avenir_time_callout(int av_year,int av_week_of_year,int av_dow,int av_hour)
{
    
}

/*
 * Function name: get_time_text
 * Description  : Get a full text version of the time.
 * Returns      : "First Hour in the fourth day of Wei chrai'ni 
 *                in the Sybarite year 1449"
 */
public string
get_time_text()
{
    int year,week,day,hour;
    string test_time;

    year=get_avenir_year();
    week=get_avenir_week();
    day=get_avenir_day();
    hour=get_avenir_hour();

    test_time = capitalize(LANG_WORD(hour)) +" Hour in the "+ 
        LANG_WORD(day)  +" day of Wei "+ get_week_name(week) +
        " in the Sybarite year "+ year;
    return test_time;
}


private nomask
avtime_alarm()
{
    update_time();

    /* make it start from 1, not 0 */
    avenir_time_callout(av_year,av_week_of_year+1,av_dow+1,av_hour+1);
}

public
start_avtime()
{
    float modulo;
    
    modulo= itof(RL_SECONDS_PER_AVENIR_HOUR  + 2 
        - ((time()-SYSTIME_OFFSET) % RL_SECONDS_PER_AVENIR_HOUR) );
    
    update_time();

    if (!my_alarm_id)
        my_alarm_id=set_alarm(modulo,itof(RL_SECONDS_PER_AVENIR_HOUR),avtime_alarm);
}

public
stop_avtime()
{
    remove_alarm(my_alarm_id);
    my_alarm_id=0;
}

