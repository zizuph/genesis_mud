/* 
 * /d/Emerald/std/region.c
 * by Shiva@Genesis with influence from code from Khail, Teth, and Igneous.
 *
 * This is the standard region object.  Inherit this and configure it to
 * set up a domain region.
 *
 *
 */
 
#pragma strict_types

#include "/d/Emerald/sys/region.h"

static private int *coordinates;
static private int elevation;
static private int terrain;
static private int temperature;
static private int precipitation_mod;
static private string region_name;

/*
 * Function name: set_coordinates
 * Description:   Indicate the northern, southern, eastern, and western
 *                boudaries of this region.  The coordinates are measured
 *                as if on a grid where Telberin is the center.  Thus, a
 *                region 2 Km by 3 Km starting 50 Km west and 2 Km north
 *                of Telberin would have coordinates of 5, 2, -52, -50.
 * Arguments:     int n - the northern boundary
 *                int s - the southern boundary
 *                int e - the eastern boundary
 *                int w - the western boundary
 */
void
set_coordinates(int n, int s, int e, int w)
{
    coordinates = ({ n, s, e, w });
}

/*
 * Function name: query_coordinates
 * Description:   Get the coordinates for this region
 * Returns:       a 4-element array of coordinates, ({ n, s, e, w })
 */
int *
query_coordinates()
{
    return coordinates + ({});
}

/*
 * Function name: set_elevation
 * Description:   Indicate the average elevation of the region (in meters)
 * Arguments:     int el - the elevation in meters
 */
void
set_elevation(int el)
{
    elevation = el;
}

/*
 * Function name: query_elevation
 * Description:   get the region's elevation
 */
int
query_elevation()
{
    return elevation;
}

/*
 * Function name: set_terrain
 * Description:   Designate a terrain type for the region
 * Arguments:     int ter - the terrain type
 */
void
set_terrain(int ter)
{
    terrain = ter;
}

/*
 * Function name: query_terrain
 * Description:   Get the region's terrain type
 */
int
query_terrain()
{
    return terrain;
}

/*
 * Function name: set_temperature
 * Description:   Indicate the region's average temperature (degrees C)
 * Arguments:     int temp - the temperature
 */
void
set_temperature(int temp)
{
    temperature = temp;
}

/*
 * Function name: query_temperature
 * Description:   Get the region's average temperature (degrees C)
 */
int
query_temperature()
{
    return temperature;
}

/*
 * Function name: query_current_temperature
 * Description:   Get the region's current temperature (degrees C)
 */
int
query_current_temperature()
{
   return query_temperature();
}

/*
 * Function name: set_precipitation_mod
 * Description:   Indicate how much precipitation the region receives.
 *                100% is average, 0% is none
 * Arguments:     int mod - the precipitation mod (as a percentage of average)
 */
void
set_precipitation_mod(int mod)
{
    precipitation_mod = mod;
}

/*
 * Function name: query_precipitation_mod
 * Description:   Get the region's precipitation modifier (as a percentage)
 */
int
query_precipitation_mod()
{
    return precipitation_mod;
}

/*
 * Function name: set_region_name
 * Description:   Designate a name for the region.  This should be unique
 *                to this region.
 * Arguments:     string name - the region's name.
 */
void
set_region_name(string name)
{
    region_name = name;
}

/*
 * Function name: query_region_name
 * Description:   Get the region's name
 */
string
query_region_name()
{
    return region_name;
}

void
create_region()
{
}

nomask void
create()
{
    set_precipitation_mod(100);
    set_temperature(25);
    create_region();
}
