/*
 * Def file for North South Road
 * Finwe, January 2020
 */
#include "/d/Shire/sys/defs.h";

#define NS_ARM_DIR  (NS_RD_DIR + "arm/")
#define NS_NPC_DIR  (NS_RD_DIR + "npcs/")
#define NS_OBJ_DIR  (NS_RD_DIR + "obj/")
#define NS_RM_DIR   (NS_RD_DIR + "rooms/")
#define NS_STD_DIR  (NS_RD_DIR + "std/")
#define NS_WEP_DIR  (NS_RD_DIR + "wep/")
#define FRUIT_DIR   (NS_RD_DIR + "food/")
#define FOOD_DIR    (NS_RD_DIR + "food/")
#define ORCHARD_DIR (NS_RD_DIR + "orchard/")

/*
 * Base files
 */
#define BASE_ROAD   (NS_STD_DIR + "base_road.c")
#define BASE_ORHARD (NS_STD_DIR + "base_orchard.c")

// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/

/* miscellaneous defines */
#define ROOM_TELL_TIME  60+random(120)
#define NPC_TELL_TIME   90
