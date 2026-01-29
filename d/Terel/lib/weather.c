/*
 * weather.c
 *
 * Manages the weather in Terel.
 *
 * Torm, June 2000
 */

#pragma save_binary
#pragma strict_types
#pragma no_inherit

inherit "/std/room";

#include "/d/Terel/include/Terel.h"
#include "weather.h"
#include <macros.h>
#include <std.h>

#define TORM(x) (find_player("torm")->catch_tell(x))

//** Global Variables **//

private static string *gAllRooms   = ({});
private static string *gAllRegions = ({});
private static int     gWeatherAlarm  = 0;

private mapping gWeatherMap = ([]);



public nomask void
create_room()
{
    FIX_EUID;

    set_short("Weather room");
    set_long("This is the weather room.\n");

    // make sure our weather map is populated
    if (!m_sizeof(gWeatherMap))
        restore_map(WEATHER_MAP);

    update_indices();

    // make sure the weather alarm is running 
//    if (!gWeatherAlarm)
//        gWeatherAlarm = set_alarm(1.0, 900.0, weather_change_effect);
}


public void
init()
{
    add_action(do_add_region,    "addregion");
    add_action(do_add_room,      "addroom"); 
    add_action(do_remove_region, "removeregion");
    add_action(do_remove_room,   "removeroom");
    add_action(do_set_weather,   "setweather");
}

private int
do_add_region(string s)
{
    string region;

    if (sscanf(s, "%s", region) != 1)
        return 0;       

    add_region(region);
    return 1;
}

private int
do_add_room(string s)
{
    string region;

    if (sscanf(s, "%s", region) != 1)
        return 0;       

    
    add_room_to_region(ENV(TP), region);
    return 1;
}

private int
do_remove_region(string s)
{
    string region;

    if (sscanf(s, "%s", region) != 1)
        return 0;       

    remove_region(region);
    return 1;
}

private int
do_remove_room(string s)
{
    string region;

    if (sscanf(s, "%s", region) != 1)
        return 0;       

    
    remove_room_from_region(ENV(TP), region);
    return 1;
}


private int
do_set_weather(string s)
{
    string weather_type, region;

    if (sscanf(s, "%s %s" , weather_type, region) != 2)
        return 0;

    set_weather_in_region(weather_type, region);
    return 1;
}

public int
add_region(string region)
{
    if (!stringp(region) || !strlen(region))
    {
        NF("Bad argument given when calling add_region.\n");
        return 0;
    }

    if (!security_check())
    {
        NF("You are not authorized to do that.\n");
        return 0;    
    }

    if (region_exists(region))
    {
        NF("That region already exists!\n");
        return 0;
    }

    // add the region and initialize it to default values
    gWeatherMap[region] = ({ DEFAULT_WEATHER, DEFAULT_ROOM });
    save_weather_state(REGION_ADDED, region);
    return 1;
}


public int
remove_region(string region)
{
    if (!stringp(region) || !strlen(region))
    {
        NF("Bad argument given when calling remove_region().\n");
        return 0;
    }

    if (!security_check())
    {
        NF("You are not authorized to do that.\n");
        return 0;    
    }

    if (!region_exists(region))
    {
        NF("No such region.\n");
        return 0;
    }

    gWeatherMap = m_delete(gWeatherMap, region);
    save_weather_state(REGION_REMOVED, region);
    return 1;

}


/*
 * function name : add_room_to_region
 * description   : Adds a room to a distinct weather region
 * arguments     : object room - The room to register in 'region'
 *                 string region - The region to register 'room' in
 * returns       : int - 0 upon failure, 1 on success
 */

public int
add_room_to_region(object room, string region)
{
    if (!objectp(room) || !stringp(region) || !strlen(region))
    {
        NF("Bad argument given when calling add_room_to_region().\n");
        return 0;
    }

    if (!security_check())
    {
        NF("You are not authorized to do that.\n");
        return 0;    
    }

    /* we will only allow new rooms to have weather. older rooms should be updated */
/*
    if (function_exists("create_terel_room", room) != MASTER_OB(room))
    {
        NF("This is not a suitable room.\n");
        return 0;
    }
*/

    if (room->query_prop(ROOM_I_INSIDE))
    {
        NF("Indoor rooms do not have weather.\n");
        return 0;
    }

    if (!region_exists(region))
    {
        NF("No such region.\n");
        return 0;
    }

    if (room_exists_in_any_region(room))
    {
        NF("This room is already registered.\n");
        return 0;
    }

    gWeatherMap[region][ROOMS_IN_REGION] += ({ MASTER_OB(room) });
    save_weather_state(ROOM_ADDED, region, MASTER_OB(room));
    return 1;
}

/*
 * function name : remove_room_from_region
 * description   : removes a room from a distinct weather region
 * arguments     : object room - The room to unregister in 'region'
 *                 string region - The region in which to unregister 'room'
 * returns       : int - 0 upon failure, 1 on success
 */

public int
remove_room_from_region(object room, string region)
{
    if (!objectp(room) || !stringp(region) || !strlen(region))
    {
        NF("Bad argument given when calling remove_room_from_region().\n");
        return 0;
    }

    if (!security_check())
    {
        NF("You are not authorized to do that.\n");
        return 0;    
    }

    /* we will only allow new rooms to have weather. older rooms should be updated */
    if (function_exists("create_terel_room", room) != STDROOM)
    {
        NF("You can't do that here!\n");
        return 0;
    }

    if (room->query_prop(ROOM_I_INSIDE))
    {
        NF("You can't do that here!\n");
        return 0;
    }

    if (!region_exists(region))
    {
        NF("No such region.\n");
        return 0;
    }

    if (!room_exists_in_region(room, region))
    {
        NF("That room does not exist in that region.\n");
        return 0;
    }

    gWeatherMap[region][ROOMS_IN_REGION] -= ({ MASTER_OB(room) });
    save_weather_state(ROOM_REMOVED, region, MASTER_OB(room));
    return 1;
}


public int
set_weather_in_region(string weather_type, string region)
{
    if (member_array(lower_case(weather_type), WEATHER_TYPES) == -1)
    {
        NF("No such weather type.\n");
        return 0;
    }

    if (!region_exists(region))
    {
        NF("No such region.\n");
        return 0;
    }

    gWeatherMap[region][WEATHER_IN_REGION] = weather_type;
    save_weather_state(WEATHER_CHANGED, region, "", weather_type);
}

private static void
weather_change_effect()
{
    // just log a change for now
    log_weather_action(WEATHER_CHANGED, NO_REGION, "", NO_WEATHER);
}


public string
weather_of_region(string region)
{
    if (member_array(region, gAllRegions) == -1)
    {
        NF("No such region.\n");
        return 0;
    }

    return gWeatherMap[region][WEATHER_IN_REGION];
}
public string
weather_of_room(object room)
{
    int region_index;
    string room_path = MASTER_OB(room);

    if (function_exists("create_terel_room", room) != STDROOM)
        return "You see no weather patterns here.\n";   

    if (member_array(room_path, gAllRooms) == -1)
        return "You see no weather patterns here.\n";

    return weather_of_region(region_of_room(room_path));
}


//************************* Helper functions **************************//

private static varargs void
log_weather_action(int action, string region, string room, string weather)
{
    string event;

    switch (action)
    {
        case ROOM_ADDED:
            event = "Room "+room+" added to "+region+" region";
            break;
        case ROOM_REMOVED:
            event = "Room "+room+" removed from "+region+" region";
            break;
        case REGION_ADDED:
            event = "Region "+region+" was created";
            break;
        case REGION_REMOVED:
            event = "Region "+region+" was removed";
            break;
        case WEATHER_CHANGED:
            event = "Weather updated to "+weather+" in region "+region;
            break;
        default:
            event = "Unknown Action: action = ("+action+") region = ("+region+") room = ("+room+") weather = ("+weather+")";
            break;     
    }

    write(event+"\n");
    write_file(WEATHER_LOG, "["+ctime(time())+"] "+event+" by "+TP->query_real_name()+"\n");
}

private static int
region_exists(string region)
{
    return (member_array(region, gAllRegions) != -1);
}

private static string
region_of_room(string room)
{
    mixed *regions = m_indices(gWeatherMap);
    int i, region_count = sizeof(regions);
    string *region_rooms;


    if (member_array(room, gAllRooms) == -1)
        return NO_REGION;

    for (i = 0; i < region_count; i++)
    {
        region_rooms = gWeatherMap[regions[i]][ROOMS_IN_REGION];
        if (member_array(room, region_rooms) != -1)
            return regions[i];
    }

    return NO_REGION;
}

private static int
room_exists_in_any_region(object room)
{
    return (member_array(MASTER_OB(room), gAllRooms) != -1);
}

private static int
room_exists_in_region(object room, string region)
{
    return (member_array(MASTER_OB(room), gWeatherMap[region][ROOMS_IN_REGION]) != -1);
}

private static varargs void
save_weather_state(int action, string region, string room, string weather)
{
    save_map(gWeatherMap, WEATHER_MAP);
    update_indices();
    log_weather_action(action, region, room, weather);
}

private static int
security_check()
{
    if ((SECURITY->query_wiz_dom(TP->query_real_name()) == "Terel") &&
        (SECURITY->query_wiz_rank(TP->query_real_name()) >= WIZ_NORMAL))
    {
        return 1;
    }

    return 0;
}

private static void
update_indices()
{
    int region_index, region_count;
    mixed *regions, *rooms = ({});

    gAllRegions  = 0;
    gAllRooms    = 0;
    if (!m_sizeof(gWeatherMap))
        return;

    regions  = m_indices(gWeatherMap);
    region_count = sizeof(regions);
    for (region_index = 0; region_index < region_count; region_index++)
        rooms += gWeatherMap[regions[region_index]][ROOMS_IN_REGION] + ({});

    gAllRegions = regions + ({});
    gAllRooms = rooms + ({});
}

private static float
weather_change_time() 
{ 
    return (WEATHER_CHANGE_TIME_BASE + itof(random(WEATHER_CHANGE_TIME_RANDOM))); 
}





