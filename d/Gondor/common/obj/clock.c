// File          : clock.c
// Description   : This is a 'stub', so that older Gondor code can utilize
//                 the newer clock I wrote based in Mordor.
// Author        : Jeffrey C. Venable, Sr. (Curumo@Genesis)
// Copyright (c) : May 15th, 2000

// Lavellan 2010/10/26
// Seems at some point, presumably when Mordor got absorbed into Gondor, or
// maybe sometime later, the Ring Quest stages were changed from 1,2,3 etc
// (as in /d/Gondor/common/mordor/sys/clock2.h) to 1,5,10,18 etc, (as in
// /d/Gondor/common/lib/clock.h and /d/Gondor/sys/clock.h). Everything was
// using the new system, except the Mordor clock, which they were all getting
// the stage from. So everything (only the Black Rider movement now?) was
// receiving incorrect stage numbers. I have modified query_rq_stage here to
// translate the numbering system, hopefully making everything else happy with
// the stages again...

#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

#include <macros.h>
#include "/d/Gondor/common/mordor/sys/clock.h"

private static object _clock;
private string *master_files = ({ });

// Method  : find_clock
// Remarks : Locates the master clock object and loads it if necessary.

private nomask object
find_clock() {
    if (objectp(_clock))
        return (_clock);
    if (!catch(CLOCK->load_me()))
        return (_clock = find_object(CLOCK));
} // load_clock


// Method  : convert_hours_minutes
// Remarks : I believe this is supposed to take a given 'game' time
//           in hours and minutes (such as 18:23), and convert it
//           into the number of seconds until that time occurs in
//           the real world, possibly for use in setting an alarm.
//           I further suspect that this function was only intended
//           to be relevant within a single 24-hour period.  We should
//           probably grep for this function in the domain and remove
//           its use.

public nomask int
convert_hours_minutes(int h, int m) {
    h %= 24;
    return (((h * 60) + m) * 10);
} // convert_hours_minutes


// Method  : convert_months_days
// Remarks : This method is inconsistent with convert_hours_minutes
//           since its return value is not real-world seconds.  This
//           simply converts a given number of months and days into
//           total days, a lame method to have.  We should grep for
//           this function in the domain and remove its use.

public int
convert_months_days(int m, int d) {
    return (((m - 1) * 30) + d);
}

// Method  : query_month_s
// Remarks : This method returns a string for the name of the month
//           asked for.

public nomask string
query_month_s(int month = _clock->game_month()) {
    return (_clock->month_string(month));
} // query_month_s


// Method  : query_month
// Remarks : This method returns an integral value for the current month.

public nomask int
query_month() { 
    return (_clock->game_month());
} // query_month


// Method  : query_day
// Remarks : This method returns an integral value for the current day.

public nomask int
query_day() { 
    return (_clock->game_day());
} // query_day


// Method  : query_year
// Remarks : This method returns an integral value for the current year.

public nomask int
query_year() {
    return (_clock->game_year());
} // query_year


// Method  : query_war
// Remarks : This method returns a boolean of whether the ring-quest
//           has reached the state of 'war'.

public nomask status
query_war() {
    return (_clock->calculate_rq_stage() >= RQ_LEFT_HENNETH_ANNUN);
} // query_war


// Method  : query_date
// Remarks : This method returns a string value to the present date.

public nomask string
query_date() { 
    return (_clock->game_day() + "/" +
            _clock->game_month() + "/" +
            _clock->game_year());
} // query_date


// Method  : query_date
// Remarks : This method returns a string value to the present date,
//           but in longer format.

public nomask string
query_date_s() { 
    return (_clock->month_string() + " " + _clock->game_day() +
            ", " + _clock->game_year());
} // query_date_s


// Method  : query_24_hour
// Remarks : This method returns an integral value for the hour of
//           the present day.

public nomask int
query_24_hour() {
    return (_clock->game_hour());
} // query_24_hour

 
// Method  : query_12_hour
// Remarks : This method returns an integral value for the hour of
//           the present day.

public nomask int
query_12_hour() {
    int hour = _clock->game_hour();
    if (hour > 12)
        return (hour - 12);
    return (hour);
} // query_12_hour


// Method  : query_hour
// Remarks : This method returns an integral value for the hour of
//           the present day.

public nomask int
query_hour() { 
    return (_clock->game_hour());
} // query_hour


// Method  : query_minute
// Remarks : This method returns an integral value for the minute of
//           the present hour of the present day.

public nomask int
query_minute() { 
    return (_clock->game_minute());
} // query_minute


// Method  : query_am
// Remarks : Obvious.

public nomask status
query_am() {
    int hour = _clock->game_hour();
    return ((hour >= 0) && (hour < 12));
} // query_am


// Method  : query_pm
// Remarks : Obvious.

public nomask status
query_pm() { 
    int hour = _clock->game_hour();
    return ((hour >= 12) && (hour < 24));
} // query_pm


// Method  : query_midnight
// Remarks : Obvious.

public nomask status
query_midnight() { 
    return (_clock->game_time_24() == 0);
} // query_midnight


// Method  : query_noon
// Remarks : Obvious.

public nomask status
query_noon() {
    return (_clock->game_time_24() == (HOUR * 12));
} // query_noon


// Method  : query_am_pm
// Remarks : Returns either "am", "noon", "pm", or "midnight".

public nomask string
query_am_pm() {
    if (query_noon()) 
        return ("noon");
    if (query_midnight())
        return ("midnight");
    if (query_am()) 
        return ("am");
    return ("pm");
} // query_am_pm


// Method  : query_time
// Remarks : Returns a standard string representation of the current time.

public nomask string
query_time() {
    return (_clock->time_string());
} // query_time


// Method  : query_time_24
// Remarks : Returns a standard string representation of the current time.

public nomask string
query_time_24() {
    return (_clock->time_string());
} // query_time_24


// Method  : query_time_12
// Remarks : Returns a standard string representation of the current time.

public nomask string
query_time_12() {
    return (sprintf("%02d:02d:02d%s",
                    query_12_hour(),
                    _clock->game_minute(),
                    _clock->game_second(),
                    query_am_pm()));
} // query_time_12


// Method  : query_moon
// Remarks : Returns the string for the moon phase on the given date of
//           the month.  This stub actually sucks because the old clock
//           moon phases had a resolution of one day, whereas the new
//           clock uses the synodic period of the real moon.

public nomask string
query_moon(int d /* = _clock->game_day() */) {
    return (_clock->moon_phase_string());
} // query_moon

public nomask string
query_season(int t = (_clock->game_time() % YEAR)) {
    if (t < (45 * DAY))
        return ("autumn");
    if (t < (135 * DAY))
        return ("winter");
    if (t < (225 * DAY))
        return ("spring");
    if (t < (315 * DAY))
        return ("summer");
    return ("autumn");
} // query_season

public nomask int
query_dawn(int m = _clock->game_month(), int d = _clock->game_day()) {
    return (_clock->dawn((m * MONTH) + (d * DAY)) / HOUR);
} // query_dawn


public nomask int
query_dusk(int m = _clock->game_month(), int d = _clock->game_day()) {
    return (_clock->dusk((m * MONTH) + (d * DAY)) / HOUR);
} // query_dusk


public nomask string
query_time_of_day(int m = _clock->game_month(),
                  int d = _clock->game_day(),
                  int h = _clock->game_hour(),
                  int y = (_clock->game_year() - 3017)) {
    int t = (_clock->game_time_from_date(m, d, y) + (h * HOUR));
    switch (_clock->sun_position(t)) {
        case POSITION_NOT_VISIBLE :
            return ("night");
        case POSITION_EASTERN_HORIZON :
            return ("early morning");
        case POSITION_EASTERN_RISING :
            return ("morning");
        case POSITION_OVERHEAD :
            return ("noon");
        case POSITION_WESTERN_SINKING :
            return ("afternoon");
        case POSITION_WESTERN_HORIZON :
            return ("evening");
    }
} // query_time_of_day


public nomask status
add_master(string file) {
    if (!strlen(file) || (file_size(file + ".c") < 1))
        return (0);
    master_files -= ({ file }); // clear any duplicates
    master_files += ({ file });
    save_object(MASTER);
    return (1);
} // add_master


public nomask status
remove_master(string file) {
    if (member_array(file, master_files) < 0)
        return (0);
    master_files -= ({ file });
    save_object(MASTER);
    return (1);
} // remove_master


public nomask status
query_in_middle_earth(object player) {
    if (!objectp(player))
        return (0);
    return (member_array(environment(player)->query_domain(),
            ({ "Gondor", "Mordor", "Shire", "Rhovanion" })) >= 0);
} // query_in_middle_earth


/*public nomask int
query_rq_stage() {
    return (_clock->calculate_rq_stage());
} // query_rq_stage
*/

public nomask int
query_rq_stage() {
    int sta;
    sta = _clock->calculate_rq_stage();
    
    switch (sta)
    {
        case 0: return 0;
        case 1: return 1;
        case 2: return 5;
        case 3: return 10;
        case 4: return 18;
        case 5: return 20;
        case 6: return 28;
        case 7: return 30;
        case 8: return 40;
        case 9: return 50;
        case 10: return 100;
        default: return sta;
    }
    
/*  FROM:
#define  RQ_NONE                            0
#define  RQ_GANDALF_IN_BAGEND               1
#define  RQ_OSGILIATH_ATTACK                2
#define  RQ_LEFT_HOBBITON                   3
#define  RQ_ARRIVED_IN_RIVENDELL            4
#define  RQ_LEFT_RIVENDELL                  5
#define  RQ_ARRIVED_IN_LOTHLORIEN           6
#define  RQ_LEFT_LOTHLORIEN                 7
#define  RQ_LEFT_HENNETH_ANNUN              8
#define  RQ_ENTERED_MORDOR                  9
#define  RQ_QUEST_ENDED                    10
    TO: 
#define RQ_GANDALF_IN_BAGEND	  1
#define RQ_OSGILIATH_ATTACK       5
#define RQ_LEFT_HOBBITON	 10
#define RQ_ARRIVED_IN_RIVENDELL	 18
#define RQ_LEFT_RIVENDELL	 20
#define RQ_ARRIVED_IN_LOTHLORIEN 28
#define RQ_LEFT_LOTHLORIEN	 30
#define RQ_LEFT_HENNETH_ANNUN	 40
#define RQ_ENTERED_MORDOR	 50
#define RQ_QUEST_ENDED		100
#define RQ_QUEST_FULFILLED     1000
*/
} // query_rq_stage



public nomask int
query_third_age_days(int  year = _clock->game_year(),
                     int month = _clock->game_month(),
                     int   day = _clock->game_day()) {
    int t = (_clock->game_time_from_date(month, day, year));
    return (t / DAY);
} // query_third_age_days


public nomask void
dawn() {
    int x, sz = sizeof(master_files);
    for (x = 0; x < sz; x++)
        catch(master_files[x]->sunrise());
    _clock->notify_dawn(dawn);
} // dawn


public nomask void
dusk() {
    int x, sz = sizeof(master_files);
    for (x = 0; x < sz; x++)
        catch(master_files[x]->sunset());
    _clock->notify_dusk(dusk);
} // dusk


public nomask void
notify_sunrise(function callback) {
    _clock->notify_dawn(callback);
} // notify_sunrise


public nomask void
notify_sunset(function callback) {
    _clock->notify_dusk(callback);
} // notify_sunset


// Method  : create
// Remarks : Constructor.

public nomask void
create() {
    // initialize security
    seteuid(getuid(this_object()));

    find_clock();

    // restore global variables
    if (!restore_object(MASTER)) {
        _clock->log("restore_object() failed in clock stub; " +
                    "unable to load domain masters.");
    }

    _clock->notify_dawn(dawn);
    _clock->notify_dusk(dusk);

    _clock->log("clock stub loaded.");
} // create
