/*
 *  /d/Sparkle/area/city/lib/broadcast_master.c
 *
 *  This module is responsible for controlling which rooms in the city of
 *  Sparkle broadcast movements that occur within them to other locations
 *  in town. For example, someone moving along a rooftop might be seen 
 *  by people on the street. Likewise, someone moving below a dock might
 *  attract the attention of someone standing on the dock.
 *
 *  Locations can broadcast to more than one room.
 *
 *  Created November 2008, by Petros and Gorboth (Cooper Sherry)
 */
 
#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"
#include "/d/Sparkle/area/city/sys/broadcast_msgs.h"


/* Global Variables */
public mapping     Broadcast_Mapping;
public object      Broadcast_Mover; /* Who is doing the moving?          */
public object      Broadcast_Viewer; /* Who is viewing the moving?       */
public string      Bc_Arrive_Msg = ""; /* Message to display to certain rooms
                                        * connected to this one when an
                                        * interactive enters.            */
public string      Bc_Leave_Msg = "";  /* Same as above, but for leaving.*/
public string      Spied_Msg = ""; /* Location text to display when people
                                    * in this location are seen from afar*/
public string     *Broadcast_Rooms; /* Array of the filenames of rooms 
                                     * that should receive potential   
                                     * messages when people enter or leave
                                     * this room.                        */ 
public string     *Unique_Broadcast; /* Special broadcasts defined by an
                                      * individual room to override the
                                      * defaults.
                                      *    element 0: arrive_msg
                                      *    element 1: leave_msg          */

/* Prototypes */
public void        add_broadcast(string room, string * target_rooms);
public void        query_broadcast(string room);
private string *   query_broadcast_helper(string room);
public string      format_broadcast(object mover, object viewer, string bc, string where = "");
public void        config_broadcasts(object who, object viewer);
public void        broadcast_movement(object who, int arriving);
public void        set_bc_arrive(string s)     { Bc_Arrive_Msg = s; }
public void        set_bc_leave(string s)       { Bc_Leave_Msg = s; }
public void        set_spied(string s)             { Spied_Msg = s; }
public void        set_bc_rooms(string *s)   { Broadcast_Rooms = s; }
public void        set_unique_bc(string *s) { Unique_Broadcast = s; }
public string *    query_bc_rooms()       { return Broadcast_Rooms; }
public string      query_bc_arrive()        { return Bc_Arrive_Msg; }
public string      query_bc_leave()          { return Bc_Leave_Msg; }
public string      query_spied_msg()            { return Spied_Msg; }
public object      query_bc_mover()       { return Broadcast_Mover; }
public object      query_bc_viewer()      { return Broadcast_Viewer;}

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
add_broadcast(string room, string * target_rooms)
{
    Broadcast_Mapping[room] = target_rooms;
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
        file = explode(file_name(room), "/")[-1..][0];
        return query_broadcast_helper(file);
    }
    
    if (stringp(room))
    {
        return query_broadcast_helper(room);
    }
    
    return ({ });
}

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    Broadcast_Mapping = ([ ]);
    add_broadcast("center_a", ({  }));
    add_broadcast("center_b", ({  }));
    add_broadcast("center_c", ({  }));
    add_broadcast("center_d", ({  }));
    add_broadcast("center_e", ({  }));
    add_broadcast("center_f", ({  }));
    add_broadcast("center_g", ({ STREET_DIR + "center_a", STREET_DIR + "center_b" }));
    add_broadcast("corset_square", ({  }));
    add_broadcast("east_1a", ({  }));
    add_broadcast("east_1b", ({  }));
    add_broadcast("east_1c", ({  }));
    add_broadcast("east_1d", ({  }));
    add_broadcast("east_1e", ({  }));
    add_broadcast("east_2a", ({  }));
    add_broadcast("east_2b", ({  }));
    add_broadcast("east_2c", ({  }));
    add_broadcast("east_2d", ({  }));
    add_broadcast("east_2e", ({  }));
    add_broadcast("east_2f", ({  }));
    add_broadcast("east_2g", ({  }));
    add_broadcast("east_3a", ({  }));
    add_broadcast("east_3b", ({  }));
    add_broadcast("east_3c", ({  }));
    add_broadcast("lars_square", ({  }));
    add_broadcast("magic_shop", ({  }));
    add_broadcast("magic_shop_store", ({  }));
    add_broadcast("market_square", ({  }));
    add_broadcast("market_square2", ({  }));
    add_broadcast("memory_lane", ({  }));
    add_broadcast("north_a", ({  }));
    add_broadcast("north_b", ({  }));
    add_broadcast("north_c", ({  }));
    add_broadcast("north_d", ({  }));
    add_broadcast("north_e", ({  }));
    add_broadcast("north_f", ({  }));
    add_broadcast("north_g", ({  }));
    add_broadcast("north_h", ({  }));
    add_broadcast("north_i", ({  }));
    add_broadcast("north_j", ({  }));
    add_broadcast("north_jetty1", ({  }));
    add_broadcast("north_jetty2", ({  }));
    add_broadcast("north_k", ({  }));
    add_broadcast("north_l", ({  }));
    add_broadcast("north_m", ({  }));
    add_broadcast("north_n", ({  }));
    add_broadcast("northeast_1a", ({  }));
    add_broadcast("northeast_1b", ({  }));
    add_broadcast("northeast_2a", ({  }));
    add_broadcast("northeast_2b", ({  }));
    add_broadcast("northeast_2c", ({  }));
    add_broadcast("northeast_2d", ({  }));
    add_broadcast("northeast_2e", ({  }));
    add_broadcast("northeast_2f", ({  }));
    add_broadcast("northeast_3a", ({  }));
    add_broadcast("northeast_3b", ({  }));
    add_broadcast("northeast_3c", ({  }));
    add_broadcast("northeast_3d", ({  }));
    add_broadcast("northeast_3e", ({  }));
    add_broadcast("northeast_3f", ({  }));
    add_broadcast("northeast_3g", ({  }));
    add_broadcast("northeast_3h", ({  }));
    add_broadcast("northeast_3i", ({  }));
    add_broadcast("northeast_4a", ({  }));
    add_broadcast("northeast_4b", ({  }));
    add_broadcast("northeast_4c", ({  }));
    add_broadcast("northeast_4d", ({  }));
    add_broadcast("northwest_a", ({  }));
    add_broadcast("northwest_b", ({  }));
    add_broadcast("northwest_c", ({  }));
    add_broadcast("northwest_d", ({  }));
    add_broadcast("northwest_e", ({  }));
    add_broadcast("south_1a", ({  }));
    add_broadcast("south_1b", ({  }));
    add_broadcast("south_1c", ({  }));
    add_broadcast("south_1d", ({  }));
    add_broadcast("south_1e", ({  }));
    add_broadcast("south_2a", ({  }));
    add_broadcast("south_2b", ({  }));
    add_broadcast("south_2c", ({  }));
    add_broadcast("south_jetty1", ({  }));
    add_broadcast("south_jetty2", ({  }));
    add_broadcast("south_jetty3", ({  }));
    add_broadcast("southeast_a", ({  }));
    add_broadcast("southeast_b", ({  }));
    add_broadcast("southeast_c", ({  }));
    add_broadcast("southeast_d", ({  }));
    add_broadcast("southeast_e", ({  }));
    add_broadcast("southwest_1a", ({  }));
    add_broadcast("southwest_1b", ({  }));
    add_broadcast("southwest_1c", ({  }));
    add_broadcast("southwest_1d", ({  }));
    add_broadcast("southwest_1e", ({  }));
    add_broadcast("southwest_2a", ({  }));
    add_broadcast("southwest_2b", ({  }));
    add_broadcast("southwest_2c", ({  }));
    add_broadcast("southwest_2d", ({  }));
    add_broadcast("southwest_2e", ({  }));
    add_broadcast("southwest_3a", ({  }));
    add_broadcast("southwest_3b", ({  }));
    add_broadcast("streetmap.t", ({  }));
    add_broadcast("west_a", ({  }));
    add_broadcast("west_b", ({  }));
    add_broadcast("west_c", ({  }));
    add_broadcast("west_d", ({  }));
    add_broadcast("west_e", ({  }));
    add_broadcast("white_sands1", ({  }));
    add_broadcast("white_sands2", ({  }));    
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
    if (!IN_ARRAY(room, m_indices(Broadcast_Mapping)))
    {
        return ({ });
    }
    
    return Broadcast_Mapping[room];
} /* query_broadcast_helper */


/*
 * Function name:        format_broadcast
 * Description  :        Because we want to do so much with met/nonmet
 *                       and the individual descriptions of movers, we
 *                       need a way to assign and replace placeholders
 *                       in the text. This function takes a given
 *                       text, searches for the break_string of
 *                       MOVER, and replaces it with the appropriate
 *                       call for the description of that mover.
 *                       Then, it does the same thing, searching for
 *                       the break_string of WHERE and replaces it with
 *                       the string defined by the variable 'where'.
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
format_broadcast(object mover, object viewer, string bc, string where = "")
{
    string *bc_text = explode(bc, "MOVER");
    string  mover_text = mover->query_art_name(viewer);
    string  formatted_text;

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, mover_text);
        return capitalize(formatted_text);
    }
    else
    {
        formatted_text = bc;
    }

    bc_text = explode(bc, "WHERE");

    if (sizeof(bc_text) > 1)
    {
        formatted_text = implode(bc_text, where);
    }

    return formatted_text;
} /* format_broadcast */


/*
 * Function name:        config_broadcast
 * Description  :        determine what should be broadcast
 * Arguments    :        who - the person broadcasting their movements
 *                       viewer - the one who will see them
 */
public void
config_broadcasts(object who, object viewer)
{
    string *bc_rooms = BC_MODULE->query_broadcast(this_object());

    if (sizeof(bc_rooms))
    {
        set_bc_rooms(bc_rooms);
    }

    if (!sizeof(Unique_Broadcast))
    {
        switch (this_object()->query_street())
        {
            case STREET_CENTER:
            case STREET_SOUTHEAST:
            case STREET_SOUTH_1:
            case STREET_SOUTH_2:
            case STREET_SOUTHWEST_1:
            case STREET_SOUTHWEST_2:
            case STREET_SOUTHWEST_3:
            case STREET_WEST:
            case STREET_NORTHWEST:
            case STREET_NORTH:
            case STREET_NORTHEAST_1:
            case STREET_NORTHEAST_2:
            case STREET_NORTHEAST_3:
            case STREET_NORTHEAST_4:
                Bc_Arrive_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_ARRIVE, "street");
                Bc_Leave_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_LEAVE, "street");
                break;
            case STREET_EAST_1:
            case STREET_EAST_2:
            case STREET_EAST_3:
                Bc_Arrive_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_ARRIVE, "docks");
                Bc_Leave_Msg = format_broadcast(who, viewer,
                    ALL_TO_ROOF_LEAVE, "docks");
                break;
        }
    }
    else
    {
        Broadcast_Mover = who;
        Broadcast_Viewer = viewer;
        Bc_Arrive_Msg = format_broadcast(who, viewer, Unique_Broadcast[0]);
        Bc_Leave_Msg = format_broadcast(who, viewer, Unique_Broadcast[1]);
    }

    Bc_Arrive_Msg += "\n";
    Bc_Leave_Msg += "\n";     
} /* config_broadcasts */


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
 */
public void
broadcast_movement(object who, int arriving)
{
    object  room;
    mixed  *viewers;
    int     seen_moving = 0; /* is the player seen moving? */
    int     awareness;       /* the awareness of the viewer */
    int     sneak;           /* the sneak skill of the mover */
    string  check_bc = ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg);

    if (!sizeof(Broadcast_Rooms))
    {
        /* There are no rooms that are supposed to see this movement
         * designated, so lets drop here.
         */
        return;
    }

    foreach(string bc_room: Broadcast_Rooms)
    {
        TELL_G("bc_room = " + bc_room);
        room = find_object(bc_room);
        viewers = FILTER_LIVE(all_inventory(room));

        if (!sizeof(viewers))
        {
            /* Apparently, there are no viable targets who might hope
             * to see the movement, so we drop.
             */
            return;
        }

        /* We need to know if the person moving more than eight feet
         * tall. Huge beings are always seen! (Sorry Ogres!)
         */
        seen_moving = who->query_prop(CONT_I_HEIGHT) > 243;
        sneak = who->query_skill(SS_SNEAK);

        foreach(object viewer: viewers)
        {
            awareness = viewer->query_skill(SS_AWARENESS);

            /* The viewer gets a % chance to see the movement based on
             * their awareness.
             */
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
                    if (who->query_prop(LIVE_I_QUICKNESS) > 99)
                    {
                        if (random(2))
                        {
                            seen_moving = 1;
                        }
                    }
                    else
                    {
                        seen_moving = 1;
                    }
                }
            }

            if (viewer == who)
            {
                /* we don't want to see a message about ourself! */
                return;
            }

            if (seen_moving)
            {
                config_broadcasts(who, viewer);
                check_bc = ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg);

                if (!strlen(check_bc))
                {
                    /* No message has been set, so we drop. */
                    return;
                }

                viewer->catch_tell(
                    ((arriving) ? Bc_Arrive_Msg : Bc_Leave_Msg));
            }
        }
    }

    return;
} /* broadcast_movement */