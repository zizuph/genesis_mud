#pragma strict_types
#pragma save_binary

inherit "/d/Krynn/std/room.c";
#include <filter_funs.h>

private int events_on,events_running;
private string *event_list;
private float start_time;
private float repeat_time;

public void
set_event_time(float start, float repeat)
{
    if(start)
        start_time = start;
    if(repeat)
        repeat_time = repeat;
}

public void
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
    tell_room(this_object(),event_list[index]);
    if(sizeof(FILTER_PLAYERS(all_inventory(this_object()))) && events_on)
        set_alarm(repeat_time, 0.0, run_events);
    else
        events_running = 0;
}

public string *
query_events()
{
    return event_list;
}


public void
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

public int
add_event(string event)
{
    if(!event_list)
        event_list = ({});
    if(!event)
        return 0;
    event_list += ({event});
    return 1;
}

public void
init()
{
    ::init();
    if(events_on && interactive(this_player()) && events_running == 0)
    {
        events_running = 1; 
        set_alarm(start_time, 0.0, run_events);
    }
}
