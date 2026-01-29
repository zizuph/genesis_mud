#pragma strict_types

#include "defs.h"

inherit ROOMBASE;

private object * entered_players = ({ });

/*
 * Funstion:	    query_is_monk_quest_room
 * Description:	    Check to see if the specified room is a monk
 *		    quest room.
 * Arguments:	    room: The room to check, or 0 to check the current
 *		    room (which will always return true, since anything
 *		    inheriting this file is a quest room).
 * Returns:	    1 if the specified or called room is a quest
 *		    room, 0 otherwise.
 */
public varargs int 
query_is_monk_quest_room (object room = 0)
{
    if (!room)
	return 1;
    else
	return room->query_is_monk_quest_room ();
}

/* 
 * Function:     may_enter_quest_rooms
 * Description:  Check to see if a player may enter the quest
 *	         rooms. Only one player at a time may be in the
 *	         rooms.
 * Returns:      1 if they player may enter the rooms, 0 if not.
 */
public int 
may_enter_quest_rooms ()
{
    object *all_rooms = map (users (), environment);
    object statueroom;

    // include linkdead players: don't want people going LD
    // so their buddy's can get in ;)
    if ((statueroom = find_object (OWN_STATUE)) && 
	sizeof (all_inventory (statueroom)))
	all_rooms += all_inventory (statueroom)->query_prop (LIVE_O_LAST_ROOM);

    if (sizeof (filter (all_rooms, query_is_monk_quest_room)) > 0)
	return 0;
    else
	return 1;
}

