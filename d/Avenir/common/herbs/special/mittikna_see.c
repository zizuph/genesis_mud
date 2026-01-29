// mittikna_see, cloned by /d/Avenir/common/herb/mittikna
//
// * Lucius Mar 2009: Changed to not be domain limited and
// 	    re-based on the new nethra water breathing object.
//
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Avenir/include/basic.h"

/* Pre-remove warn interval. */
#define WARN_INT	30
/* Default object id. */
#define ADS_CHECK_ID	"avenir::darkvision"

public static int alarm_id;
public static string object_id;


public nomask void
set_object_id(string what)	{ object_id = what; }

public nomask string
query_object_id(void)		{ return object_id; }

public void
create_object(void)
{
    set_no_show();
    set_name("av_darksight");
    set_object_id(ADS_CHECK_ID);

    add_prop(OBJ_M_NO_DROP, 1);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
}

public nomask void
remote_remove(void)
{
    /* Called when a new object is taking over.
     * Only kill the alarm and destruct.
     */
    if (alarm_id)
	remove_alarm(alarm_id);

    ::remove_object();
}

/*
 * Function name: hook_worn_off
 * Description	: Inform that this darkvision object has worn off.
 * Arguments	: object who - Who the object wore off from.
 * 		    int prop - Now current status of LIVE_I_SEE_DARK.
 */
public void
hook_worn_off(object who, int prop)
{
    who->catch_tell("Your ability to discern objects in the "+
	"dark has diminished.\n");
    
    if (!prop && !CAN_SEE_IN_ROOM(who))
    {
	who->catch_tell("Darkness coats your vision as "+
	    "your eyes fail to pierce it.\n");
    }
}

/*
 * Function name: hook_worn_off
 * Description	: Warn that this darkvision object is wearing out.
 * Arguments	: object who - Who the object we are warning.
 * 		    int prop - Now would-be status of LIVE_I_SEE_DARK.
 */
public void
hook_warning(object who, int prop)
{
    who->catch_tell("Your vision flickers with a black halo, "+
	"a warning that one of your enhancements is about to fail.\n");
}

public nomask void
remove_object(void)
{
    object who = environment();

    if (!objectp(who) || !living(who))
    {
	::remove_object();
	return;
    }

    ALTER_PROP(who, LIVE_I_SEE_DARK, -1);

    int prop = who->query_prop(LIVE_I_SEE_DARK);
    hook_worn_off(who, (prop > 0 ? 1: 0));

    ::remove_object();
}

private nomask void
warn_remove(void)
{
    object who = environment();
    int prop = who->query_prop(LIVE_I_SEE_DARK);

    hook_warning(who, (prop > 0 ? 1: 0));
    alarm_id = set_alarm(itof(WARN_INT), 0.0, remove_object);
}

public nomask int
query_time(void)
{
    mixed alarm;

    if (alarm_id && sizeof(alarm = get_alarm(alarm_id)))
	return ftoi(alarm[2]);

    return 0;
}

public nomask void
add_time(int num)
{
    num += (query_time() - WARN_INT);

    if (num < 1)
	return;

    if (alarm_id)
	remove_alarm(alarm_id);

    alarm_id = set_alarm(itof(num), 0.0, warn_remove);
}

public nomask void
set_time(int num)	{ add_time(num); }

/*
 * Function name: hook_add_vision
 * Description	: Inform that this darkvision object has been added.
 * Arguments	: object who - Who the object was added to.
 * 		    int more - If true, then we are adding time.
 * 		               If false, we were newly added.
 */
public void
hook_add_vision(object who, int more)
{
    who->catch_tell("Your vision blurs for a moment as your "+
	"sensitivity to light "+ ( more ?
	    "is strengthened" : "has changed") +
	", enabling your eyes to pierce the dark.\n");
}

public nomask void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
    {
	::remove_object();
	return;
    }

    if (objectp(from = present(object_id, to)))
    {
	add_time(from->query_time());
	set_alarm(0.0, 0.0, &from->remote_remove());
    }
    else
    {
	ALTER_PROP(to, LIVE_I_SEE_DARK, 1);
    }

    add_name(object_id);
    hook_add_vision(to, objectp(from));
}
