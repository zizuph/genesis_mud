#pragma strict_types
/* Water resistance from the Nethra herb
 * Cirion, July 1996
 * Updated from water_resistance, by Glinda
 *
 * Lucius, Jan 2009: Re-write to make more robust and fix bugs.
 * 	Object to be shared between Nethra herbs, Hizarbin altar(s),
 * 	and anything else that needs magic water breathing.
 * Lucius, Jan 2009: Re-wrote some bits to make more generic/inheritable.
 *                   Added usage example.
 */
/*
 * INHERIT USAGE:
 *
 * If you want to share messages and usage with the standard object,
 * then do nothing. You can simply clone instead of inherit.
 *
 * If you do wish to have custom messages or other properties, then
 * after inheriting, mask create_object and hook_worn_off:
 *
 *    public void
 *    create_object(void)
 *    {
 *        ::create_object();
 *
 *        set_object_id("MY OBJECT ID");
 *        <... Other Customization ...>
 *    }
 *
 *    public void
 *    hook_worn_off(object who, int prop)
 *    {
 *        if (prop)
 *        {
 *            who->catch_tell(
 *                "Your ability to breathe underwater is reduced.\n");
 *        }
 *        else
 *        {
 *            who->catch_tell(
 *                "Your ability to breathe underwater is GONE!\n");
 *        }
 *    }
 */  
inherit "/std/object";

#include <stdproperties.h>
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/water.h"

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
    set_name("water_breathe");
    set_object_id(MBW_CHECK_ID);

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
 * Description	: Inform that this water breathing object has worn off.
 * Arguments	: object who - Who the object wore off from.
 * 		    int prop - Now current status of the MAGIC_I_BREATHE_WATER
 * 		               prop on 'who' after worn off.
 */
public void
hook_worn_off(object who, int prop)
{
    who->catch_tell("The air tastes normal again.\n");

    if (!prop && UNDER_WATER(ENV(who)))
    {
	who->catch_tell("You suddenly find you cannot breathe, "+
	    "and the water around seem to press on you with "+
	    "a menacing hand!\n");
    }
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

    ALTER_PROP(who, MAGIC_I_BREATH_WATER, -1);

    int prop = who->query_prop(MAGIC_I_BREATH_WATER);

    if (--prop <= 0)
	who->remove_prop(MAGIC_I_BREATH_WATER);
    else
	who->add_prop(MAGIC_I_BREATH_WATER, prop);

    hook_worn_off(who, (prop > 0 ? prop : 0));

    ::remove_object();
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
    num += query_time();

    if (num < 1)
	return;

    if (alarm_id)
	remove_alarm(alarm_id);

    alarm_id = set_alarm(itof(num), 0.0, remove_object);
}

public nomask void
set_time(int num)	{ add_time(num); }

/*
 * Function name: hook_add_breathe
 * Description	: Inform that this water breathing object has been added.
 * Arguments	: object who - Who the object was added to.
 * 		    int more - If true, then we are adding breathing time.
 * 		               If false, we were newly added.
 */
public void
hook_add_breathe(object who, int more)
{
    /*
     * We don't do anything by default, leaving it to the
     * cloning code to print messages.
     */
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
	ALTER_PROP(to, MAGIC_I_BREATH_WATER, 1);
    }

    add_name(object_id);
    hook_add_breathe(to, objectp(from));
}

