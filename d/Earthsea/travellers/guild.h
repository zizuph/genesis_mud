#ifndef TRAV_DEFS
#define TRAV_DEFS

#define GUILD_NAME  "Traveller guild"
#define GUILD_STYLE "race"
#define GUILD_TAX   1

#define TRAVELLERS_DIR ("/d/Earthsea/travellers/")

#define TRAVELLERS_ROOM_DIR     (TRAVELLERS_DIR + "room/")
#define TRAVELLERS_OBJ_DIR      (TRAVELLERS_DIR + "obj/")
#define TRAVELLERS_LOG_DIR      (TRAVELLERS_DIR + "log/")
#define TRAVELLERS_NPC_DIR      (TRAVELLERS_DIR + "npc/")
#define TRAVELLERS_HELP_DIR     (TRAVELLERS_DIR + "help/")
#define TRAVELLERS_STD_DIR      (TRAVELLERS_DIR + "std/")
#define TRAVELLERS_LIB_DIR      (TRAVELLERS_DIR + "lib/")
#define TRAVELLERS_CARVINGS_DIR (TRAVELLERS_OBJ_DIR + "carvings/")
#define TRAVELLERS_BOOK_DIR     (TRAVELLERS_LOG_DIR + "books/")

#define TRAVELLERS_MANAGER         (TRAVELLERS_LOG_DIR + "manager")
#define TRAVELLERS_SHADOW          (TRAVELLERS_DIR + "trav_shadow")
#define TRAVELLERS_SOUL            (TRAVELLERS_DIR + "trav_soul")
#define TRAVELLERS_BADGE           (TRAVELLERS_OBJ_DIR + "badge")
#define TRAVELLERS_GUILD_EMBLEM    (TRAVELLERS_OBJ_DIR + "walking_stick")
#define TRAVELLERS_GUILD_EMBLEM_ID "_travellers_guild_emblem"
#define TRAVELLERS_STARTLOC        (TRAVELLERS_ROOM_DIR + "start")

#define TRAVELLERS_CARVING_STD (TRAVELLERS_STD_DIR + "carving")

#define CARVE_OBJECT_ID "_travellers_carving_object"

#define COUNCIL_MEMBER(x) (TRAVELLERS_MANAGER->query_council_member(x))
#define IS_MEMBER(x) (x->query_guild_member(GUILD_NAME))

#endif
