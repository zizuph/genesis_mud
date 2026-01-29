#include "defs.h"
inherit STD_DIR + "routine_status";

object current_routine, *schedule = ({});

// Prototypes
void start_routine(object routine);

// Add something to run next on the schedule, like a stack
public void
push_routine(object routine)
{
    schedule = ({routine}) + schedule;
}

// Add something to the end of a schedule
public void
queue_routine(object routine)
{
    schedule += ({routine});
}

public object *
query_schedule()
{
    return schedule;
}

private object
dequeue_routine()
{
    object result;
    if (!sizeof(schedule))
        return 0;

    result = schedule[0];
    schedule = schedule[1..];
    return result;
}

void
schedule_ended()
{
}

void
stop_schedule()
{
    if (current_routine)
        current_routine->stop(STATUS["CANCELLED"]);
}

void
start_schedule()
{
    if (current_routine || !(current_routine = dequeue_routine()))
        return;
    start_routine(current_routine);
}

void
clear_schedule()
{
    if (current_routine)
        stop_schedule();
    foreach (object routine: schedule)
        routine->destruct();
}

void
interrupt_current_routine(int s)
{
    if (current_routine)
        current_routine->interrupt(s);
}

void
stop_current_routine(int s)
{
    if (current_routine)
        current_routine->stop(s);
}

void
resume_current_routine()
{
    if (current_routine)
        current_routine->resume();
}

void
routine_interrupted(object routine, int event)
{
    set_alarm(10.0, 0.0, resume_current_routine); 
}

void
routine_stopped(object routine, int event)
{
    current_routine = dequeue_routine();
    if (!current_routine)
        schedule_ended();
    else
        start_routine(current_routine);    
}

void
start_routine(object routine)
{
    routine->set_interrupt_callback(routine_interrupted);
    routine->set_stop_callback(routine_stopped);
    routine->start();
}

