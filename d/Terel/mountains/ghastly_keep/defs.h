#include "/d/Terel/include/Terel.h"

// Define shortcuts.
#define GKEEP_DIR          DOMAIN_DIR + "mountains/ghastly_keep/"
#define GKEEP_STD_ROOM     GKEEP_DIR + "std/gkeep_std_room.c"
#define GKEEP_NPC_DEFS	   GKEEP_DIR + "npc_stats.h"
#define GKEEP              GKEEP_DIR + "rooms/"
#define GKEEP_NPC          GKEEP_DIR + "npc/"
#define GKEEP_OBJ          GKEEP_DIR + "obj/"
#define GKEEP_ARM          GKEEP_DIR + "arm/"
#define VERATH_KILLED      GKEEP_DIR + "log/verath_killed"
#define SABINE_KILLED      GKEEP_DIR + "log/sabine_killed"
#define VAMP_KILLED        GKEEP_DIR + "log/vampire_killed"
#define BREW_THROW         GKEEP_DIR + "log/brew_throw"
#define BREW_THROW2        GKEEP_DIR + "log/brew_throw2"
#define GPOTION_CDWN       GKEEP_DIR + "obj/g_potion_cooldown"
#define GTHROW_CDWN        GKEEP_DIR + "obj/g_throw_cooldown"
#define GTHROW_CDWN2       GKEEP_DIR + "obj/g_throw_cooldown2"
#define GTHROW_STUN        GKEEP_DIR + "obj/g_keep_stun"
#define STEEL_QUEST_LOG    GKEEP_DIR + "log/steel_quest_log"
#define FOCUSED_SPYGLASS   GKEEP_DIR + "log/focused_room_log"
#define STONE_LOG          GKEEP_DIR + "log/stone_log"
#define P_KILL_IN_GKEEP    GKEEP_DIR + "log/players_killed_in_keep"

// Kill Tracking
#define GKEEP_KILL_TRACKER      "_gkeep_kill_tracker"
#define GKEEP_KILLS_LEVEL2      (20)

// Define cooldowns.
#define GPOTION               60
#define GBREW				  60
#define G_SUMMON			   9

// Define locations          
#define GKEEP_LVL1             1
#define GKEEP_LVL2             2
#define GKEEP_OUTDOOR          3 
#define GKEEP_INTREE           4 

// Door props
#define GKEEP_DOOR   "_gkeep_finds_door"
#define GKEEP_DOOR2  "_gkeep_finds_door2"

// Quest props
#define GKEEP_STONE_DELIVERY "_gkeep_stone_delivery"

// Special defines
#define ONE_OF_LIST(array) ((array)[random(sizeof(array))])
