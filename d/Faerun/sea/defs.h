/*
 * Defs file for seas of Faerun
 * Created by Nerull, July 2020
 */
 
// Root directory
#define DEFAULT_DIR         "/d/Faerun/sea/"
 
// Directories
#define OBJ_DIR               (DEFAULT_DIR + "obj/")
#define NPC_DIR               (DEFAULT_DIR + "npcs/")
#define STD_DIR               (DEFAULT_DIR + "std/")
#define SEA_ROOM_DIR          (DEFAULT_DIR + "rooms/")

// Base files
#define STD_SEA_SURFACE       (STD_DIR + "std_sea_surface.c")
#define STD_SEA_UNDERWATER    (STD_DIR + "std_sea_underwater.c")
#define STD_SEA_WATER         (STD_DIR + "water.c")

// Some defines
#define FAERUN_UNDERWATER      "_faerun_underwater"
#define FAERUN_SHIP_CAN_SAIL   "_faerun_ship_can_sail"
#define OBJ_I_FLOAT            "_obj_i_float"
#define OBJ_I_FAERUN_SHIP      "_obj_i_faerun_ship"
