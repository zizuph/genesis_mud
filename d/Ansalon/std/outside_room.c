inherit "/d/Krynn/std/outside_room.c";
#include "/d/Ansalon/common/defs.h";
#include <filter_funs.h>

int events_on,events_running;
string *event_list;
float start_time;
float repeat_time;

string *
query_events()
{
    return event_list;
}

void
set_event_time(float start, float repeat)
{
    if(start)
        start_time = start;
    if(repeat)
        repeat_time = repeat;
}

void
init()
{
    ::init();
    if(events_on && interactive(TP) && events_running == 0)
    {
        events_running = 1; 
        set_alarm(start_time,0.0,"run_events");
    }
}

void
run_events()
{
    int index,num;
    num = sizeof(event_list);
    if(!num)
    {
        events_running = 0;
        return;
    }
    index = random(num);
    tell_room(TO,event_list[index]);
    if(sizeof(FILTER_PLAYERS(all_inventory(TO))) && events_on)
        set_alarm(repeat_time,0.0,"run_events");
    else
        events_running = 0;
}


void
set_events_on(int i)
{
    if(i)
    {
        events_on = 1;
        events_running = 0;
    }
    else
        events_on = 0;
}

int
add_event(string event)
{
    if(!event_list)
        event_list = ({});
    if(!event)
        return 0;
    event_list += ({event});
    return 1;
}


