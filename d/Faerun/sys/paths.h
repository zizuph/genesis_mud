/*
 *  faerun/definitions/paths.h
 *
 *  Contains all the global path definitions. Do not use hardcoded paths in
 *  any of the objects, always refer to a define.
 *
 *  Created by Wully, 12-2-2004
 */

#ifndef FAERUN_PATH_DEFINITIONS
#define FAERUN_PATH_DEFINITIONS


// Global domain paths
#define FAERUN_DIR              "/d/Faerun/"
#define FAERUN_LIB              (FAERUN_DIR + "lib/")
#define FAERUN_LOG              (FAERUN_DIR + "log/")
#define FAERUN_SYS              (FAERUN_DIR + "sys/")
#define FAERUN_STD              (FAERUN_DIR + "std/")
#define FAERUN_SPELLS           (FAERUN_DIR + "spells/")
#define FAERUN_HERBS            (FAERUN_DIR + "herbs/")
#define FAERUN_BOARDS           (FAERUN_DIR + "private/boards/")
#define FAERUN_AUTOTEAM         (FAERUN_STD + "team_code.c")

#define UNDERDARK_DIR           (FAERUN_DIR + "underdark/")
#define UPPERDARK_DIR           (UNDERDARK_DIR + "upper/")

// Herb Related files
#define HERB_SEARCH             (FAERUN_HERBS + "herbsearch")
// Domain herbal paths
#define AVENIR_HERB_DIR         "/d/Avenir/common/herbs/"
#define EARTHSEA_HERB_DIR       "/d/Earthsea/herbs/herb_files/"
#define FAERUN_HERB_DIR         "/d/Faerun/herbs/herb_files/"
#define GONDOR_HERBS            "/d/Gondor/common/herbs/"
#define GONDOR_HERB_DIR         "/d/Gondor/common/herbs/"
#define KALAD_HERB_DIR          "/d/Kalad/common/herbs/"
#define KHAL_HERB_DIR           "/d/Khalakhor/common/herbs/"
#define KRYNN_HERB_DIR          "/d/Krynn/common/herbs/"
#define SHIRE_HERB_DIR          "/d/Shire/common/herbs/"
#define TEREL_HERB_DIR          "/d/Terel/common/herbs/"

#define HERB_POISONS            (FAERUN_HERBS + "poisons/")
#define SCRATCH_POISON          (HERB_POISONS + "scratch.c")

// Base file defines
#define FAERUN_ARM_BASE         (FAERUN_STD + "faerun_armour")
#define FAERUN_WEP_BASE         (FAERUN_STD + "faerun_weapon")
#define FAERUN_ROOM_BASE        (FAERUN_STD + "faerun_room")
#define FAERUN_TEAM_BASE        (FAERUN_STD + "team_code")
#define FAERUN_NPC_BASE         (FAERUN_STD + "faerun_npc")
#define FAERUN_CREATURE         (FAERUN_STD + "faerun_creature")
#define FAERUN_WATER_BASE       (FAERUN_STD + "water_faerun")
#define FAERUN_ITEM_BASE        (FAERUN_LIB + "item_origin")
#define FAERUN_ROOM_TELL_BASE   (FAERUN_LIB + "room_tell")
#define FAERUN_OUTDOOR_BASE     (FAERUN_STD + "room")
#define FAERUN_INDOORS_BASE     (FAERUN_STD + "room_indoors")
#define FAERUN_DRAGON           (FAERUN_STD + "faerun_dragon")

// Temple directories
#define TEMPLE_DIR              (FAERUN_DIR + "temples/")

// Miscellaneous defines
#define KILL_LOGGER             (FAERUN_LIB + "kill_logger")

// *** DO NOT USE DEFINITIONS BELOW THIS LINE. THEY ARE OBSOLETE ***
#define P_UNDERDARK             (P_FAERUN + "underdark/")
#define P_UNDERDARK_STD         (P_UNDERDARK + "std/")
#define P_UPPERDARK             (P_UNDERDARK + "upper/")
#define P_MIDDLEDARK            (P_UNDERDARK + "middle/")
#define P_LOWERDARK             (P_UNDERDARK + "lower/")

#define P_FAERUN                "/d/Faerun/"
#define P_FAERUN_LIB            (P_FAERUN + "lib/")
#define P_FAERUN_LOG            (P_FAERUN + "log/")
#define P_FAERUN_SYS            (P_FAERUN + "sys/")
#define P_FAERUN_STD            (P_FAERUN + "std/")
#define P_FAERUN_SPELLS         (P_FAERUN + "spells/")
#define P_FAERUN_BOARDS         (P_FAERUN + "private/boards/")
#define P_FAERUN_AUTOTEAM       (P_FAERUN_STD + "team_code.c")

// Paths for the upperdark
#define P_UPPERDARK_STD	        (P_UPPERDARK + "std/")

// Paths to guilds
#define P_FAERUN_GUILDS         (P_FAERUN + "guilds/")
#define P_DROW_RACIAL           (P_FAERUN_GUILDS + "drow/race/")
#define P_DROW_LAYMAN           (P_FAERUN_GUILDS + "drow/lay/")

// Loot table paths for some Faerun monsters
#define P_LOOTTABLES            (P_FAERUN + "monsters/loot-tables/")

#endif FAERUN_PATH_DEFINITIONS
