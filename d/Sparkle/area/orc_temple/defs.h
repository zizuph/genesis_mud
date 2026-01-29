/*
 *  /d/Sparkle/area/orc_temple/defs.h
 * 
 *  These are the definition files for the Dungeons beneath the orc temple
 *  in Sparkle.
 *
 *  Created June 2010, by Cooper Sherry (Gorboth)
 */

#define DUNGEON_DIR    "/d/Sparkle/area/orc_temple/"
#define WEP_DIR        DUNGEON_DIR + "wep/"
#define ARM_DIR        DUNGEON_DIR + "arm/"
#define LOG_DIR        DUNGEON_DIR + "log/"
#define NPC_DIR        DUNGEON_DIR + "npc/"
#define DOORS_DIR      DUNGEON_DIR + "doors/"
#define ROOMS_DIR      DUNGEON_DIR + "rooms/"
#define OBJ_DIR        DUNGEON_DIR + "obj/"
#define TEXT_DIR       DUNGEON_DIR + "text/"

#define QUEST_WEAPON  "_imbuement_quest_dagger"
#define QUEST_JOURNAL "_imbuement_quest_read_journal"
#define QUEST_FLUTE   "_imbuement_quest_bone_flute"
#define QUEST_DEMON   "_imbuement_quest_demon_object"
#define QUEST_TEAR    "_imbuement_quest_tear"
#define AMULET        "_imbuement_quest_amulet"

#define ORC_TEMPLE_QUEST_PROP  "_enchanter_orc_temple_instructions"
#define JOURNAL_REAGENT_PROP   "_kerchak_journal_reagent"
#define AMULET_TRIGGER_ACTIVE  "_imbue_amulet_trigger_active"

#define JAILERS_KEYS    "_sparkle_orc_temple_cell_keys"
#define ORC_TEMPLE_NPC  "_sparkle_orc_temple_npc"
#define DUNGEON_CELL    "_sparkle_orc_temple_cell"
#define DOOR_BLOCK_ROOM "_doors_should_block_here"
#define HIGH_PRIEST     "_orc_temple_high_priest"
#define DUNGEON_ROOM    "_orc_temple_dungeon_room"
#define DIARY_ID        "_orc_temple_enchanter_diary"

#define NPC_BASE_STAT       5
#define RUNT_BASE_STAT      (NPC_BASE_STAT + 1)
#define WARRIOR_BASE_STAT   (NPC_BASE_STAT + 5)
#define PRIEST_BASE_STAT    (NPC_BASE_STAT + 5)
#define RUNT_WEP_STAT       12
#define WARRIOR_WEP_STAT    15
#define THREAT_THRESHHOLD   42 /* beneath wanderer level */

#define NPC_RUNT_STR        (RUNT_BASE_STAT + 2)
#define NPC_RUNT_DEX        (RUNT_BASE_STAT + 3)
#define NPC_RUNT_CON        (RUNT_BASE_STAT + 3)
#define NPC_RUNT_INT        (RUNT_BASE_STAT + -1)
#define NPC_RUNT_WIS        (RUNT_BASE_STAT + -2)
#define NPC_RUNT_DIS        (RUNT_BASE_STAT + 0)

#define NPC_WARRIOR_STR     (WARRIOR_BASE_STAT + 2)
#define NPC_WARRIOR_DEX     (WARRIOR_BASE_STAT + 3)
#define NPC_WARRIOR_CON     (WARRIOR_BASE_STAT + 3)
#define NPC_WARRIOR_INT     (WARRIOR_BASE_STAT + 0)
#define NPC_WARRIOR_WIS     (WARRIOR_BASE_STAT + 0)
#define NPC_WARRIOR_DIS     (WARRIOR_BASE_STAT + 5)

#define NPC_PRIEST_STR      (PRIEST_BASE_STAT + 0)
#define NPC_PRIEST_DEX      (PRIEST_BASE_STAT + 2)
#define NPC_PRIEST_CON      (PRIEST_BASE_STAT + 0)
#define NPC_PRIEST_INT      (PRIEST_BASE_STAT + 20)
#define NPC_PRIEST_WIS      (PRIEST_BASE_STAT + 10)
#define NPC_PRIEST_DIS      (PRIEST_BASE_STAT + 30)

#include "/d/Genesis/imbuement/imbuement.h"

/* ifdef values */
#define    LOG_ACTIVITY 0
#define    LOG_MOVES    0
