/*
 *  /d/Sparkle/area/wild/defs.h
 *
 *  These are definitions to be used in Sparkle wild.
 *
 *  Created April 26 2008, by Styles.
 *  Original defs.h file format by Cooper Sherry (Gorboth)
 *
 */

#define CITY_DIR            ("/d/Sparkle/area/city/")
#define WILD_DIR            ("/d/Sparkle/area/wild/")

#define ROOMS_DIR           (WILD_DIR + "rooms/")
#define DATA_DIR            (WILD_DIR + "data/")
#define OBJ_DIR             (WILD_DIR + "obj/")
#define LOG_DIR             (WILD_DIR + "log/")
#define TEXT_DIR            (WILD_DIR + "text/")
#define LIB_DIR             (WILD_DIR + "lib/")
#define NPC_DIR             (WILD_DIR + "npc/")


#define MAP_MODULE          (CITY_DIR + "lib/map_module")


#define WILD_NPC_DATA		(DATA_DIR + "master_time_data")
#define MASTER_TIME_ROOM    (CITY_DIR + "rooms/master_time_room")
#define PATHFIND_LIB        (CITY_DIR + "lib/pathfind")
#define WILD_NPC_BASE		(NPC_DIR + "wild_npc")
#define WILD_ROOM_BASE		(ROOMS_DIR + "wild_room_base")


#define QUEST_FILE(n)        (extract((n), 0, 0) + "/" + (n))
#define TELL_S(x)            find_living("styles")->catch_tell( \
                               "WILD DEBUG: " + x + "\n")



                              
