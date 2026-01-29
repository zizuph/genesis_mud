/*
 * Blah.
 */

#pragma save_binary
#pragma strict_types
#pragma no_clone

#include "/d/Faerun/defs.h"

private static int      registered;
private static int      time_index;
private static int      last_index;
private static mapping  tell_list = ([]);
private static string  *temp_list = ({});

/* Define this to have a 1 out of () chance of skipping tells */
#define RANDOM_TELL_CHANCE	(5)
/* Defined path to the telltimer object for registration */
#define TELLTIMER          ("/d/Faerun/lib/telltimer")

/*
 * Function name: register_room
 * Description	: Registeres this room with the master telltimer object.
 * Arguments	: None
 * Returns	: void
 */
public static void
register_room(void)
{
    if (!registered && m_sizeof(tell_list))
	registered = TELLTIMER->register_room(this_object());
}

/*
 * Function name: start_room_tells
 * Description	: Legacy function, do not use in new code.
 * Arguments	: None
 * Returns	: Void
 */
public static void
start_room_tells(void)
{
    register_room();
}

/*
 * Function Name: set_tell_time
 * Description:   Set the mean value for room_tell interval
 * Arguments:     time: Interval
 *                if 'time' == -1; sets the tell timer to 0.
 * Returns:       void
 */
public void
set_tell_time(int time)
{
    if (time == -1)
    {
        time_index = 0;
        return;
    }

    if (time < 10)
    {
        time = 10;
    }

    time = (time / 10);
    time_index = (time * 10);
}

/*
 * Compat function.
 */
public void
set_atmosphere_interval(int time)
{
    set_tell_time(time);
}

/*
 * Function Name: query_tell_time
 * Description:   returns the tell_time index
 * Returns:       (int) time_index
 */
public int
query_tell_time(void)
{
    return time_index;
}

/*
 * Function Name: add_tell
 * Description:   Add's a tell to the rooms tell listings
 * Arguments:     str: The text of the desired message, can be VBFC
 *                id:  A numeric id to assign this tell which can be
 *                     used later to make removing it easier.
 *                     If you do not specify an id, a number between
 *                     100-200 will be randomly assigned to it.
 * Returns:       0 if fail, else returns the 'id' value
 * Note		: Updated 'str' arg to be an array.  However, id's do
 *		  currently get processed (assigned randomly) for now.
 *		  Also returns an array of the 'id' values.
 */
public varargs mixed
add_tell(mixed str, int id)
{
    if (pointerp(str))
    {
	int ix = -1, sz = sizeof(str), *rval = ({});
	while(++ix < sz)
	{
	    rval += ({ add_tell(str[ix]) });
	}
	return rval;
    }
    else if (!stringp(str) || str == "")
    {
	return 0;
    }

    if (!intp(id) || id < 1)
    {
        id = (100 + random(100));
    }

    if (str[strlen(str)-1] == '\n') 
	str = str[..-2];

    tell_list[str] = id;
    return id;
}

/*
 * Compat function.
 */
public int
add_atmosphere(mixed str)
{
    return add_tell(str);
}

/*
 * Function Name: remove_tell
 * Description:   Remove a specific tell from the list of tells.
 * Arguments:     arg: the tell to remove from the present list
 *                   or the id of the tell to remove.
 * Returns:       1 if success, 0 if fail
 */
public int
remove_tell(mixed arg)
{
    string *list;
    int    size;

    if (stringp(arg) && intp(tell_list[arg]))
    {
        tell_list = m_delete(tell_list, arg);
    }
    else if (intp(arg))
    {
	list = m_indices(tell_list);
	size = sizeof(list);
	while(size--)
	{
	    if (tell_list[list[size]] == arg)
	    {
		tell_list = m_delete(tell_list, list[size]);
	    }
	}
    }
    else
    {
        return 0;
    }
    return 1;
}

/*
 * Compat function.
 */
public int
remove_atmosphere(mixed arg)
{
    return remove_tell(arg);
}

/*
 * Function Name: query_tells
 * Description:   Print the array tell_list
 * Returns:       tell_list
 */
public string *
query_tells(void)
{
    return m_indices(tell_list) + ({});
}

/*
 * Function Name: query_tells_left
 * Description:   Print out an array of the tells left to be displayed
 * returns:       temp_list
 */
public string *
query_tells_left(void)
{
    return temp_list + ({});
}

/*
 * Function Name: clear_tells
 * Description:   Clears ALL tells.
 * Returns:       Void
 */
public void
clear_tells(void)
{
    tell_list = ([]);
    temp_list = ({});
}

/*
 * Function Name: clear_temp_tells
 * Description:   Clears out the temp tells array
 *                Use this if you added/removed tells and need the
 *                change reflected immediately.
 * Returns:       void
 */
public void
clear_temp_tells(void)
{
    temp_list = ({});
}

/*
 * Function:    do_room_tell()
 * Description: Perform one tell in the room.
 * Arguments:   time counter
 * Returns:     0 - Do not perform a tell, and prevent further checking
 *                  of this room
 *              1 - Room tell performed
 *              2 - Room tell NOT performed, but don't unregister the room
 *
 * Note:        This function should ONLY be called from the telltimer.
 */
public int
do_room_tell(int index)
{
    mixed tmp;

    if (!registered)
    {
	/* paranoi check */
	return 0;
    }

#ifdef RANDOM_TELL_CHANCE
    if (!random(RANDOM_TELL_CHANCE))
    {
        return 2;
    }
#endif

    if (index == last_index)
    {
	/* we already performed a tell this cycle */
        return 2;
    }

    if ((index % time_index) != 0)
    {
	/* we aren't supposed to perform a tell this cycle */
        return 2;
    }

    if (!m_sizeof(tell_list))
    {
	/* no tells to give, don't bother */
        return registered = 0;
    }

    if (!sizeof(filter(all_inventory(this_object()), interactive)))
    {
	/* no players, don't bother */
        return registered = 0;
    }

    if (!(tmp = sizeof(temp_list)))
    {
        tmp = sizeof(temp_list = m_indices(tell_list));
    }

    tmp = temp_list[random(tmp, time())];
    temp_list -= ({ tmp });
    last_index = index;

    if (stringp(tmp = this_object()->check_call(tmp)))
        tell_room(this_object(), tmp + "\n");

    return 1;
}
