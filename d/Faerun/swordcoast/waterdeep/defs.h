/*
 * /d/Faerun/waterdeep/defs.h
 * This file contains the definitions for the City of Waterdeep area
 *
 * Created by Brine, January 2021
 */

#ifndef WATERDEEP_DEFS
#define WATERDEEP_DEFS

#include "../defs.h"

// Link rooms
#define SHR_LINK            (SOUTH_HIGHROAD_DIR + "rooms/s_hroad15")

// Common directories
#define WD_ARM_DIR          (WATERDEEP_DIR + "armours/")
#define WD_WEP_DIR          (WATERDEEP_DIR + "weapons/")
#define WD_OBJ_DIR          (WATERDEEP_DIR + "objects/")
#define WD_NPC_DIR          (WATERDEEP_DIR + "mobiles/")
#define WD_STD_DIR          (WATERDEEP_DIR + "std/")
#define WD_AREAS_DIR        (WATERDEEP_DIR + "areas/")
#define WD_CONTROL_DIR      (WATERDEEP_DIR + "control")

// Wards' directories
#define FIELD_WARD_DIR      (WD_AREAS_DIR + "fieldward/")

// Waterdeep specific properties
#define IS_WATERDEEP_NPC    "_npc_i_is_waterdavian"
#define IS_WATERDEEP_ROOM   "_room_i_in_waterdeep"
#define IS_WATERDEEP_ITEM   "_obj_i_is_waterdavian"
#define WATERDEEP_AREA      "_room_s_waterdeep_area"
#define ENEMY_OF_WATERDEEP  "_live_i_waterdeep_enemy"

// Area constants
#define CASTLE_WARD         "Castle Ward"
#define DEAD_WARD           "City of the Dead"
#define DOCK_WARD           "Dock Ward"
#define FIELD_WARD          "Field Ward"
#define MNT_WATERDEEP       "Mount Waterdeep"
#define MOUNTAINSIDE        "Mountainside"
#define NORTH_WARD          "North Ward"
#define SEA_WARD            "Sea Ward"
#define SOUTHERN_WARD       "Southern Ward"
#define TRADES_WARD         "Trades Ward"
#define UNDERCLIFF          "Undercliff"
#define OUTSKIRTS           "Outskirts"
#define TROLLWALL           "Troll Wall"

// Terrain constants
#define DIRT_ROAD           "Dirt road"
#define HIGH_ROAD           "High road"
#define BOARDWALK_STREET    "Boardwalk street"
#define COBBLED_STREET      "Cobbled street"
#define DIRT_STREET         "Dirt street"
#define FILTHY_STREET       "Filthy street"

// Standard objects
#define WATERDEEP_ROOM      (WD_STD_DIR + "waterdeep_room")
#define WATERDEEP_INDOOR    (WD_STD_DIR + "waterdeep_room_indoor")
#define WATERDEEP_NPC_BASE  (WD_STD_DIR + "waterdeep_npc")
#define WATERDEEP_GUARD     (WD_STD_DIR + "guard_base")
#define WATERDEEP_WEP       (WD_STD_DIR + "waterdeep_wep")
#define WATERDEEP_ARM       (WD_STD_DIR + "waterdeep_arm")
#define WATERDEEP_OBJ       (WD_STD_DIR + "waterdeep_obj")

// City Guard definitions
#define PRIVATE             0
#define ARMAR               1
#define CIVILAR             2
#define SENIOR_CIVILAR      3

#endif WATERDEEP_DEFS
