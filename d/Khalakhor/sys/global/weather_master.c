/* File         : /d/Khalakhor/sys/global/weather_master.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : December 3rd 1998
 * Purpose      : The Master file for the Khalakhor weather system
 * Related Files: /d/Khalakhor/std/room.c
 *                /d/Khalakhor/lib/weather_server.c
 * Comments     : DO NOT MODIFY THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING
 *                If you wish to use this code, please ask me first or
 *                if you can't find me try to give credit where credit
 *                is due ;-)
 *
 * Modifications: 
 */
#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/weather.h"

inherit "/d/Khalakhor/sys/global/weather_descriptions";

#define CHANGE_WEATHER  10
#define SAVE_FILE       "/d/Khalakhor/sys/global/weatherdata"

#define DEBUG_WHO   find_player("igneous")

#ifdef DEBUG_WHO
#define DEBUG(x)      DEBUG_WHO->catch_tell("WEATHER:  "+ x +"\n")
#else
#define DEBUG
#endif

//  Prototypes
void do_weather();
void init_region_mapping();

// Global Vars
string *Weather_servers;
int Weather_tells;
static mapping Region_info = ([]);

/* Function name: create 
 * Description:   The creation function... it sets up a few things.
 */
void
create()
{
    setuid(); seteuid(getuid());
    restore_object(SAVE_FILE);
    if (!pointerp(Weather_servers))
	Weather_servers = ({});
    init_region_mapping();
}

/* Function name: init_region_mapping
 * Description:   This function builds a mapping which contains what
 *                servers belong to each weather region.  This is done
 *                to cut down on the calls to all the servers to find
 *                out what the weather is for each region.
 */
void
init_region_mapping() 
{
    int i, j;
    mixed indices;

    i = -1;
    while(++i < sizeof(Weather_servers))
    {
	indices = m_indices(Weather_servers[i]->query_weather_info());
	j = -1;
	while(++j < sizeof(indices))
	    Region_info[indices[j]] = Weather_servers[i];
    }
}

/* Function name: add_weather_server
 * Description:   Adds a server to the Weather_server list 
 * Arguments:     string file:  The filename of the server
 * Returns:       1 if we added it, 0 if we didn't
 */
int
add_weather_server(string file)
{
    if (file_size(file) == -1)
    {
	write("The file "+file+" was invalid.\n");
	return 0;
    }
    if (!file->query_weather_server())
    {
	write("The file "+file+" was not a proper weather server.\n");
	return 0;
    }

    write("Adding "+file+" as a weather server.\n");
    Weather_servers += ({file});
    init_region_mapping();
    setuid(); seteuid(getuid());
    save_object(SAVE_FILE);
    return 1;
}

/* Function name: remove_weather_server
 * Description:   Removes a server from the Weather_server list
 * Arguments:     string file:  The filename we want to remove
 * Returns:       1 if we removed the file 0 if we didn't
 */
int
remove_weather_server(string file)
{
    if (member_array(file, Weather_servers) == -1)
    {
	write("The file "+file+" is not a listed weather server.\n");
	return 0;
    }
    Weather_servers -= ({file});
    init_region_mapping();
    setuid(); seteuid(getuid());
    save_object(SAVE_FILE);
    write("Removed "+file+" from the weather server list.\n");
    return 1;
}

/* Function name: query_weather_info
 * Description:   A query_function to get all the weather mappings.
 *                This is a service function so I can get all the 
 *                available information I can
 * Returns:       Returns a mapping of all the weather info
 */
mapping
query_weather_info()
{
    int i = -1;
    mapping info = ([]);

    while(++i < sizeof(Weather_servers))
	info += Weather_servers[i]->query_weather_info();

    return info;
}

/* Function name: query_weather
 * Description:   returns the current stauts of the weather in a region
 *                This function is the main function used in the 
 *                weather system so I've tried to make it as 
 *                efficent as I possibly can.
 * Arguments:     string region: The region we are interested in.
 * Returns:       The current weather of the region. 
 */
int
query_weather(string region)
{
    return Region_info[region]->query_weather_info()[region][CURRENT_WEATHER];
}

/* Function name: set_weather_region
 * Description:   This function automatically sets a region to a room
 *                when it is loaded _IF_ that room doesn't already have 
 *                a weather region set and is a valid room for the 
 *                weather master to add weather to. 
 * Arguments:     object room:  The room we are setting the weather 
 *                              region for 
 * Returns:       1 if a region was set, 0 if no region was set.
 */
int
set_weather_region(object room)
{
    string path = MASTER_OB(room);
    int i = -1, j;
    mapping info = query_weather_info();
    string *info_indices = m_indices(info);

    while (++i < sizeof(info_indices))
    {
	j = -1;
	while (++j < sizeof(info[info_indices[i]][REGION_PATHS]))
	{
	    if (wildmatch(info[info_indices[i]][REGION_PATHS][j] + "*", path))
	    {
		room->set_weather_region(info_indices[i]);
		return 1;
	    }
	}
    }
    return 0;
}

/* Function name: is_valid_player
 * Description:   A filter used to find valid players to send weather
 *                messages to.
 * Arguments:     object player: THe player we are checking 
 * Returns:       1 if the player is valid, 0 if invalid
 */
int
is_valid_player(object player)
{
    object env;

    if (!objectp(env = environment(player)))
	return 0;

    if (env->query_domain() != "Khalakhor")
	return 0;

    if (env->query_prop(ROOM_I_NO_WEATHER) ||
      env->query_prop(ROOM_I_INSIDE) || !strlen(env->query_weather_region()))
	return 0;

    return 1;
}

/* Function name: in_region
 * Description:   A Filter used to determine which region a player is in
 * Arguments:     object player:  The player we are testing
 *                string region:  The region we are testing
 * Returns:       1 if the player is in that region of Khalakhor
 */
int
in_region(object player, string region)
{
    if (environment(player)->query_weather_region() == region)
	return 1;

    return 0;
}

/* Function name: Do_weather
 * Description:   Does the filtering and the checks and balances to see
 *                if any weather related stuff happens.
 */
void
do_weather()
{
    object *to_tell, *players;
    string *regions = m_indices(Region_info);
    int i;

    players = filter(users() - ({0}), is_valid_player);

    if (!sizeof(players))
	return;

    Weather_tells += 1;
    if (Weather_tells > CHANGE_WEATHER)
    {
	Weather_servers->change_weather();
	Weather_tells = 0;
    }
    i = -1;
    while(++i < sizeof(regions))
    {
	to_tell = filter(players, &in_region(, regions[i]));
	if (sizeof(to_tell))
	{
	    players -= to_tell;
	    display_weather_message(to_tell, query_weather(regions[i]));
	}
	if (!sizeof(players))
	    break;
    }
}

// This function is added so that the weather does not happen
// exactly when the hour changes (since it is called
// from the clock when a new hour occurs)
void
do_weather_with_delay()
{
    set_alarm(itof(1 + random(180)), 0.0, do_weather);
}
/* Function name: query_prevent_shadow
 * Description:   We don't want this object to be shadowed
 * Returns:       1 to prevent shadowing
 */
int
query_prevent_shadow()
{
    return 1;
}

/* Function name: remove_object
 * Description:   A cleanup function to make sure data is saved
 */
public int
remove_object()
{
    save_object(SAVE_FILE);
    destruct();
    return 1;
}
