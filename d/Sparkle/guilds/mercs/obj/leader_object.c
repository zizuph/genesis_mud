/*
 * leader_object.c
 * 
 * A player has this object when leading a steed.
 * 
 * Copyright by Wout de Zeeuw, Fysix@Genesis, Sep 2002
 * 
 */
inherit "/std/object";

#include <stdproperties.h>

#define STEED_S_LAST_COMMAND	("_steed_s_last_command")

object steed;
object leader;

void create_object()
{
    set_name("__leader_object");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
}

/* Function name: set_steed
 * Description:   Set the steed for which this leader object is meant.
 * Arguments:     object steed
 */
public void set_steed(object o)
{
    steed = o;
}

/* Function name: query_steed
 * Description:   Query the steed for which this leader object is meant.
 * Returns:       object steed
 */
public object query_steed()
{
    return steed;
}

/* Function name: set_leader
 * Description:   Set the leader for which this leader object is meant.
 * Arguments:     object leader
 */
public void set_leader(object o)
{
    leader = o;
}

/* Function name: query_leader
 * Description:   Query the leader for which this leader object is meant.
 * Returns:       object leader
 */
public object query_leader()
{
    return leader;
}

/* Action. See steed.c#unlead */
public int unlead(string s)
{
    return steed->unlead(s);
}

/* Capture the command to use for moving the steed */
public int capture_command(string s)
{
    environment(this_object())->add_prop(STEED_S_LAST_COMMAND, s);
    return 0;
}

/* Adds the actions. */
public void init()
{
    add_action(capture_command, "", 1);
    add_action(unlead, "unlead");
    ::init();
}
