/*
 * Defines for Barrow Downs
 * -- Finwe, December 2001
 */

#define DOWNS_DIR       "/d/Shire/downs/"
#define DOWNS_NPC       (DOWNS_DIR + "npc/")
#define DOWNS_WEP       (DOWNS_DIR + "wep/")
#define DOWNS_ARM       (DOWNS_DIR + "arm/")
#define DOWNS_OBJ       (DOWNS_DIR + "obj/")
#define BAR_DIR         (DOWNS_DIR + "barrows/")
#define VAL_DIR         (DOWNS_DIR + "valley/")
#define ROAD_DIR        (DOWNS_DIR + "road/")

/* base files */
#define BAR_BASE        (DOWNS_DIR + "base_barrow.c")
#define STONE_BASE      (DOWNS_DIR + "base_stone.c")        
#define ROAD_BASE       (DOWNS_DIR + "base_road.c")
#define WITHY_BASE      (DOWNS_DIR + "base_withy.c")

/* miscellaneous defines */
#define ROOM_TELL_TIME  60+random(120)
#define NPC_TELL_TIME   90
/* entered valley by going into barrows. full access to the back 
 * doors of some barrows given only to players who come thru the 
 * barrows. Others may enter the valley either via the
 * old forest or climbed down around a barrow. These times no 
 * props are set. The prop is removed automatically when player 
 * leaves the valley.
 */
#define BAR_SHAFT_EXIT  "_shire_exit_from_shaft_"


// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/