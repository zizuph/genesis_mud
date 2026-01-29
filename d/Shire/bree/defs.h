/*
 * Local defines for Bree
 * Created by Finwe, April 2002
 *
 */
 
// Root directory
#define NEW_BREE_DIR        "/d/Shire/bree/"
#define OLD_BREE_DIR        "/d/Shire/common/bree/"
 
// Directories
#define ARM_DIR             (NEW_BREE_DIR + "arm/")
#define WEP_DIR             (NEW_BREE_DIR + "wep/")
#define OBJ_DIR             (NEW_BREE_DIR + "obj/")
#define NPC_DIR             (NEW_BREE_DIR + "npcs/")
#define FOOD_DIR            (NEW_BREE_DIR + "food/")
#define BREE_LOG_DIR        (NEW_BREE_DIR + "log/")
#define ROAD_DIR            (NEW_BREE_DIR + "rooms/road/")
#define TOWN_DIR            (NEW_BREE_DIR + "rooms/town/") 
#define HOUSES_DIR          (NEW_BREE_DIR + "rooms/houses/")
#define FOOD_DIR            (NEW_BREE_DIR + "food/")

#define CAMP_DIR            ("/d/Shire/bree_camp/")
#define TRICK_DIR           ("/d/Shire/tricksters/")
#define ER_DIR              ("/d/Shire/eastroad/western/")
#define GWAY_DIR            ("/d/Shire/common/greenway/")
#define STAND_OBJ           ("/d/Shire/common/obj/")
#define STAND_WEAPON        ("/d/Shire/common/weapon/")
#define ARNOR_DIR           ("/d/Gondor/arnor/greenway/")
#define CALATHIN_DIR        ("/d/Terel/calathin/");

// Base files
#define ROAD_BASE           (NEW_BREE_DIR + "base_road.c")
#define HOUSE_BASE          (NEW_BREE_DIR + "base_house.c")
#define INSIDE_BASE         (NEW_BREE_DIR + "base_inside.c")
#define PATH_BASE			(NEW_BREE_DIR + "base_path.c")
 
#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
 
// Sets up time defs for area.
#define LATE_NIGHT		    0..3	/*12am-3am*/
#define EARLY_MORNING	    4..7	/*4am-7am*/
#define MORNING			    8..10	/*8am-10am*/
#define NOON			    11..13	/*11am-1pm*/
#define AFTERNOON		    14..17	/*2pm-5pm*/
#define EVENING			    18..21	/*6pm-9pm*/
#define EARLY_NIGHT		    22..24	/*10pm-12am*/

