/*
 * Mapserver area example created by Milan
 *
 * This file is to be inherited by all mapserver example rooms.
 */
#pragma save_binary
#pragma strict_types
inherit "/d/Ansalon/std/map_serv";
#include "local.h"

/* Function name: query_file_with_map
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return path to the file containing map
 */
public nomask string
query_file_with_map()
{
    return THIS_DIR + "ex_map";
}

/* Function name: query_base_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where base-files are located
 */
public string
query_base_dir()
{
    return THIS_DIR;
}

/* Function name: query_room_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where room-files are located
 */
public string
query_room_dir()
{
    return THIS_DIR + "rooms/";
}

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
public int
is_room(string arg)
{
    if ((arg == "x") || (arg == "p") || (arg == "f"))
	return 1;
    return 0;
}

/* Function name: exit_not_obvious
 * Description:	  Test if exit from one room to another should be not obvious
 * Argument:	  from - letter corresponding to from room
 *		  dest - letter corresponding to dest room
 * Returns:	  1 if not obvious    else 0 - exit will be obvious
 */
public int
exit_not_obvious(string from, string dest)
{
    if (from == "p" && dest == "p") // path is obvious
	return 0;
    return 1; // all other are not obvious
}
