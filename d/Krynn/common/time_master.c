/*
 * This is the timemaster. This room controls the flow
 * of events and time in Krynn.
 *
 * Functionality: All files which suffice *.c in /d/Krynn/common/flow/
 * are loaded. Each event and period is added to this master for
 * quicker access. This file keeps a marker for each flowchart to
 * determine the current state of each. This can be queried from within
 * the room by the command 'past', 'present', and 'future'.
 * Adding new charts is easy: just write a chart, and put it into
 * /d/Krynn/common/flow/. At next reboot, or when this file is updated,
 * the new information is automatically loaded. Removing old charts will
 * (presumably) not happen that often:
 * Just call remove_thread here in this room for the thread and hopefully
 * everything connected to the flowchart will be gone.
 *
 * Created by Aridor
 * Updated by Rastlin
 */

#pragma save_binary
#pragma strict_types

#include "/d/Krynn/common/defs.h"

inherit R_FILE
inherit "/lib/time";

#define SAVE_ME    "/d/Krynn/common/time_master"
#define FLOWCHARTS "/d/Krynn/common/flow/"

static mapping gPeriod         = ([]);
static mapping gEvent          = ([]);
mapping gCurrent_period = ([]);
mapping gLast_event     = ([]);
mapping gLast_period    = ([]);
mapping gCurrent_alarm  = ([]);
mapping special_thread_info = ([]);

/*prototypes*/
static void do_restore_object();
static void do_load_flowcharts();
static int handle_event(string thread, string name);

public void
create_krynn_room()
{
    seteuid(getuid(TO));
    set_short("Time Master");
    set_long("This is a peculiar room. Actually it's not even a room " +
	     "at all. You are just anywhere in time! You feel time as " +
	     "it flows past you and things happen. Actually you can " +
	     "do 'past', 'present' and 'future' to get the recent, current " +
	     " and future events, respectively, in Krynn as they are " +
	     "known.\n");
    add_exit("/d/Krynn/workroom", "out");
    do_restore_object();
    do_load_flowcharts();
}

/*
 * Function name: save_master
 * Description:   Save the time master
 */
public void
save_master()
{
    save_object(SAVE_ME);
}

public void
dump()
{
    dump_array(gCurrent_alarm);
}

/*
 * Function name: past
 * Description:   Output a list of gLast_event
 * Arguments:     str - The input is ignored
 */
public int
past(string str)
{
    int size = m_sizeof(gLast_event);
    mixed idxs = m_indexes(gLast_event);
    string idx;

    write("Thread         Last Event             Took place ... ago\n");
    write("-----------------------------------------------------------" +
	  "----------\n");

    while (size--)
    {
	idx = idxs[size];
	if (!idx)
	    write(sprintf("%-12s   NONE.\n",C(idx)));
    else if (gLast_event[idx])
	    write(sprintf("%-12s   %-20s   %-30s\n", C(idx), 
			  gLast_event[idx][0],
			  convtime(time() - gLast_event[idx][1])));
    }
    return 1;
}

/*
 * Function name: present
 * Description:   Output a list of gCurrent_period
 * Arguments:     str - The input is ignored
 */
public int
present(string str)
{
    int size = m_sizeof(gCurrent_period);
    mixed idxs = m_indexes(gCurrent_period);
    string idx;

    write("Thread         Current Period         Started ... ago\n");
    write("--------------------------------------------------------" +
	  "-------------\n");

    while(size--)
    {
        idx = idxs[size];
	if (!idx)
	    write(sprintf("%-12s   NONE.\n",C(idx)));
    else if (gCurrent_period[idx])
	    write(sprintf("%-12s   %-20s   %-30s\n", C(idx), 
			  gCurrent_period[idx][0],
			  convtime(time() - gCurrent_period[idx][1])));
    }
    return 1;
}

/*
 * Function name: future
 * Description:   Output a list of default events following the
 *                current periods
 * Arguments:     str - The input is ignored
 */
public int
future(string str)
{
    int size = m_sizeof(gCurrent_alarm);
    mixed idxs = m_indexes(gCurrent_alarm);
    string idx;

    write("Thread         Default Future Event   Takes place in\n");
    write("-------------------------------------------------------" +
	  "--------------\n");

    while(size--)
    {
        idx = idxs[size];
	if (!idx)
	    write(sprintf("%-12s   NONE.\n",C(idx)));
    else if (gCurrent_alarm[idx])
	    write(sprintf("%-12s   %-20s   %-30s\n", C(idx), 
			  gCurrent_alarm[idx][5],
			  (gCurrent_alarm[idx][0] == -1 ? 
			     "Krynn time based" : 
			     convtime(gCurrent_alarm[idx][1] + 
				      ftoi(gCurrent_alarm[idx][2]) -
				      time()))));
    }
    return 1;
}

public void
init()
{
    add_action(past, "past");
    add_action(present, "present");
    add_action(future, "future");
    ::init();
}

/*
 * Function name: remove_object
 * Description:   Save the time master when it is removed from the game
 */
public void
remove_object()
{
    save_master();
    ::remove_object();
}

/**************************************************************
 * help function that loads the flowcharts and the timable npcs.
 **************************************************************/
static void
load_one_flowchart(string file)
{
    mixed err = catch(file->create_flow());

    if (err)
        write_file("/d/Krynn/log/runtime", "RUNTIME ERROR while loading: " +
		   file + "\n      " + err + "\n\n");

    file->reboot_setup();
}

static void
do_load_flowcharts()
{
    mixed flows = get_dir(FLOWCHARTS);
    string file, str;
    int i;

    for(i = 0; i < sizeof(flows); i++)
    {
	file = FLOWCHARTS + flows[i];

	if (flows[i] && sscanf(file, "%s.c", str) == 1)
	    set_alarm(itof(i), 0.0, &load_one_flowchart(file));
    }
}

/***************************************************************
 * help functions to make the alarms 'reboot'.
 **************************************************************/
static varargs int
set_permanent_alarm(float tme, float rep, mixed arg1, mixed arg2, mixed arg3)
{
    int alarm_id = -1;

    if (!gCurrent_alarm)
        gCurrent_alarm = ([]);

    if (gCurrent_alarm[arg1])
        remove_alarm(gCurrent_alarm[arg1][0]);

    if (tme != 0.0)
    {
        if (tme > 0.0)
        alarm_id = set_alarm(tme, rep, &handle_event(arg1, arg2));
     else
        alarm_id = set_alarm(0.0, rep, &handle_event(arg1, arg2));
    }

    gCurrent_alarm += ([ arg1 : ({ alarm_id, time(), tme, rep, arg1, arg2, 
				   arg3 }) ]);

    return alarm_id;
}

static void
do_restore_object()
{
    int when, i, tmp;
    string thread;
    mixed all_values;

    restore_object(SAVE_ME);

    if (gCurrent_alarm && m_sizeof(gCurrent_alarm))
    {
	all_values = m_values(gCurrent_alarm);

	for (i = 0; i < sizeof(all_values); i++)
	    if (all_values[i] && sizeof(all_values[i]) > 6)
	    {
	        if (all_values[i][0] != -1)
	            when = ftoi(all_values[i][2]) + all_values[i][1] - time();
		else
		    when = 0;

		if (when < 0)
		  when = 500;

		thread = all_values[i][4];

		if (all_values[i][0])
		    tmp = set_permanent_alarm(itof(when),all_values[i][3],
					      thread, all_values[i][5],
					      all_values[i][6]);
		else
		    gCurrent_period[thread] = 0;
	    }
    }
    save_master();
}


/***************************************************************
 * Event and Period storing and retrieving
 **************************************************************/
public mixed
query_event(string name)
{
    return gEvent[name];
}

public mixed
query_period(string name)
{
    return gPeriod[name];
}

public string
query_current_period(string thread)
{
    return gCurrent_period[thread][0];
}

static void
end_current_period(string thread)
{
    int alarm_id;

    // Milan runtimes were here
    if (!sizeof(gCurrent_alarm[thread]))
    {    
        write_file("/d/Krynn/log/runtime", "RUNTIME ERROR: /d/Krynn/common/time_master\n" +
		   "     function end_current_period() called with wrong argument:\n" + 
		   "         " + thread + "\n\n");
	return;
    }
    alarm_id = gCurrent_alarm[thread][0];
    if (alarm_id > 0)
        remove_alarm(alarm_id);
}

/*
 * Function name: add_time_event
 * Description:   Add an event to the list
 * Arguments:     event - Name of the event
 *                period - Name of period following the event
 *                func - Name of a function to call as event
 */
public void
add_time_event(string event, string period, string func)
{
    if (!gEvent)
        gEvent = ([]);
    
    gEvent += ([ event : ({ period, func }) ]);
  
    save_master();  
}

public void
remove_time_event(string name)
{
    if (!gEvent)
        gEvent = ([]);
    
    gEvent = m_delete(gEvent, name);
    
    save_master();
}

/*
 * Function name: add_time_period
 * Description:   Add a period to the list
 * Arguments:     name - Name of the period
 *                length - Either (int) length of period
 *                         or (array)({a, b}) with length = a + random(b)
 *                event - Default event following end of period
 *                interrupts - List of events that can end this period
 *                             prematurely
 */
public varargs void
add_time_period(string name, mixed length, string event, mixed interrupts)
{
    if (!gPeriod)
        gPeriod = ([]);
    
    gPeriod += ([ name : ({ length, event, interrupts }) ]);
   
    save_master(); 
}

public void
remove_time_period(string name)
{
    if (!gPeriod)
        gPeriod = ([]);
    
    gPeriod = m_delete(gPeriod, name);
    
    save_master();
}

/* Period and Event Handler. These functions control time as it passes.
 * 1) Each event has a period following after it.
 * 2) Each period has a default event following after it, after a certain time.
 * 3) A period may be interrupted by another event, triggered by the game
 */
/*
 * Function name: handle_period
 * Description:   Handle a period
 * Arguments:     thread - The name of the thread
 *                name - The name of the period
 */
static void
handle_period(string thread, string name)
{
    mixed pe = query_period(name);
    mixed length = pe[0];
    string event = pe[1];
    int len;

    if (intp(length) && length > 0)
        len = length;
    else 
        if (pointerp(length))
            len = length[0] + random(length[1]);

    gLast_period[thread] = gCurrent_period[thread];
    gCurrent_period[thread] = ({ name, time() });
    set_permanent_alarm(itof(len), 0.0, thread, event);

    save_master();
}

/*
 * Function name: handle_event
 * Description:   Handle an event
 * Arguments:     thread - The name of the thread
 *                name - The name of the event
 */
static void
handle_event(string thread, string name)
{
    mixed ev = query_event(name);
    string period;
    string event;

    if (!ev || !sizeof(ev))
        return 0;

    period = ev[0];
    event = ev[1];

    call_other(FLOWCHARTS + thread, event);

    handle_period(thread, period);

    gLast_event[thread] = ({ name, time() });
    
    save_master();
}

/*
 * Function name: handle_interrupt
 * Description:   Handle an interrupt
 * Arguments:     thread - The name of the thread
 *                event - The name of the event
 */
public void
handle_interrupt(string thread, string event)
{
    /* check where interrupt comes from and see if it is relevant. */
    /* if it is relevant, remove alarm and perform event instead.  */
    end_current_period(thread);
    handle_event(thread, event);

    save_master();
}

/*
 * Function name: init_thread
 * Description:   Initialize a thread
 * Arguments:     name - The name of the thread
 *                event - The event to start on
 * Returns:       True if everything event ok, false otherwise
 */
public int
init_thread(string name, string event)
{
    if (gCurrent_period[name])
        return 0;

    handle_event(name, event);

    return 1;
}

/*
 * Function name: end_thread
 * Description:   End a thread
 * Arguments:     thread - The thread to end
 */
public void
end_thread(string thread)
{
    end_current_period(thread);

    gLast_period[thread] = gCurrent_period[thread];
    gLast_event[thread] = ({ "END THREAD", time() });

    gCurrent_period[thread] = 0;
    gCurrent_alarm[thread] = 0;

    save_master();
}

void
store_special_thread_info(string thread, mixed info)
{
    if (!special_thread_info)
        special_thread_info = ([]);

    special_thread_info += ([thread:info]);
}

mixed
query_special_thread_info(string thread)
{
    if (!special_thread_info)
      special_thread_info = ([]);
    
    return special_thread_info[thread];
}


int
remove_thread(string thread)
{
    gCurrent_period     = m_delete(gCurrent_period, thread);
    gLast_event         = m_delete(gLast_event, thread);
    gLast_period        = m_delete(gLast_period, thread);
    gCurrent_alarm      = m_delete(gCurrent_alarm, thread);
    special_thread_info = m_delete(special_thread_info, thread);
    write("Please make sure that the gEvent and gPeriod variables " +
	  "are cleaned up as well (by using remove_time_event and " +
	  "remove_time_period.\n");
    save_master();
    return 1;
}

