/*
 * Local defines for Farmer Maggot's farm and area
 * Created by Finwe, March 2005
 *
 */
 
// Root directory
#define MAGGOT_DIR          "/d/Shire/maggot/"
 
// Directories
#define ARM_DIR             (MAGGOT_DIR + "arm/")
#define WEP_DIR             (MAGGOT_DIR + "wep/")
#define OBJ_DIR             (MAGGOT_DIR + "obj/")
#define NPC_DIR             (MAGGOT_DIR + "npcs/")
#define ROOM_DIR            (MAGGOT_DIR + "rooms/")

// Base files
#define ROAD_BASE           (MAGGOT_DIR + "base_road.c")
#define HOUSE_BASE          (MAGGOT_DIR + "base_house.c")
#define INSIDE_BASE         (MAGGOT_DIR + "base_inside.c")

#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90
 
// Sets up time defs for area.
#define LATE_NIGHT              0..3    /*12am-3am*/
#define EARLY_MORNING   4..7    /*4am-7am*/
#define MORNING                 8..10   /*8am-10am*/
#define NOON                    11..13  /*11am-1pm*/
#define AFTERNOON               14..17  /*2pm-5pm*/
#define EVENING                 18..21  /*6pm-9pm*/
#define EARLY_NIGHT             22..24  /*10pm-12am*/

//Added base room for fields. Altrus, March 2005
#define BASE_COMMON 	("/d/Shire/maggot/rooms/base_common.c")