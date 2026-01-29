#include "defs.h"
inherit STD_DIR + "routine_status";

int      alarm;
float    repeat_delay = 10.0, start_delay = 0.0;
function interrupt_callback, routine_callback, stop_callback;

public void
routine()
{
    if (routine_callback)
        routine_callback();
}

public void
interrupt(int s)
{
    remove_alarm(alarm);
    if (interrupt_callback && s != STATUS["CANCELLED"])
        interrupt_callback(TO, s);
}

public void
stop(int s)
{
    remove_alarm(alarm);
    if (stop_callback && s != STATUS["CANCELLED"])
        stop_callback(TO, s);
    destruct();
}

public void
start()
{
    alarm = set_alarm(start_delay, repeat_delay, routine);
}

public void
resume()
{
    start();
}

public void
set_interrupt_callback(function callback)
{
    interrupt_callback = callback;
}

public void
set_routine_callback(function callback)
{
    routine_callback = callback;
}

public void
set_stop_callback(function callback)
{
    stop_callback = callback;
}

public void
set_start_delay(float delay)
{
    start_delay = delay;
}

public void
set_repeat_delay(float delay)
{
    repeat_delay = delay;
}

public void
create_routine()
{
}

public nomask void
create()
{
    create_routine();
}
