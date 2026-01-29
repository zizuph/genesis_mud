/*
 * Local defines for Thalandrone
 * Created by Finwe, July 2001
 *
 */
 
// Root directory
 
// Object directories
#define ARM_DIR             (THAL_DIR + "armours/")
#define WEP_DIR             (THAL_DIR + "weapons/")
#define OBJ_DIR             (THAL_DIR + "objects/")
#define NPC_DIR             (THAL_DIR + "npcs/")
 
// Room directories
#define ROAD_DIR            (THAL_DIR + "rooms/roads/")
#define TOWN_DIR            (THAL_DIR + "rooms/town/")
#define RD1_DIR             (ROAD_DIR + "ring1/")
#define RD2_DIR             (ROAD_DIR + "ring2/")
#define RD3_DIR             (ROAD_DIR + "ring3/")
#define GLEN_DIR            (THAL_DIR + "rooms/glen/")
#define OTHERS_DIR          (ROAD_DIR + "others/")

// Base files
#define ROAD_BASE           (THAL_DIR + "base_road.c")
#define HOUSE_BASE          (THAL_DIR + "base_house.c")
#define INSIDE_BASE         (THAL_DIR + "base_inside.c")
#define FOREST_BASE         (THAL_DIR + "base_forest.c")
 
#define NPC_TELL_TIME       random(90)+15
 
// Sets up time defs for area.
#define LATE_NIGHT		0..3	/*12am-3am*/
#define EARLY_MORNING	4..7	/*4am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/
