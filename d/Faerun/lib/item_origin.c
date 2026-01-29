/*
 *  faerun/lib/item_origin.c
 *
 *  This file can be included into objects to add functions to set and
 *  query the region, level, area and location this item originates from
 *
 *  Created by Wully, 12-2-2004
 */

#include "/d/Faerun/defs.h"

string	faerun_region;		// The global region this room is in
int		faerun_level;		// The land level you are on, 0 being surface,
							// anything negative is below the ground (-1 being
							// upper underdark), anything possitive is above
							// ground level
string  faerun_area;		// The name of the area you are in
string	faerun_location;	// Location within the specific area

/*
 * Function name: set_faerun_region
 * Description  : Set the global region of this room
 * Arguments	: region - the name of the region
 */
void set_faerun_region(string region)
{
	faerun_region = region;
}

/*
 * Function name: query_faerun_region
 * Description  : In which global region is this room
 * Returns		: a string
 */
string query_faerun_region()
{
	return faerun_region;
}

/*
 * Function name: set_faerun_level
 * Description  : Sets the land level of this room, 0 is surface, anything
 *				: positive above the surface, anything negative below
 * Argumens		: level - the land level
 */
void set_faerun_level(int level)
{
	faerun_level = level;
}

/*
 * Function name: query_faerun_level
 * Description  : Get the land level of this room
 * Returns		: an integer
 */
int query_faerun_level()
{
	return faerun_level;
}

/*
 * Function name: set_faerun_area
 * Description  : Set the area of this room
 * Arguments	: area - the name of the area
 */
void set_faerun_area(string area)
{
	faerun_area = area;
}

/*
 * Function name: query_faerun_area
 * Description  : In which area is this room
 * Returns		: a string
 */
string query_faerun_area()
{
	return faerun_area;
}

/*
 * Function name: set_faerun_location
 * Description  : Set the location within the area of this room
 * Arguments	: location - the name of the location
 */
void set_faerun_location(string location)
{
	faerun_location = location;
}

/*
 * Function name: query_faerun_location
 * Description  : In which location of the area is this room
 * Returns		: a string
 */
string query_faerun_location()
{
	return faerun_location;
}