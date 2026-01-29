/*
 * Defs file for Thornhold
 * Created by Gnim, June 2016
 */
 
// Root directory
#define ZONE_DIR            "/d/Faerun/thornhold/" 

// Directories
#define ARM_DIR             (ZONE_DIR + "arm/")
#define WEP_DIR             (ZONE_DIR + "wep/")
#define OBJ_DIR             (ZONE_DIR + "obj/")
#define NPC_DIR             (ZONE_DIR + "npcs/")
#define STD_DIR             (ZONE_DIR + "std/")
#define ROOM_DIR            (ZONE_DIR + "rooms/")
#define FOOD_DIR            (ZONE_DIR + "food/")
#define DATA_DIR            (ZONE_DIR + "data/")
#define FRUIT_DIR           "/d/Faerun/fruit/"

// Base files
#define BASE_ROAD           (STD_DIR + "base_road.c")
#define BASE_KEEP           (STD_DIR + "base_keep.c")

// Misc defines
#define ROOM_TELL_TIME      120

// Quest object for the zone
#define  QUEST_MASTER    (STD_DIR+"/thornhold_return_quest")

// Send all zone debugs to this dude
#define DEBUGGING
#ifdef DEBUGGING
#define DEBUGGER "tomas"
#define DEBUG(s) find_player(DEBUGGER)->catch_msg("Quest Helper: "+s+"\n")
#else
#define DEBUG(s)
#endif

#include "/d/Faerun/sys/basic.h"