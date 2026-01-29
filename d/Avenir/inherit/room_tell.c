/*
 * Alternate room_tell system by Lucius.
 *
 * Revisions:
 * 	Lucius, APR 2016: Added skip_room_tells function and modified
 * 	                  the do_room_tell code to use it as a filter.
 */
#pragma no_clone
#pragma strict_types

private static int      registered;
private static int      time_index;
private static int      last_index;
private static mapping  tell_list = ([]);
private static string  *temp_list = ({});

/* Define this to have a 1 out of () chance of skipping tells */
#define RANDOM_TELL_CHANCE	(5)
/* Defined path to the telltimer object for registration */
#define TELLTIMER          ("/d/Avenir/inherit/telltimer")

/*
 * Function name: skip_room_tells
 * Description	: This function may be masked and is called via filter()
 *                to determine if any players should be skipped for tells.
 * Arguments	: Object who - The interactive we are querying against
 * Returns	: Integer - 1 (default) = Receive room tells
 *                          0 = Skip tells for <who>
 */
public int
skip_room_tells(object who)	{ return 1; }

/*
 * Function name: start_room_tells
 * Description	: Registers this room with the master telltimer object.
 * Arguments	: None
 * Returns	: Void
 */
public static void
start_room_tells(void)
{
    if (!registered && m_sizeof(tell_list))
	registered = TELLTIMER->register_room(this_object());
}

/*
 * Function name: stop_room_tells
 * Description	: Called by the telltimer object to reset registered state.
 * Arguments	: None
 * Returns	: Void
 */
public static void
stop_room_tells(void)
{
    registered = 0;
    last_index = 0;
    temp_list = ({});
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
 *                     1000-2000 will be randomly assigned to it.
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
	int *rval = ({});

	foreach(string tmp : str)
	    rval += ({ add_tell(tmp) });

	return filter(rval, &operator(>)(,0));
    }
    else if (!strlen(str))
    {
	return 0;
    }

    if (!intp(id) || id < 1)
        id = (1000 + random(1000));

    if (str[-1..] == "\n") 
	str = str[..-2];

    tell_list[str] = id;
    return id;
}

/*
 * Function Name: remove_tell
 * Description:   Remove a specific tell from the list of tells.
 * Arguments:     arg: the tell to remove from the present list
 *                   or the id of the tell to remove, can be an array.
 * Returns:       1 if success, 0 if fail
 */
public int
remove_tell(mixed arg)
{
    int match;

    if (pointerp(arg))
    {
	int *rval = ({});

	foreach(mixed val : arg)
	    rval += ({ remove_tell(val) });

	return sizeof(rval);
    }
    else if (strlen(arg) && tell_list[arg])
    {
	match = 1;
        m_delkey(tell_list, arg);
    }
    else if (intp(arg))
    {
	foreach(string str, int val : tell_list)
	{
	    if (val == arg)
	    {
		match++;
		m_delkey(tell_list, str);
	    }
	}
    }

    return match;
}

/*
 * Function Name: query_tells
 * Description:   The indices of tell_list.
 * Returns:       mixed *
 */
public mixed *
query_tells(void)
{
    return m_indices(tell_list);
}

/*
 * Function Name: query_tells_map
 * Description:   The mapping tell_list
 * Returns:       mixed mapping
 */
public mapping
query_tells_map(void)
{
    return m_indices(tell_list);
}

/*
 * Function Name: query_tells_left
 * Description:   An array of the tells left to be displayed
 * returns:       mixed *
 */
public mixed *
query_tells_left(void)
{
    return secure_var(temp_list);
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
    object *whom;

    /* Paranoi check */
    if (!registered)
	return 0;

#if RANDOM_TELL_CHANCE
    if (!random(RANDOM_TELL_CHANCE))
        return 4;
#endif

    /* Did we already performed a tell this cycle? */
    if (index == last_index)
        return 3;

    /* Are we supposed to perform a tell this cycle? */
    if ((index % time_index) != 0)
        return 2;

    /* Are there tells to give? */
    if (!m_sizeof(tell_list))
        return registered = 0;

    /* Are there players present? */
    if (!sizeof(whom = filter(all_inventory(), query_interactive)))
        return registered = 0;

    /* Are there players wanting tells? */
    if (!sizeof(whom = filter(whom, skip_room_tells)))
        return registered = 0;

    if (!sizeof(temp_list))
        temp_list = m_indices(tell_list);

    tmp = one_of_list(temp_list);
    temp_list -= ({ tmp });
    last_index = index;

    if (stringp(tmp = this_object()->check_call(tmp)))
    	whom->catch_vbfc(tmp + "\n");

    return 1;
}
