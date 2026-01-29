/*
 * Local defines for Blue Mountains
 * Created by Finwe, July 2002
 *
 */
 
// Root directory
#define BLUE_DIR            "/d/Shire/blue/"

// Room directories     
#define ROAD_DIR            (BLUE_DIR + "road/")
#define GER_DIR             "/d/Shire/eastroad/western/"

// Base files
#define BASE_ROAD           (BLUE_DIR + "base_road.c")
 
#define ROOM_TELL_TIME      180
 
// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/