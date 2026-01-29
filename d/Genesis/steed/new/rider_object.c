/*
 * rider_object.c
 * 
 * A player has this object when mounted on a steed.
 * 
 * Copyright by Wout de Zeeuw, Fysix@Genesis, Sep 2002
 * 
 * Added a weight and volume of zero - Arman, March 2018
 * 
 */
inherit "/std/object";

#include <stdproperties.h>

object steed;
object rider;

void create_object()
{
    set_name("__rider_object");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

/* Function name: set_steed
 * Description:   Set the steed for which this rider object is meant.
 * Arguments:     object steed
 */
public void set_steed(object o)
{
    steed = o;
}

/* Function name: query_steed
 * Description:   Query the steed for which this rider object is meant.
 * Returns:       object steed
 */
public object query_steed()
{
    return steed;
}

/* Function name: set_rider
 * Description:   Set the rider for which this rider object is meant.
 * Arguments:     object rider
 */
public void set_rider(object o)
{
    rider = o;
}

/* Function name: query_rider
 * Description:   Query the rider for which this rider object is meant.
 * Returns:       object rider
 */
public object query_rider()
{
    return rider;
}

/* Action. See steed.c#dismount */
public int dismount(string s)
{
    return steed->dismount(s);
}

/* Action. See steed.c#do_auto_mount */
public int auto_mount(string s)
{
    return steed->do_auto_mount(s);
}

/* Action. See steed.c#auto_dismount */
public int auto_dismount(string s)
{
    return steed->do_auto_dismount(s);
}

/* Adds the actions. */
public void init()
{
    add_action(dismount, "dismount");
    add_action(auto_mount, "automount");
    add_action(auto_dismount, "autodismount");
    ::init();
}
