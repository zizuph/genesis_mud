/*
 * leader_object.c
 * 
 * A player has this object when leading a steed.
 * For each steed he is leading he has a leader_object.
 * This is because every steed may have a different 
 * implementation of the leader_object.
 * 
 * Copyright by Wout de Zeeuw, Fysix@Genesis, Sep 2002
 * 
 */
inherit "/std/object";

#include <stdproperties.h>

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

/* Adds the actions. */
public void init()
{
    add_action(unlead, "unlead");
    ::init();
}
