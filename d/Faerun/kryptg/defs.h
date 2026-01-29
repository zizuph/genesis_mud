/*
 * Defs file
 */
 
// Root directory
#define DEFAULT_DIR         "/d/Faerun/kryptg/"
 
// Directories
#define ARM_DIR             (DEFAULT_DIR + "arm/")
#define WEP_DIR             (DEFAULT_DIR + "wep/")
#define OBJ_DIR             (DEFAULT_DIR + "obj/")
#define NPC_DIR             (DEFAULT_DIR + "npcs/")
#define STD_DIR             (DEFAULT_DIR + "std/")
#define ROOM_DIR            (DEFAULT_DIR + "rooms/")
#define CIT_DIR             (ROOM_DIR + "citadel/")
#define FOR_DIR             (ROOM_DIR + "forest/")
#define DRAGON_DIR          (ROOM_DIR + "dragons_lair/")

// Citadel Underground Levels
#define L1_DIR              (CIT_DIR + "lvl1/")

// Base files
#define BASE_FOREST         (STD_DIR + "base_forest.c")
#define BASE_CITADEL        (STD_DIR + "base_citadel.c")
#define BASE_DRAGONSLAIR    (STD_DIR + "base_dragonslair.c")
#define BASE_CAVE           (STD_DIR + "base_cave.c")

// Misc definitions
#define FOR_NAME            " Kryptgarden Forest"
#define FOR_NPC             "_kryptg_npc"

// Citadel settings
#define MIN_AWARENESS 30
#define BONES               ({"bone_head", "bone_larm", "bone_lleg", \
                              "bone_rarm", "bone_rleg", "bone_spine"})

// Bone defines
#define HEAD                "_faerun_bone_head"
#define SPINE               "_faerun_bone_spine"
#define LARM                "_faerun_bone_larm"
#define RARM                "_faerun_bone_rarm"
#define LLEG                "_faerun_bone_lleg"
#define RLEG                "_faerun_bone_rleg"

// Found bone items
#define FOUND_HEAD          "_found_bone_head"
#define FOUND_SPINE         "_found_bone_spine"
#define FOUND_LARM          "_found_bone_larm"
#define FOUND_RARM          "_found_bone_rarm"
#define FOUND_LLEG          "_found_bone_lleg"
#define FOUND_RLEG          "_found_bone_rleg"

// Accepted bone items by npc
#define OK_HEAD             "_ok_head"
#define OK_SPINE            "_ok_spine"
#define OK_LARM             "_ok_larm"
#define OK_RARM             "_ok_rarm"
#define OK_LLEG             "_ok_lleg"
#define OK_RLEG             "_ok_rleg"

// path for Highroad directory
#define HIGHRD_DIR          "/d/Faerun/highroad/rooms/"

