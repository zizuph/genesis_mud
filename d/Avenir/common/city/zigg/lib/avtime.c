#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

inherit "/d/Avenir/inherit/avenir_time";

private static object *events = ({});

/*
 * We are masking this function from the avenir_time.c
 * It notifies us of the change of hours once every hour.
 */
public void
avenir_time_callout(int year, int week, int day, int hour)
{
    /*
     * Run through events
     * Events that wish to remain running should return a 'true' value.
     * Otherwise, false '0' should be returned so it gets filtered out.
     */
    events = filter(events, &->avenir_event(year, week, day, hour));
}

private void
create(void)
{
    setuid();
    seteuid(getuid());

    start_avtime();
}

/********************************************************************
 * The event handling semantics
 */

/*
 * Register an event.
 */
public void
add_event(object ob)
{
    if (objectp(ob) && (member_array(ob, events) == -1))
	events += ({ ob });
}

/*
 * Remove a registered event.
 */
public void
rem_event(object ob)
{
    events -= ({ ob });
}

/*
 * What events are waiting?
 */
public void
query_events(void)
{
    return secure_var(events);
}

public object
get_this_object(void)
{
    return this_object();
}
