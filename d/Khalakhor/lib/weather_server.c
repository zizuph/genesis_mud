/* File         : /d/Khalakhor/lib/weather_server.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : December 3rd 1998
 * Purpose      : A lib to be inherited as a weather server.
 * Related Files: /d/Khalakhor/std/room.c
 *                /d/Khalakhor/sys/global/weather.c
 * Comments     : DO NOT MODIFY THIS FILE UNLESS YOU KNOW WHAT YOU ARE DOING
 *
 * Modifications: 
 */

#include "/d/Khalakhor/sys/weather.h"
#include "/d/Khalakhor/sys/defs.h"


mapping Info;
static string Save_file;

/* Function name: create_weather_server()
 * Description:   creation function to allow customization for a server.
 */
void create_weather_server() {}

/* Function name: create
 * Description:   A creation function used to set up a few things
 */
void
create()
{
    create_weather_server();
    if (!stringp(Save_file)) 
	return;
    setuid(); seteuid(getuid());
    restore_object(Save_file);
    if (!mappingp(Info))
	Info = ([]);
}

/* Function name: set_save_file
 * Description:   sets up the save file.
 * Agruments:     string file: The file name of the save file
 */
void
set_save_file(string file)
{
    Save_file = file;
}

/* Function name: query_weather_server
 * Description:   Lets us know if this is a weather server.
 * Returns:       1
 */
int
query_weather_server()
{
    return 1;
}

int
legal_weather(string region, int weather)
{
    int flag;

    // These elements can not exsist by themselves
    if (weather == WIND || weather == PRECIP || weather == FREEZING)
    {
	// If all else fails clouds go with everything!!
	weather = weather | CLOUD;
	flag = 1;
    }

    // Only 2 types of extremes so we check thoose.
    if ((weather & EXTREMES) &&
      weather != TSTORM && weather != BLIZZARD)
    {
	// Take out the EXTREMES if it is an invalid one
	weather = weather ^ EXTREMES;
	flag = 1;
    }

    // You can't have rain without clouds
    if ((weather & PRECIP) && !(weather & CLOUD))
    {
	weather = weather | CLOUD;
	flag = 1;
    }

    // Now see if this weather is banned in this region
    if (member_array(weather, Info[region][BANNED_WEATHER]) != -1)
    {
	weather = Info[region][CURRENT_WEATHER];
	flag = 1;
    }

    // If we have no weather we'll make is sunny
    if (!weather)
    {
	weather = SUNNY;
	flag = 1;
    }
    return (flag ? weather : 0);
}

/* Function name:  change_weather_hook
 * Description:    A hook that is to be used to alter the chances of 
 *                 certain weather for a region.  Mask it if you wish
 *                 to alter the default here.
 * Arguments:      string region:  The weather region we are changing
 */
void
change_weather_hook(string region)
{
    int element, weather, temp;

    element = ONE_OF(Info[region][POSSIBLE_WEATHER]);
    weather = Info[region][CURRENT_WEATHER];

    weather = weather ^ element;
    if (temp = legal_weather(region, weather))
    {
	weather = temp;
    }
    Info[region][CURRENT_WEATHER] = weather;
}

/* Function name: change_weather
 * Description:   Changes the current weather for all the regions 
 *                stored within this weather server.
 * Arguments:     string region: What region we wish to change (optional)
 *                int weather:   Weather we want to change to  (optional)
 */
varargs void
change_weather(string region, int weather)
{
    int i;
    string *indices;

    if (pointerp(Info[region]) && !legal_weather(region, weather))
    {
	Info[region][CURRENT_WEATHER] = weather;
    }
    else
    {
	indices = m_indices(Info);
	i = -1;
	while (++i < sizeof(indices))
	{
	    change_weather_hook(indices[i]);
	}
    }
    setuid(); seteuid(getuid());
    save_object(Save_file);
}

/* Function name: query_weather_info
 * Description:   A query function for all the information this 
 *                server contains
 * Returns:       mapping of the weather info.
 */
mapping
query_weather_info()
{
    return Info;
}

/* Function name: add_weather_region
 * Description:   Adds a region and all possible weather to this server.
 *
 * IMPORTANT!!    No error checking is done in this function so make
 *                sure your data is correct.
 *
 * Arguments:     string region  What region we are adding
 *                string *dirs:  Array of directories for this region
 *                int *possible: Possible weather elements for this region
 *                int *banned:  Weather combos we don't want here
 * Returns:       1 if we added this region 0 if we didn't
 */
varargs int
add_weather_info(string region, string *dirs, int *possible, int *banned)
{
    if (!pointerp(Info[region]))
    {
	if (!pointerp(dirs))
	    dirs = ({dirs});
	if (!pointerp(possible))
	    possible = ({possible});
	if (!pointerp(banned))
	    banned = ({banned});
	Info[region] = ({dirs, possible, banned, 
	  (random(2) ? SUNNY : CLOUDY) });
	setuid(); seteuid(getuid());
	save_object(Save_file);
	WEATHER_MASTER->init_region_mapping();
	write("Region "+region+" added.\n");
	return 1;
    }
    write("Region "+region+" already exists.\n");
    return 0;
}

/* Function name: remove_weather_info
 * Description:   Removes a region from the server
 * Arguments:     string region:  The region we want to remove
 * Returns:       True if we removed the region 0 if we did not
 */
int
remove_weather_info(string region)
{
    if (!pointerp(Info[region]))
    {
	write("Region "+region+" does not exist.\n");
	return 0;
    }
    WEATHER_MASTER->init_region_mapping();
    write("Removing "+region+"...\n");
    Info = m_delete(Info, region);
    setuid(); seteuid(getuid());
    save_object(Save_file);
    return 1;
}

/* Function name: modify_dir_info
 * Description:   Allows you to remove or add a directory to a region
 * Arguments:     string region:  The region we are modifying
 *                string dir:     The directory we are adding or removing
 * Returns:       1 if we modified the info 0 if we failed
 */
int
modify_dir_info(string region, string dir)
{
    if (!pointerp(Info[region]))
    {
	write("Region "+region+" does not exist.\n");
	return 0;
    }
    if (member_array(dir, Info[region][REGION_PATHS]) == -1)
    {
	write("Adding the directory "+dir+" to "+region+".\n");
	Info[region][REGION_PATHS] += ({dir});
    }
    else
    {
	write("Removing the directory "+dir+" from "+region+".\n");
	Info[region][REGION_PATHS] -= ({dir});
	if (!sizeof(Info[region][REGION_PATHS]))
	{
	    Info = m_delete(Info, region);
	    write("Region "+region+" was removed.\n");
	}
    }
    setuid(); seteuid(getuid());
    save_object(Save_file);
    return 1;
}

/* Function name: modify_weather_info
 * Description:   Allows us to add or remove weather from a region
 * Arguments:     string region:  The region we are modifying
 *                int weather:    The weather we are adding or removing
 * Returns:       1 if we modified the info 0 if we failed.
 */
int
modify_weather_info(string region, int weather)
{
    if (!pointerp(Info[region]))
    {
	write("Region "+region+" does not exist.\n");
	return 0;
    }
    if (member_array(weather, Info[region][POSSIBLE_WEATHER]) == -1)
    {
	write("Adding weather...\n");
	Info[region][POSSIBLE_WEATHER] += ({weather});
    }
    else
    {
	write("Removing weather....\n");
	Info[region][POSSIBLE_WEATHER] -= ({weather});
	if (!sizeof(Info[region][POSSIBLE_WEATHER]))
	{
	    Info = m_delete(Info, region);
	    write("Region "+region+" was removed.\n");
	}
    }
    setuid(); seteuid(getuid());
    save_object(Save_file);
    return 1;
}
/* Function name: modify_banned_weather_info
 * Description:   Allows us to add or remove banned weather from a region
 * Arguments:     string region:  The region we are modifying
 *                int weather:    The weather we are adding or removing
 * Returns:       1 if we modified the info 0 if we failed.
 */
int
modify_banned_weather_info(string region, int weather)
{
    if (!pointerp(Info[region]))
    {
	write("Region "+region+" does not exist.\n");
	return 0;
    }
    if (member_array(weather, Info[region][BANNED_WEATHER]) == -1)
    {
	write("Adding banned weather...\n");
	Info[region][BANNED_WEATHER] += ({weather});
    }
    else
    {
	write("Removing banned weather....\n");
	Info[region][BANNED_WEATHER] -= ({weather});
	if (!sizeof(Info[region][POSSIBLE_WEATHER]))
	{
	    Info = m_delete(Info, region);
	    write("Region "+region+" was removed.\n");
	}
    }
    setuid(); seteuid(getuid());
    save_object(Save_file);
    return 1;
}

