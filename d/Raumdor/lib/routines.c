#pragma strict_types
#include "defs.h"

int current_routine = -1,
    schedule_changed = 0,
    schedule_index,
    *simple_alarms = ({}),
    *simple_routines = ({}),
    *routine_schedule = ({});
float *simple_delays = ({});
mixed *Routines = ({});

int
add_routine(function start, function stop, function interrupt, function resume)
{
    Routines += ({({start, stop, interrupt, resume})});
    return sizeof(Routines) - 1;
}

void
simple_stop(int num)
{
    remove_alarm(simple_alarms[num]);
}

void
simple_interrupt(int num)
{
    simple_stop(num);
}

void
simple_start(int num)
{
    simple_alarms[num] = set_alarm(0.0, simple_delays[num],
      simple_routines[num]);
}

void
simple_resume(int num)
{
    simple_start(num);
}

int
add_simple_routine(function f, float delay)
{
    int i = sizeof(simple_routines);
    simple_alarms += ({0});
    simple_delays += ({delay});
    simple_routines += ({f});
    return add_routine(&simple_start(i), &simple_stop(i), &simple_interrupt(i),
      &simple_resume(1));
}

void
interrupt_routine()
{
    if (current_routine >= 0)
        Routines[current_routine][2]();
}

void
resume_routine()
{
    if (current_routine >= 0)
        Routines[current_routine][3]();
}

void
stop_routine()
{
    if (current_routine >= 0)
    {
        Routines[current_routine][1]();
        if (!schedule_changed && sizeof(routine_schedule) &&
          schedule_index < sizeof(routine_schedule))
        {
            current_routine = routine_schedule[schedule_index];
            schedule_index++;
            Routines[current_routine][0]();
            schedule_index++;
        }
        else
            current_routine = -1;
    }
}   

void
start_routine(int num)
{
    stop_routine();
    if (num < 0 || num >= sizeof(Routines))
        throw("Argument num out of range.\n");
    current_routine = num;
    Routines[num][0]();
}

void
set_routine_schedule(int *schedule)
{
    schedule_changed = 1;
    routine_schedule = schedule;
}

void
start_schedule()
{
    schedule_index = 0;
    schedule_changed = 0;
    start_routine(routine_schedule[0]);
}
