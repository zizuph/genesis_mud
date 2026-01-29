/*
* Local defines for Tevalen
* Created by Tijgen 07OCT01
*/
#define TOWN_NAME   "Tevalen"
// Root Directory
#define TV_DIR    "/d/Shire/cypress/tevalen/"

// Object directory
#define ARM_DIR            (TV_DIR + "arm/")
#define WEP_DIR            (TV_DIR + "wep/")
#define OBJ_DIR            (TV_DIR + "obj/")
#define NPC_DIR            (TV_DIR + "npcs/")
 
// Room Directorys
#define WST_DIR			   (TV_DIR + "rooms/wasteland/road/")

// Misc Objects

#define FOOD_DIR            (TV_DIR + "food/")
#define COURIER_DIR         (TV_DIR + "messengers/")


// Base Files
#define WROAD_BASE			(TV_DIR + "base_outside_road.c")
#define PROAD_BASE			(TV_DIR + "base_in_poor_road.c")

#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90

// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/