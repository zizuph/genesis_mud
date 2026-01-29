/*
 * File: clock.c
 * Description: The Raumdor Time System (RTS)
 * Authors: Lucius and Rhyn
 * Created: Jan 11 2001
 *
 * Notes:
 *
 * 1 qhour = 225 secs
 * 1 hour = 900 secs
 * 1 day = 24 hours = 96 quarters = 21600 secs
 *
 *
 * WARNING:
 *
 *  DO NOT CALL THIS CLOCK DIRECTLY OR YOU WILL BE BEATEN!
 *  Instead, use the defines which may be found in /d/Raumder/defs.h
 *
 */
#pragma save_binary
#pragma strict_types
#pragma no_inherit
#pragma no_clone

#include <language.h>
#include <macros.h>

#include "defs.h"

/* The daytime hours. */
#define DAY_START   DAYBREAK
#define DAY_END     NIGHTFALL

/* Shortcuts to the values named */
#define HOUR    time[1]
#define QHOUR   time[0]

/* Base hour, quarter hour values */
#define B_HOUR  1
#define B_QHOUR 0

/* Increment values for hour/quarter hour */
#define I_HOUR  1
#define I_QHOUR 15

/* Values to reset back to base when reached for hour, quarter hour */
#define R_HOUR  24
#define R_QHOUR 45

/* Global variables. */
#ifndef SAVE_EVENTS
static mixed *events = ({});
#else
public mixed *events = ({});
#endif
static int ticker_id;
public int *time = ({ B_QHOUR, B_HOUR });

/*
 * Don't need people shadowing our clock.
 */
public int
query_prevent_shadow()
{
    return 1;
}


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
    return (std ? (HOUR > 12 ? HOUR - 12 : HOUR) : HOUR);
}

/*
 * The current quarter hour
 */
public int
query_quarter_hour()
{
    return QHOUR;
}

/*
 * Is it day?
 */
public int
query_day()
{
    return (HOUR >= DAY_START && HOUR < DAY_END);
}

/*
 * Is it night?
 */
public int
query_night()
{
    return !query_day();
}

/*
 * Is it 'am' according to a 12hr clock?
 */
public int
query_am()
{
    return (HOUR <= 11 || HOUR == 24);
}

/*
 * Is it 'pm' according to a 12hr clock?
 */
public int
query_pm()
{
    return !query_am();
}

/*
 * Return 12hr time format by default.
 * 24hr time format if specify 'mil' argument.
 */
public varargs string
query_time(int mil)
{
    int hour = HOUR, qhour = QHOUR;
    string time = "";

    if (!mil && hour > 12)
        hour -= 12;

    if (mil && hour < 10)
        time += "0";

    time += hour + ":" + (qhour == 0 ? "00" : "" + qhour);

    if (!mil)
        time += (query_am() ? " am" : " pm");

    return time;
}

/*
 * Return a 'fancy text' descriptive time output.
 * 12hr time by default, 24hr time if 'mil' argument specified.
 */
public varargs string
query_time_desc(int mil)
{
    string hour_str, qhour_str;
    int hour = HOUR, qhour = QHOUR;

    if (!mil && hour > 12)
        hour -= 12;

    switch(hour)
    {
        case 12:
            if (!mil)
                hour_str = (query_day() ? "noon" : "midnight");
            else
                hour_str = "noon";
            break;
        case 24:
            hour_str = "midnight";
            break;
        default:
            hour_str = LANG_WORD(hour);
            break;
    }

    switch(qhour)
    {
        case 15:
            qhour_str = "a quarter past the ";
            break;
        case 30:
            qhour_str = "half past the ";
            break;
        case 45: /* Special case, check one hour ahead. */
            switch(hour + 1)
            {
                case 24:
                    hour_str = "midnight";
                    break;
                case 12:
                    if (!mil)
                        hour_str = (query_day() ? "noon" : "midnight");
                    else
                        hour_str = "noon";
                    break;
                default:
                    hour_str = LANG_WORD(hour + 1);
                    break;
            }
            qhour_str = "a quarter until the ";
            break;
        default:
            qhour_str = "in the ";
            break;
    }

#if 0
    if (mil)
    {
    return "Is is " + qhour_str + hour_str + " hour.\n";
    }
    else
#endif
    return (query_day() ? "daylight" : "night") + " and " + qhour_str + 
      hour_str + " hour";
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
    if (member_array(ob, events) < 0)
        events += ({ ob });
}

/*
 * Remove a registered event.
 */
public void
remove_event(mixed ob)
{
    if (!pointerp(ob))
        ob = ({ob});
    events -= ob;
}

/*
 * What events are waiting?
 */
public void
query_events()
{
    return secure_var(events);
}


/*
 * Actually call an event and catch errors
 */
public void
run_event(object ob)
{
    try {
        ob->event_hook(HOUR);
    } catch(mixed error) 
    {
        log_file("clock", 
            sprintf("Runtime while executing event hook in %O: %s\n", ob, error));
    }
}

/*
 * Run through events
 */
public void
clock_events()
{
    remove_event(0);
    events = filter(events, &not() @ run_event);
}


/********************************************************************
 * The clock mechanics 
 */
/*
 * Advance the clock.
 */
public void
tick_tock()
{
    if(HOUR == R_HOUR && QHOUR == R_QHOUR)
    {
        HOUR  = B_HOUR;
        QHOUR = B_QHOUR;
        set_alarm(0.0, 0.0, &clock_events());
    }
    else if(QHOUR == R_QHOUR)
    {
        HOUR += I_HOUR;
        QHOUR = B_QHOUR;
        set_alarm(0.0, 0.0, &clock_events());
    }
    else
    {
        QHOUR += I_QHOUR;
    }
}

/*
 * Start the clock running.
 */
private void
start_clock()
{
    if (get_alarm(ticker_id))
        return;

    restore_object(MASTER);
    ticker_id = set_alarm(255.0, 255.0, tick_tock);
}


/*
 * Stop a running clock.
 */
private void
stop_clock()
{
    if (!ticker_id)
        return;

    remove_alarm(ticker_id);
    save_object(MASTER);
    ticker_id = 0;
}

/*
 * Unload the clock.
 */
public void
remove_object()
{
    stop_clock();
    destruct();
}

/*
 * Load the clock.
 */
private void
create()
{
    setuid();
    seteuid(getuid());
    start_clock();
}

