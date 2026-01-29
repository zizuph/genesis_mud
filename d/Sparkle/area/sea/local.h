/*
 * local.h - For the Sparkle Sea sailing rooms between
 *           that links to the Krynn sailing rooms.
 * 
 * Arman - April 2021
 */

#include "/d/Sparkle/sys/defs.h"

#define MAP_HANDLER                "/d/Ansalon/std/map_map"

#define SPARKLE_SEA                "/d/Sparkle/area/sea/"
#define ROOM                       (SPARKLE_SEA + "room/")

#define SOBJ                       (SPARKLE_SEA + "obj/")
#define LIVING                     (SPARKLE_SEA + "living/")

#define SAIL_ROOM_BASE             (SPARKLE_SEA + "std_sailing_room")
#define ROOM_BASE	           SPARKLE_SEA + "sparkle_sea_base"

#define HIGH_SEA_LINK              "/d/Krynn/turbidus_ocean/room/high_sea_transit"
#define KRYNN_LINK              "/d/Krynn/turbidus_ocean/room/13s"


// set the same as CONDITIONS_NORMAL in std_boat_defs.h
#define NORMAL_DIFFICULTY          0

// set the same as CONDITIONS_TRICKY in std_boat_defs.h
#define TRICKY_DIFFICULTY          30

// set the same as CONDITIONS_CHALLENGING in std_boat_defs.h
#define ROUGH_SEAS_DIFFICULTY      51

// set the same as CONDITIONS_EXT_CHALLENGING in std_boat_defs.h
#define HIGH_SEAS_DIFFICULTY       76


