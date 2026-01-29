/* Modified from the /d/Sparkle/area/sea/defs.h
 *              and  /d/Khalakhor/ocean/defs.h 
 *   by Lilith Feb 2022
 * 
 * defs.h - For the sailing rooms that link to the Sparkle sailing rooms.
 * 
 */

#include "/d/Krynn/std/boats/std_boat_defs.h"

#define MAP_HANDLER      "/d/Ansalon/std/map_map"

#define SPARKLE_SEA      "/d/Sparkle/area/sea/"
#define AVENIR_SEA       "/d/Avenir/common/sea/"
#define SEA_ROOM         AVENIR_SEA + "room/"
#define SEA_MON          AVENIR_SEA + "mon/"
#define ROOM_BASE        AVENIR_SEA + "avenir_sea_base"
#define SAILING_BASE     AVENIR_SEA + "sailing"
#define SAILING_LIB      AVENIR_SEA + "lib"
#define SEA_SECTOR       AVENIR_SEA + "avenir_sea_sector"
#define MAP_DATA_FILE    AVENIR_SEA + "avenir_sea_map.txt"
#define SINK_ROOM        SEA_ROOM + "sink_room"

#define AVENIR_BERTH     "/d/Avenir/common/port/port12" 
#define AVENIR_PORT      SEA_ROOM + "sea-12-2-d"
#define SPARKLE_LINK     SPARKLE_SEA + "room/sparkle_sea-16-3-e"

#define MAP_SIZE_X 15
#define MAP_SIZE_Y 15
#define NEIGHBOURS (["west": "Khalakhor", "north": "icesheet", \
                     "east": "Sybarus",   "south": "Terel" ])
					 
#define SAILING_OPEN 1
					
//                    /d/Krynn/std/boats/
// set the same as CONDITIONS_NORMAL in std_boat_defs.h
#define NORMAL_DIFFICULTY          0
// set the same as CONDITIONS_TRICKY in std_boat_defs.h
#define TRICKY_DIFFICULTY          30
// set the same as CONDITIONS_CHALLENGING in std_boat_defs.h
#define ROUGH_SEAS_DIFFICULTY      51
// set the same as CONDITIONS_EXT_CHALLENGING in std_boat_defs.h
#define HIGH_SEAS_DIFFICULTY       76
// set the same as CONDITIONS_NEAR_IMPOSSIBLE in std_boat_defs.h
#define IMPOSSIBLE_SEAS_DIFFICULTY 91

#define MAX_BOATS                  20
#define DEFAULT_BLOCK_MSG          "You feel lost...\n"

#ifndef TP
#define TP this_player()
#define TO this_object()
#define NF0(x) { notify_fail(x); return 0; }
#endif

