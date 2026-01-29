/*
 * Broadcast Module for Sparkle
 *
 * Created November 2008
 */
 
#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"
#include "/d/Sparkle/area/city/sys/broadcast_msgs.h"

inherit "/d/Sparkle/area/city/lib/utility_functions";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void         add_broadcast(string room, mixed rooms);
public string *     query_broadcast(string room);
private string *    query_broadcast_helper(string room);

// Global Variables
public mapping      broadcast_rooms;

// Defines
#define DATA        (DATA_DIR + "broadcast_rooms")

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    broadcast_rooms = ([ ]);

    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }
}

/*
 * Function:    clear_broadcast
 * Description: Removes all the entries from the broadcast
 *              room list for this room.
 */
public void
clear_broadcast(string room)
{
    m_delkey(broadcast_rooms, room);
    save_object(DATA);
}

/*
 * Function:        add_broadcast
 * Description:     This sets up a relationship between one room
 *                  and a list of other rooms that will receive
 *                  the broadcast.
 * Arguments:       room - the room that sends the broadcast
 *                  target_rooms - the list of rooms that will receive
 * Returns:         nothing
 */
public void
add_broadcast(string room, mixed rooms)
{
    string * valid_rooms, * target_rooms;
    
    // First we get all the existing rooms that we broadcast to    
    valid_rooms = query_broadcast(room);
    
    // The input can be either a string or an array of strings
    target_rooms = ({ });
    if (stringp(rooms))
    {
        target_rooms = ({ rooms });
    }
    else if (pointerp(rooms))
    {
        target_rooms = rooms;
    }
    
    // Add each valid room to the valid_rooms list
    foreach (string target : target_rooms)
    {
        if (objectp(safely_load_master_file(target))
            && !IN_ARRAY(target, valid_rooms))
        {
            valid_rooms += ({ target });
        }
    }
    
    // Set the broadcast rooms to the new list.
    broadcast_rooms[room] = valid_rooms;
    save_object(DATA);
}

/*
 * Function:        query_broadcast
 * Description:     Given a room (object or no-dir name) returns the
 *                  list of rooms should receive a broadcast from this
 *                  room.
 * Arguments:       room - the room that sends the broadcast
 * Returns:         list of rooms that should receive broadcasts
 */
public string *
query_broadcast(mixed room)
{
    string file;
    
    if (objectp(room) && IS_ROOM_OBJECT(room))
    {
        file = file_name(room);
        return query_broadcast_helper(file);
    }
    
    if (stringp(room))
    {
        return query_broadcast_helper(room);
    }
    
    return ({ });
}

/*
 * Function:        query_broadcast_helper
 * Description:     Function called by query_broadcast to actually look
 *                  things up in the mapping.
 * Arguments:       room - the string of the room that sends the broadcast
 * Returns:         list of rooms from the mapping to send broadcast to
 */
private string *
query_broadcast_helper(string room)
{
    if (!IN_ARRAY(room, m_indices(broadcast_rooms)))
    {
        return ({ });
    }
    
    return broadcast_rooms[room];
}

public int
observed_movement(object mover, object viewer)
{
    int sneak, awareness;

    if (mover == viewer
        || !mover->check_seen(viewer))
    {
        return 0;
    }
    
    sneak = mover->query_skill(SS_SNEAK);
    awareness = viewer->query_skill(SS_AWARENESS);

    if (awareness - random(90))
    {
        /* But! We don't want to base it entirely on the viewer.
         * If the mover has good sneak skill, we want to give
         * them a chance to foil the opportunity. 
         */
        if ((sneak - random(30)) < (awareness - random(50)))
        {
            /* If they have some form of enhanced speed, lets
             * give them one last flip of the coin.
             */
            if (mover->query_prop(LIVE_I_QUICKNESS) > 99)
            {
                if (random(2))
                {
                    return 1;
                }
            }
            else
            {
                return 1;
            }
        }
    }
    
    return 0;    
}

public int
query_room_type(object room)
{
    string file;
    
    if (!objectp(room) || !IS_ROOM_OBJECT(room))
    {
        return ROOM_TYPE_UNKNOWN;
    }    

    return room->query_broadcast_room_type();    
}

/*
 * Function name:        format_broadcast
 * Description  :        Because we want to do so much with met/nonmet
 *                       and the individual descriptions of movers, we
 *                       need a way to assign and replace placeholders
 *                       in the text. This function takes a given
 *                       text, searches for the break_string of
 *                       MOVER, and replaces it with the appropriate
 *                       call for the description of that mover.
 * Arguments    :        object mover - the one doing the moving
 *                       object viewer - the one seeing the mover
 *                       string bc - the broadcast message
 *                       string where - the type of area the mover is
 *                                      moving in. Default is set to a
 *                                      null string. Define this only
 *                                      if you need to replace the
 *                                      placeholder WHERE in the text.
 * Returns      :        string - the text with the appropriate text
 *                                inserted.
 */
public string
format_broadcast(object mover, string bc, string where = "")
{
    string rest;
    
    // If mover is in the beginning, we use QCTNAME instead.
    if (sscanf(bc, "MOVER %s", rest))    
    {
        bc = QCTNAME(mover) + " " + rest;
    }
    
    string *bc_text = explode(bc, "MOVER");
    string  mover_text = QTNAME(mover);
    string  formatted_text;

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, mover_text);
    }
    else
    {
        formatted_text = bc;
    }

    bc_text = explode(formatted_text, "WHERE");

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, where);
    }

    return formatted_text;
} /* format_broadcast */

public string
query_broadcast_message(object src_room, object dest_room, object mover, int arriving)
{
    string custom_message;
    int src_type, dest_type;
    
    // This allows each room to define their own custom broadcast messages
    custom_message = dest_room->query_custom_broadcast_message(src_room, mover, arriving);
    if (strlen(custom_message))
    {
        return custom_message;
    }
    
    src_type = query_room_type(src_room);
    dest_type = query_room_type(dest_room);
    
    switch (src_type)
    {
    case ROOM_TYPE_ROOF:
        if (dest_type != ROOM_TYPE_ROOF)
        {
            if (arriving)
            {
                return format_broadcast(mover, ROOF_TO_STREET_ARRIVE, "roof") + "\n";
            }
            else
            {
                return format_broadcast(mover, ROOF_TO_STREET_LEAVE, "roof") + "\n";
            }
        }
        break;
        
    case ROOM_TYPE_DOCK:
        break;
        
    case ROOM_TYPE_STREET:
    case ROOM_TYPE_UNKNOWN:
    default:
        if (dest_type == ROOM_TYPE_ROOF)
        {
            if (arriving)
            {
                return format_broadcast(mover, ALL_TO_ROOF_ARRIVE, "street") + "\n";
            }
            else
            {
                return format_broadcast(mover, ALL_TO_ROOF_LEAVE, "street") + "\n";
            }
        }
    }
    
    switch (arriving)
    {
    case 0:
        return QCTNAME(mover) + " leaves the room.\n";
    
    case 1:
        return QCTNAME(mover) + " arrives in the room.\n";
    }
    
    return "";
}

/*
 * Function name:        broadcast_movement
 * Description  :        When players move along rooftops or beneath
 *                       piers or sewer drains, they will sometimes
 *                       catch the eye of someone on the levels above
 *                       or below them. This function is called when 
 *                       the movement takes place.
 * Arguments    :        object who - the person doing the moving
 *                       int arriving - true if they are arriving to rather 
 *                                      than leaving from the location.
 *                       mixed exclude - rooms to exclude from broadcasting
 */
public void
broadcast_movement(object who, object src_room, int arriving, mixed exclude = 0)
{
    string * rooms;
    string broadcast_msg;
    
    rooms = query_broadcast(src_room);
    if (sizeof(exclude))
    {
        // We remove the excluded rooms so we don't broadcast to them.
        rooms -= exclude;
    }    
    foreach (string room_name : rooms)
    {        
        object room = safely_load_master_file(room_name);
        
        if (room == src_room)
        {
            // Don't allow broadcasts to the same room.
            continue;
        }
        
        object * observers = FILTER_LIVE(all_inventory(room));
        observers = filter(observers, &observed_movement(who, ));
        
        broadcast_msg = query_broadcast_message(src_room, room, who, arriving);
        if (strlen(broadcast_msg))
        {
            send_debug_message("broadcast", "broadcasting from "
                + file_name(src_room) + " to room " + room_name);
            observers->catch_msg(broadcast_msg);         
        }
    }
}
