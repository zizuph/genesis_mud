/*
 * Much improved room_tell system by Lucius.
 *
 * Revisions:
 *     Lucius, Jul 2017: Minor fixes and cleanups.
 */
#pragma no_clone
#pragma no_inherit
#pragma strict_types

public static int alarm = 0;
public static object *rooms = ({ });

private void check_room_tells(int index);

#define TIMER     (10)       /* Our check time interval (in seconds) */
#define TIMERF    (10.0)     /* Float value of TIMER */

/*
 * Function Name: register_room
 * Description:   Registers the room with the telltimer so it knows it should
 *                check the room on a regular basis to determing if it needs
 *                to perform room_tells
 * Arguments:     object room - the room to register
 * Returns:       int 1 - room registered, 0 - room not registered
 */
public int
register_room(object room)
{
    if (!objectp(room))
        return 0;

    rooms += ({ room });

    if (!alarm)
	alarm = set_alarm(TIMERF, 0.0, &check_room_tells(TIMER));

    return 1;
}

/*
 * Function Name: registered_rooms
 * Description:   Returns on object array of all the currently registred
 *                rooms.  Usefull only for debugging purposes...
 * Arguments:     none
 * Returns:       object *rooms - array of registered rooms
 */
public object *
registered_rooms(void)
{
    return secure_var(rooms);
}

/*
 * Function name: unregister_room
 * Description	: Unregister a room manually from the rooms array, or
 *		  optionally clear out the rooms array completely.
 * Arguments	: mixed arg - objectp to room to remove,
 *			    - string "all" to dump all rooms.
 * Returns	: void
 */
public void
unregister_room(mixed arg)
{
    if (objectp(arg))
	rooms -= ({ arg });
    else if (stringp(arg) && (arg == "all"))
	rooms = ({ });
}

/*
 * Function Name: perform_room_tells
 * Description:   Called by check_room_tells as a filter function to
 *                perform room tells in registered rooms, and also to
 *                determine if we need to continue to check all the rooms.
 * Arguments:     object room - the room currently being checked.
 * Returns:       int 2: No, but keep checking anyways... ;)
 *                    1: Yes, tell was performed, keep checking...
 *                    0: No, and don't bother with this room until it
 *                       gets re-registered...
 */
private int
perform_room_tells(object room, int index)
{
    return room->do_room_tell(index);
}

/*
 * Function Name: check_room_tells
 * Description:   Called by an internal alarm within the telltimer object
 *                to have it perform room tells in registered rooms.
 * Arguments:     int index - This keeps track of the running time and
 *                            incremented and passed onto this function
 *                            again via internal alarm.
 * Returns:       void
 */
private void
check_room_tells(int index)
{
    alarm = 0;
    rooms = filter(rooms, &perform_room_tells(, index));

    if (sizeof(rooms))
	alarm = set_alarm(TIMERF, 0.0, &check_room_tells(index + TIMER));
}

/*
 * Function Name: stop_telltimer
 * Description:   Stops the telltimer alarm, then destructs the telltimer
 *                object itself.  Used to turn off room tells globally.
 * Arguments:     none
 * Returns:       void
 */
public void
stop_telltimer(void)
{
    map(rooms, &->stop_room_tells());
    remove_alarm(alarm);
    destruct();
}

/*
 * Function Name: create
 * Descriptoin:   Creates the object and starts the telltimer alarm.
 * Arguments:     none
 * Returns:       void
 */
private void
create(void)
{
    setuid();
    seteuid(getuid());
}
