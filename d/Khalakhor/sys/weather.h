/*
 *    Khalakhor's Weather defines!
 *
 *    Useful with the weather system ;)
 */
#ifndef _KHALAKHOR_WEATHER_DEFS_
#define _KHALAKHOR_WEATHER_DEFS_

// A shortcut to the master object.
#define WEATHER_MASTER    "/d/Khalakhor/sys/global/weather_master"

// Some indices for the weather mappings
#define REGION_PATHS     0
#define POSSIBLE_WEATHER 1
#define BANNED_WEATHER   2
#define CURRENT_WEATHER  3

// Some bit wise weather defines so it can be
// Windy raining and cloudy at the same time ;)
#define SUN       1
#define CLOUD     2
#define WIND      4
#define PRECIP    8
#define EXTREMES  16
#define FREEZING  32

//  These are the actual types of weather.
//  They are bit encoded numbers created from 
//  the types listed above.

// Regular weather
#define SUNNY     1
#define CLOUDY    2
#define PTCLOUDY  3
#define SUN_WIND  5
#define CL_WIND   6
#define PTCL_WIND 7  

// Rain based weather
#define RAINBOW   11
#define MIST      10
#define FOG       10 
#define SUNSHOWER 15
#define SHOWERS   14   
#define TSTORM    30

// Freezing based weather
#define SNOW_CALM 34
#define SNOW_WIND 38
#define FLURRY    42
#define SNOWING   50 
#define BLIZZARD  58


#define NORMAL_WEATHER_SOUTH ({SUN, CLOUD, WIND, PRECIP, EXTREMES})
#define NORMAL_WEATHER_NORTH ({CLOUD, WIND, PRECIP, EXTREMES, FREEZING})
#define POSSIBLE_ELEMENTS ({SUN, CLOUD, WIND. PRECIP, EXTREMES, FREEZING})

// macros for rooms
#define QUERY_WEATHER    WEATHER_MASTER->query_weather(query_weather_region())

// No more defines after this line
#endif
