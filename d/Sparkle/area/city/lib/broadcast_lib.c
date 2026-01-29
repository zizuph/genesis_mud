/*
 * Broadcast Library
 *
 * Inherit from this library if you want to support broadcasting in your
 * rooms.
 *
 * Created by Petros, November 2008
 */

#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"

// Global variables
public int      broadcast_room_type = ROOM_TYPE_UNKNOWN;

/*
 * Function:    query_custom_broadcast_message
 * Description: Use this function to describe how you want to receive
 *              movement messages from the other room.
 * Arguments:   src_room - the room the movement occurred in
 *              mover    - the person moving
 *              arriving - 0/1 - leaving/arriving
 * Returns:     custom string or ""
 */
public string
query_custom_broadcast_message(object src_room, object mover, int arriving)
{
    return "";
}

/*
 * Function:    clear_broadcast_rooms
 * Description: Remove all broadcast rooms from this room.
 *              This is called first before registering new
 *              rooms inside of the create_room in the
 *              sparkle_room_base.
 */
public void
clear_broadcast_rooms()
{
    BC_MODULE->clear_broadcast(file_name(this_object()));
}

/* 
 * Function:    register_broadcast_rooms
 * Description: Make calls to this function to register your
 *              rooms to broadcast to. The function can take in
 *              either a roomfile or an array of roomfiles.
 *              Example of Usage:
 *                register_broadcast_rooms( ({ STREET_DIR + "center_g" }) );
 *                register_broadcast_rooms(STREET_DIR + "center_a");
 */
public void
register_broadcast_rooms(mixed rooms)
{
    BC_MODULE->add_broadcast(file_name(this_object()), rooms);
}

/* 
 * Function:    query_broadcast_rooms
 * Description: Returns a full list of the roms that are currently
 *              being broadcast to.
 */
public string *
query_broadcast_rooms()
{
    return BC_MODULE->query_broadcast(this_object());
}

/*
 * Function:    query_broadcast_room_type
 * Description: The room type is used to determine the type of message
 *              that gets displayed by default.
 * Arguments:   none
 * Returns:     Room type of these types
                #define ROOM_TYPE_UNKNOWN   0
                #define ROOM_TYPE_STREET    1
                #define ROOM_TYPE_ROOF      2
                #define ROOM_TYPE_DOCK      3
 */ 
public int
query_broadcast_room_type()
{
    return broadcast_room_type;
}

/*
 * Function:    set_broadcast_room_type
 * Description: Sets the room type in the broadcast so that
 *              it can determine what to display when it formats
 *              the broadcast messages.
 *              See all defined types in defs.h.
 */
public void
set_broadcast_room_type(int type)
{
    broadcast_room_type = type;
}
