/*******************************************************
 *   To be inherited by all rooms in Raumdor
 *******************************************************/

#pragma save_binary
#pragma strict_types

#include "defs.h"
inherit "/std/room";
inherit LIB_DIR + "time";
inherit LIB_DIR + "room_tell";

/***************************************************************
 *   Globals
 ***************************************************************/
static string day_desc = "", night_desc = "";

void
init()
{
    ::init();
    init_time();

    int *thereCoords,*hereCoords = TO->query_coordinates();
    object room;
    mixed *rooms = query_exit();
    string dir;
    if (sizeof(hereCoords) != 3)
    {
        KLOG("coords_not_found", MASTER_OB(TO));
        return;
    }
    for (int i = 0; i < sizeof(rooms) / 3; i+=3)
    {
        if (!strlen(rooms[i]))
            continue;
        room = check_call(rooms[i]);
        if (!objectp(room))
        {
            room = find_object(rooms[i]);
            if (!objectp(room))
            {
                if (LOAD_ERR(rooms[i]))
                {
                    KLOG("coords_room_error", rooms[i]);
                    continue;
                }
                room = find_object(rooms[i]);
            }
        }
        if (!room)
           continue;
        thereCoords = room->query_coordinates();
        if (sizeof(thereCoords) != 3)
        {
            KLOG("coords_not_found", MASTER_OB(room));
            continue;
        }
        dir = rooms[i+1];
        if (dir == "north" || dir == "northwest" || dir == "northeast")
            thereCoords[1] -= 1;
        if (dir == "south" || dir == "southwest" || dir == "southeast")
            thereCoords[1] += 1;
        if (dir == "east" || dir == "northeast" || dir == "southeast")
            thereCoords[0] -= 1;
        if (dir == "west" || dir == "northwest" || dir == "southwest")
            thereCoords[0] += 1;
        else if (dir == "up")
            thereCoords[2] -= 1;
        else if (dir == "down")
            thereCoords[2] += 1;
        
        for (int j = 0; j < 3; j++)
        {
            if (hereCoords[j] != thereCoords[j])
            {
                KLOG("coords_inconsistent",
                        MASTER_OB(TO) + " " + dir + " " + MASTER_OB(room));
                break;
            }
        }
    }
}

/****************************************************************
 * Function: set_time_desc()
 * Args: day_desc   - the daytime description
 *       night_desc - the nighttime description
 *
 * Set the day and night time descriptions for your room.
 ****************************************************************/
public void
set_time_desc(string day_str, string night_str)
{
    day_desc   = day_str;
    night_desc = night_str;
}

/****************************************************************
 * Function: query_time_desc()
 *
 * Will return the time description for the room. If no time
 * description has been set and the room is an outdoor room in
 * Kabal, the default description will be used, unless you set
 * the property ROOM_NO_TIME_DESC in the room. For any other room,
 * without a description set, no description will be used. Got it?
 ****************************************************************/
public string
query_time_desc()
{
    if (TO->query_prop(ROOM_NO_TIME_DESC))
        return "";

    if (DAY)
        return day_desc;

    return night_desc;
}

/****************************************************************
 * Function: long()
 *
 * This will append the time desciption of the room to the long
 * description set with set_long(), unless no long has been set.
 *
 * Note: This added time description will show up only when people
 *       look at the room but will not show up when query_long()
 *       is called.
 ****************************************************************/
varargs public mixed long(string str, object for_obj)
{
    if (str)
        return ::long(str, for_obj);

    return ::long(str, for_obj) + query_time_desc();
}

/*******************************************************
 *   Function: create_room()
 *
 *   Set defaults for our rooms.
 *******************************************************/
public void
create_room()
{
    // This is silly
    int inside = query_prop(ROOM_I_INSIDE);
    ::create_room();
    if (inside)
        add_prop(ROOM_I_INSIDE, inside);

    if (!query_prop(ROOM_I_INSIDE))
        set_time_desc(
          "The sky is obscurred by dark heavy clouds that blocks the rays of the sun.\n",
          "Storm clouds loom overhead, casting darkness over the land.\n");
}
