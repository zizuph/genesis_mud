/* Traveller definitions - Dec 12, 2000 by Shadowlynx */
#ifndef TRAV_DEFS
#define TRAV_DEFS

/* Defining the guild */
#define GUILD_NAME  "Traveller guild"
#define GUILD_STYLE "Race"
#define GUILD_TAX   1

/* Main directories */
#define TRAV_DIR "/d/Genesis/guilds/travellers/"

#define TRAV_ROOM_DIR         (TRAV_DIR + "room/")

#define TRAV_OBJ_DIR          (TRAV_DIR + "obj/")
#define TRAV_NPC_DIR          (TRAV_DIR + "npc/")
#define TRAV_LOG_DIR          (TRAV_DIR + "log/")
#define TRAV_HELP_DIR         (TRAV_DIR + "help/")
#define TRAV_FOREST_DIR       (TRAV_DIR + "forest/")
#define TRAV_GARDEN_DIR       (TRAV_DIR + "garden/")

#define TRAV_LODGE_DIR        (TRAV_DIR + "lodges/")
#define TRAV_MAIN_DIR         (TRAV_LODGE_DIR + "main/")
#define TRAV_TRADE_DIR        (TRAV_LODGE_DIR + "trade/")
#define TRAV_STABLE_DIR       (TRAV_LODGE_DIR + "stable/")
#define TRAV_KENNEL_DIR       (TRAV_LODGE_DIR + "kennel/")
#define TRAV_COMFORT_DIR      (TRAV_LODGE_DIR + "comfort/")
#define TRAV_HARDWARE_DIR     (TRAV_LODGE_DIR + "hardware/")
#define TRAV_BUSINESS_DIR     (TRAV_LODGE_DIR + "business/")

#define TRAV_STD_DIR          (TRAV_DIR + "std/")
#define TRAV_LIB_DIR          (TRAV_DIR + "lib/")
#define TRAV_BOOK_DIR         (TRAV_LOG_DIR + "books/")
#define TRAV_CARVINGS_DIR     (TRAV_OBJ_DIR + "carvings/")

#define TRAV_SOUL_DIR         (TRAV_DIR + "soul")
#define TRAV_SHADOW_DIR       (TRAV_DIR + "shadow")
#define TRAV_SOUL             (TRAV_SOUL_DIR + "trav_soul")
#define TRAV_SHADOW           (TRAV_SHADOW_DIR + "trav_shadow")
#define TRAV_MANAGER          (TRAV_LOG_DIR + "manager")
#define TRAV_BADGE            (TRAV_OBJ_DIR + "badge")
#define TRAV_GUILD_EMBLEM     (TRAV_OBJ_DIR + "walking_stick")
#define TRAV_GUILD_EMBLEM_ID  "_travellers_guild_emblem"
#define TRAV_STARTLOC         (TRAV_MAIN_DIR + "start")

#define TRAV_CARVING_STD      (TRAV_STD_DIR + "carving")

#define CARVE_OBJECT_ID       "_travellers_carving_object"

/* Guild and Council members */
#define COUNCIL_MEMBER(x)     (TRAV_MANAGER->query_council_member(x))
#define IS_MEMBER(x)          (x->query_guild_member(GUILD_NAME))

#endif

