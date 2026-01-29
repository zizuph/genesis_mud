/*
 * Blah.
 */

#include "/d/Faerun/defs.h"

#pragma strict_types
#pragma no_clone
#pragma no_inherit
#pragma save_binary

static  int     alarm = 0;
static  int     index = 0;
static  object *rooms = ({});

#define TIMER     (10)       /* Our check time interval (in seconds) */
#define MAX_INDEX (1000000)  /* Prevent value from growing to large  */
#define CONSTANT_ALARM	     /* Do we allow the timer to run always? */

/*
 * Function Name: register_room
 * Description:   Registers the room with the telltimer so it knows it should
 *                check the room on a regular basis to determing if it needs
 *                to perform room_tells
 * Arguments:     object room - the room to register
 * Returns:       int 1 - room registered, 0 - room not registered
 *
 * Notes:         I am not bothering to do an array check simply because
 *                there is a simple check in the room_tell code to see
 *                if the room has already been registered or not, and also
 *                any duplicates will get caught in the filter function and
 *                dumped out due to additional safeguards in the code.
 */
public int
register_room(object room)
{
    if (!objectp(room))
        return 0;

    rooms += ({ room });

#ifndef CONSTANT_ALARM
    if (!alarm)
    {
	alarm = set_alarm(itof(TIMER), 0.0, &check_room_tells(TIMER));
    }
#endif
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
    return rooms + ({});
}

/*
 * Function name: unregister_room
 * Description	: Unregister a room manually from the rooms array, or
 *		  optionally clear out the rooms array completely.
 * Arguments	: mixed arg - objectp to room to remove,
 *			    - string "all" to dump all rooms.
 * Returns	: int - 1, success - 0, failure.
 */
public int
unregister_room(mixed arg)
{
    if (objectp(arg) && member_array(arg, rooms) >= 0)
    {
	rooms -= ({ arg });
	return 1;
    }

    if (stringp(arg) && arg == "all")
    {
	rooms = ({});
	return 1;
    }
    return 0;
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
 *                            again via internal alarm.  It will reset
 *                            itself back to 0 to prevent from growing
 *                            to large over the uptime of the mud.
 * Returns:       void
 */
private void
check_room_tells(int index)
{
    rooms = filter(rooms, &perform_room_tells(, index));

#ifndef CONSTANT_ALARM
    if (!sizeof(rooms))
    {
	alarm = 0;
        return;
    }
#endif

    alarm = set_alarm(itof(TIMER), 0.0, &check_room_tells(index + TIMER));
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

#ifdef CONSTANT_ALARM
    alarm = set_alarm(itof(TIMER), 0.0, &check_room_tells(TIMER));
#endif
}
