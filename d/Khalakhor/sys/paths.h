/*
 * paths.h
 *
 * Header file containing some of the default dir paths
 * in the domain.
 * Removed the STDCAPTAIN definition as unused and clashing with
 * new ship system - Tapakah, 10/2008
 *
 * Some minor updates - Tapakah, 05/2021
 */
#ifndef DOMAIN_PATHS
#define DOMAIN_PATHS

#define BASE_PATH    "/d/Khalakhor/"
#define COMMON       (BASE_PATH + "common/")
#define GUILDS       (BASE_PATH + "guilds/")
#define INISI        (BASE_PATH + "inisi/")
#define LIB          (BASE_PATH + "lib/")
#define LOG          (BASE_PATH + "log/")
#define NORTH        (BASE_PATH + "n_speir/")
#define S_EAST       (BASE_PATH + "se_speir/")
#define S_WEST       (BASE_PATH + "sw_speir/")
#define SHIPS        (BASE_PATH + "ship/")
#define STD          (BASE_PATH + "std/")
#define SYS          (BASE_PATH + "sys/")

#define COM_ARM      (COMMON + "arm/")
#define COM_HERBS    (COMMON + "herbs/")
#define COM_KILTS    (COMMON + "kilts/")
#define COM_OBJ      (COMMON + "obj/")
#define COM_NPC      (COMMON + "npc/")
#define COM_POISONS  (COMMON + "poisons/")
#define COM_POTIONS  (COMMON + "potions/")
#define COM_ROOM     (COMMON + "room/")
#define COM_WEP      (COMMON + "wep/")
#define COM_WILDLIFE (COMMON + "wildlife/")

#define STDROOM      (STD + "stdroom")
#define ROOMTELL     (LIB + "room_tell")

// Defines for standard base monsters.
#define STDCREATURE  (STD + "creature")
#define STDMONSTER   (STD + "monster")

// Defines for paths to standard npcs
#define STDBIRD      (STD + "npc/bird")
// #define STDCAPTAIN   (STD + "npc/captain")
#define STDCUNDEAD   (STD + "npc/c_undead")
#define STDDWARF     (STD + "npc/dwarf")
#define STDELF       (STD + "npc/elf")
#define STDGOBLIN    (STD + "npc/goblin")
#define STDHUNDEAD   (STD + "npc/h_undead")
#define STDHUMAN     (STD + "npc/human")
#define STDTALAMH    (STD + "npc/talamhdubh")
#define STDWILDLIFE  (STD + "npc/wildlife")

// Defines for paths to standard non-npcs
#define KSTDARMOUR   (STD + "armour")
#define KSTDWEAPON   (STD + "weapon")

// Defines for paths to common npcs

#define COMDWARF     (COM_NPC + "dwarf")
#define COMELF       (COM_NPC + "elf")
#define COMGOBLIN    (COM_NPC + "goblin")
#define COMHUMAN     (COM_NPC + "human")
#define COMTALAMH    (COM_NPC + "talamhdubh")

// Paths for common npcs weapons and armours.

#define DWARM        (COM_ARM + "dwarf/")
#define DWWEP        (COM_WEP + "dwarf/")
#define ELARM        (COM_ARM + "elf/")
#define ELWEP        (COM_WEP + "elf/")
#define GOARM        (COM_ARM + "goblin/")
#define GOWEP        (COM_WEP + "goblin/")
#define HUARM        (COM_ARM + "human/")
#define HUWEP        (COM_WEP + "human/")
#define TAARM        (COM_ARM + "talamhdubh/")
#define TAWEP        (COM_WEP + "talamhdubh/")

#define LEFTOVER     (COM_OBJ + "leftover/")
#define FEATHER      (LEFTOVER + "feather")
#define HORN         (LEFTOVER + "horn")
#define SKIN         (LEFTOVER + "skin")
#define KHAL_DOOR    (STD + "door")

#define INFO_BASE    (BASE_PATH + "std/obj/information_base")
#define INFO_MASTER  (COM_OBJ + "information_master")

/* Herb definitions */
#define HERBSEARCH   (LIB + "herbsearch")
#define HERBMASTER   (COM_HERBS + "herb_master")

#define STDHERBSEARCH (LIB + "herb_search")
#define TERRAINSERVER (LIB + "terrain_server")

#define AVHERB   ("/d/Avenir/common/herbs/")
// GENHERB obsolete - do not use
#define GENHERB  ("/d/Genesis/herbs/")
#define GEHERB   ("/d/Genesis/herbs/")
#define GOHERB   ("/d/Gondor/common/herbs/")
#define KHHERB   (COM_HERBS)
#define KRHERB   ("/d/Krynn/common/herbs/")
#define SHHERB   ("/d/Shire/common/herbs/")
#define TEHERB   ("/d/Terel/common/herbs/")
// TER_HERB obsolete - do not use
#define TER_HERB ("/d/Terel/common/herbs/")

/* Herb definitions */
#define BAITSEARCH   (LIB + "bait-search")

#endif
