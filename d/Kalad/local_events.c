#pragma strict_types
#pragma save_binary

inherit "/std/room";

#include "/d/Kalad/defs.h"
#include <time.h>

/* This is the shortest interval you can have between events.
 * This is not the recommended interval (default is 60) but
 * it is the extreme case. Anything smaller would just be
 * too obnoxious. This is also the interval used when first
 * starting the events. We want the first one to happen fairly
 * soon (but not immediately) and the rest to follow at the
 * interval set with set_event_interval().
 */
#define MINTIME 20
/* 3 times a minute (Once every 6 2/3 minutes Kalad time)
 * - let's not bug the mortals too much
 */

/***************************************************************
 *   Globals
 ***************************************************************/
private float event_interval;
private string *eventlist;
private int allow_events;
private int alarm_id;

/***************************************************************
 *   Protoypes
 ***************************************************************/
nomask void new_event(string message);
nomask mixed query_events();
nomask void set_event_interval(float interval);
nomask float query_event_interval();
nomask void set_allow_events(int allow);
nomask int query_allow_events();
nomask void remove_event(string event);
static nomask void start_events();
private nomask void bad_interval(mixed arg);
nomask void clear_events();
nomask void stop_events();

void
create_room()
{
   ::create_room();
   
   /* set room defaults                                      */
   EVENTS_ON;             /* allow local events              */
   SET_ETIME(60.0);       /* once a min (20 mins Kalad time) */
}

nomask void
new_event(string message)
{
   if (!stringp(message) || message == "")
      return;

   if (eventlist == 0)
      eventlist = ({});
      
   eventlist += ({message});
}

nomask mixed
query_events()
{
   if (!pointerp(eventlist))
      return 0;
      
   return eventlist + ({});
}

nomask void
set_event_interval(mixed interval)
{
   if ( !floatp(interval) )
      if ( intp(interval) && (interval >= MINTIME) )
         event_interval = itof(interval);
      else
         bad_interval(interval);               
   else
      if ( ftoi(interval) >= MINTIME )
         event_interval = interval;
      else
         bad_interval(ftoa(interval));         
}

private nomask void
bad_interval(mixed arg)
{
   KLOG("errors", RTILDE(FN(TO)) + ": illegal argument to set_event_interval\n" +
      "int|float >= " + MINTIME + " expected. Received: " + arg + "\n");
}

nomask float
query_event_interval()
{
   return event_interval;
}

nomask void
set_allow_events(int allow)
{
   allow_events = allow;
}

nomask int
query_allow_events()
{
   if (allow_events == 0)
      return 0;
   else
      return 1;
}

nomask void
remove_event(string event)
{
   int pos;
   
   pos = member_array(event, eventlist);   
   if (pos >= 0)
      eventlist = exclude_array(eventlist, pos, pos);
}

nomask void
clear_events()
{
   eventlist = ({});
}

nomask void
stop_events()
{
   if (get_alarm(alarm_id))
      remove_alarm(alarm_id);
   alarm_id = 0;
   
   KLOG("local_events", RTILDE(FN(TO)) + ": Stopping events...\n");
}

static nomask void
start_events()
{
   int size;
   
   /* are events allowed? are there any events?      *
    * and are there any players present to see them? *
    * if so, show a random event and call next event */
    
   if ( allow_events && (size = sizeof(eventlist)) && 
    (sizeof(FILTER_PLAYERS(AINV(TO)))) )
   {
      tell_room(TO, "\n" + eventlist[random(size)] + "> " );
      alarm_id = ALARM(event_interval,start_events);
   }
   
   else
      stop_events(); /* otherwise stop the events    */
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   
   /* Is this_object a player?
    * are events allowed? are there any events? *
    * are no events already running?            *
    * If so, start the events...                */
    
   if ( interactive(ob) && allow_events && sizeof(eventlist) &&
    !get_alarm(alarm_id) )
   {
      KLOG("local_events", RTILDE(FN(TO)) + ": Starting events...\n");
      alarm_id = ALARM(itof(MINTIME),start_events);
   }
}
