/* 	this is an special object of the town Gelan 
 
    coder(s):	Merlin 
 
    history:     7. 1.93    included ground and snow        Merlin 
                 7. 1.93    corrected -x.-x problem         Merlin 
                 5. 1.93    room check in tell_gelan        Merlin 
                 4. 1.93    functions for cmdsoul           Merlin 
                 3. 1.93    debugging, testing              Merlin 
                 2. 1.93    testing of weather              Merlin 
                 1. 1.93    debugging                       Merlin 
                30.12.92    cont                            Merlin 
                28.12.92    created                         Merlin 
 
    purpose:	this is the weather object of Gelan 
 
    quests:     none 
    special:    none 
 
    to do:      special weather things like flashes, blizzards etc 
                routines to handle string stuff 
                break modify weather in several parts for diff values 
                include random for calculating 
                calculate diff values on different intervalls 
                height of sun 
                rising and setting of sun 
                control output 
    bug:        none known 
*/ 
 
#include "specials.h" 
#include "timer.h" 
#include <stdproperties.h> 
 
/* all values all counted in real time, so to use converse them in Calia time ! */ 
 
/* some constants */ 
#define NOON_HOUR     9                         /* hour of noon in a day */ 
#define MAX_HOURS    19                         /* maximal hours in a day */ 
#define LAST_MONTH   13                         /* last month of year */ 
#define SUN_PERIOD   10                         /* clouds % for sun period */ 
#define DELAY       150                         /* seconds between 2 caculations */ 
#define SAVE_DELAY 1800                         /* time between 2 saving of values */ 
#define DATA_DELAY  300                         /* time between 2 saving of all data */ 
#define WEATHER_FILE    TOWN_SPECIALS + "weather.dat" 
                                                /* file where to save the data */ 
#define WEATHER_SAVE    TOWN_SPECIALS + "weather.sav" 
                                                /* file where to store data for reboot */ 
#define WIND_WEIGHT  50                         /* weight of the wind */ 
#define WIND_CLOUDS 100                         /* wieght of the wind for clouds */ 
 
/* changing of groundstatus and snowheight */ 
#define SNOW_MELT              20 
#define SNOW_MELT_WATER       200 
#define SNOW_MELT_RAIN        100 
#define SNOW_MELT_WATER_RAIN   10 
#define GROUND_MELT             5 
#define SNOW_DROP               1 
#define GROUND_DROP             3 
 
#define SNOW_THERE         10 
#define WET_ICED            3 
#define DRY_TO_WET          3 
#define DRY_TO_ICY          5 
#define WET_TO_DRY         10 
#define WET_TO_WET          5 
#define WET_TO_ICY          2 
#define ICY_TO_DRY          8 
#define ICY_TO_ICY          5 
#define ICY_RAIN            8 
 
/* strings for output to players */ 
#define SNOW_TO_RAIN        "The snow changes into rain.\n" 
#define RAIN_TO_SNOW        "The rain changes into snow.\n" 
#define RAIN_ICY            "An icy rain starts, you'd better look for shelter.\n" 
#define RAIN_COLD           "Suddenly a cold rain starts falling on you.\n" 
#define RAIN_NORMAL         "It starts raining.\n" 
#define RAIN_WARM           "A warm summer rain starts.\n" 
#define RAIN_REFRESHING     "Ah, a refreshing rain starts.\n" 
#define SNOW_WET            "It starts snowing with small rainlike flakes.\n" 
#define SNOW_NORMAL         "Suddenly it starts snowing.\n" 
#define SNOW_DRY            "It starts snowing with big dry flakes.\n" 
#define SNOW_ICY            "Brrr, in this cold. It even starts snowing now.\n" 
#define GROUND_THAW         "The ground thaws.\n" 
#define GROUND_FREEZE       "The ground freezes, better watch your steps.\n" 
#define CLOUDS_LIGHT        "Light white clouds start to cover the sky.\n" 
#define CLOUDS_NORMAL       "Clouds cover the sky.\n" 
#define CLOUDS_DARK         "Dark and heavy clouds cover the sky, it smells like rain.\n" 
#define SUN_BREAK           "The sun breaks through the clouds.\n" 
#define STAR_BREAK          "Some starts break through the clouds.\n" 
#define RAIN_STOP           "It stops raining.\n" 
#define SNOW_STOP           "It stops snowing.\n" 
#define WIND_N_LIGHT        "The wind changes to a light wind from north" 
#define WIND_N_NORMAL       "The wind changes to north" 
#define WIND_N_HEAVY        "The wind changes to a cold strong wind from north" 
#define WIND_W_LIGHT        "The wind changes to a light wind from west" 
#define WIND_W_NORMAL       "The wind changes to west" 
#define WIND_W_HEAVY        "The wind changes to a strong wind from west" 
#define WIND_S_LIGHT        "The wind changes to a light wind from south" 
#define WIND_S_NORMAL       "The wind changes to south" 
#define WIND_S_HEAVY        "The wind changes to a warm str   0,   0 }), 
