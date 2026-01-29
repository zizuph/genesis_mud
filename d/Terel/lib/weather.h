/*
 * Definitions for Terel's weather module.
 */

/* weather types */
#define NO_WEATHER "none"
#define SUN        "sun"
#define SNOW       "snow"
#define RAIN       "rain"

#define WEATHER_TYPES ({ NO_WEATHER, SUN, SNOW, RAIN })

/* relative strength */
#define LIGHT_WEATHER  "light"
#define MEDIUM_WEATHER "moderate"
#define HEAVY_WEATHER  "heavy"

/* weather regions */
#define NO_REGION        "None"

/*
#define CALATHIN         "Calathin"
#define DABAAY           "Dabaay"
#define ELDERWOOD        "Elderwood"
#define ENCHANTED_FOREST "Enchanted Forest"
#define LAST             "Last"
#define RIBOS            "Ribos"
#define SILVER_FOREST    "Silver Forest"
#define STONEHOLD        "Stonehold"
#define UTTERDARK        "Utterdark"
*/

#define WEATHER_MAP       "/d/Terel/lib/weather_map"
#define WEATHER_IN_REGION 0
#define ROOMS_IN_REGION   1

#define DEFAULT_WEATHER "none"
#define DEFAULT_ROOM    ({})

#define WEATHER_LOG    "/d/Terel/log/weather_log"
#define ROOM_ADDED      1
#define ROOM_REMOVED    2
#define REGION_ADDED    3
#define REGION_REMOVED  4
#define WEATHER_CHANGED 5


#define WEATHER_CHANGE_TIME_BASE   900.0
#define WEATHER_CHANGE_TIME_RANDOM 300

/* Prototypes */
public  int                 add_region(string s);
public  int                 add_room_to_region(object o, string r);
private static varargs void log_weather_action(int i, string r, string s, string t);
private static int          region_exists(string s);
private static string       region_of_room(string s);
public  int                 remove_room_from_region(object o, string r);
public  int                 remove_region(string s);
private static int          room_exists_in_any_region(object o);
private static int          room_exists_in_region(object o, string s);
private static varargs void save_weather_state(int i, string r, string s, string t);
private static int          security_check();
public  int                 set_weather_in_region(string s, string r);
private static void         update_indices();
private static void         weather_change_effect();
private static float        weather_change_time();
public  string              weather_of_region(string s);
public  string              weather_of_room(object o);
private int                 do_add_region(string s);
private int                 do_add_room(string s);
private int                 do_remove_region(string s);
private int                 do_remove_room(string s);
private int                 do_set_weather(string s);
