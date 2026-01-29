/*
 * This is a set of definitions for the Keepers of Telberin
 * Re-Done by Alaron March 5, 1997
 */

#ifndef KOT_DEFS
#define KOT_DEFS

#undef  KOT_DIR
#define KOT_DIR "/d/Emerald/common/guild/kot/"

#define KOT_LOG_DIR    (KOT_DIR + "log/")
#define KOT_OBJ_DIR    (KOT_DIR + "obj/")
#define KOT_SOUL_DIR   (KOT_DIR + "soul/")
#define KOT_SHADOW_DIR (KOT_DIR + "shadow/")
#define KOT_ROOM_DIR   (KOT_DIR + "room/")
#define KOT_HELP_DIR   (KOT_DIR + "help/")
#define KOT_BOOK_DIR   (KOT_LOG_DIR + "books/")
#define KOT_EAGLE_DIR  (KOT_DIR + "eagles/")

#define GUILD_SOUL_CLERIC  (KOT_SOUL_DIR + "cleric_soul")
#define GUILD_SOUL_WARRIOR (KOT_SOUL_DIR + "warrior_soul")
#define SPELL_OBJECT_CLERIC (KOT_OBJ_DIR + "spells")
#define MANAGER            (KOT_LOG_DIR + "manager")
#define EAGLE_MANAGER      (KOT_EAGLE_DIR + "eagle_manager")
#define TEMP_EAGLE_ROOM    (KOT_EAGLE_DIR + "tmp")

/* Define the general race guild characteristics */
#define GUILD_NAME           "Keepers of Telberin"
#define GUILD_TYPE           "race"
#define GUILD_SOUL_ID        "telberin_keepers"

#define GUILD_TAX            2

#define GUILD_EMBLEM_ID "kot_guild_emblem"

#define GUILD_OBJECT (KOT_OBJ_DIR + "sash")

#define GUILD_POST     (KOT_ROOM_DIR + "post")
#define GUILD_STARTLOC (KOT_ROOM_DIR + "kot_common")
#define GUILD_SHADOW   (KOT_SHADOW_DIR + "kot_shadow")

#define WARRIOR_CASTE   0
#define CLERIC_CASTE    1

#define CLERIC_GOD_NAME "Telan-Ri"
#define RI_OBJECT       "kot_ri_object"
#define CRYSTAL_OBJECT  "kot_ri_crystsal"

#define CONVEY_COLORS ({"red","orange","yellow","green","blue",\
		        "violet","white","black","grey","gray"})

#define MAX_GUILD_STAT 84

#define PROT_GUILD_NAME  "Protectorate of the Keepers of Telberin"
#define ORDER_GUILD_NAME "Order of the Keepers of Telberin"

#define IS_MEMBER(who) (who->query_kot_member())
#define LAY_PROT_MEMBER(x)  (x->query_guild_name_lay() == PROT_GUILD_NAME)
#define LAY_ORDER_MEMBER(x) (x->query_guild_name_lay() == ORDER_GUILD_NAME)
#define OCC_PROT_MEMBER(x)  (x->query_guild_name_occ() == PROT_GUILD_NAME)
#define OCC_ORDER_MEMBER(x) (x->query_guild_name_occ() == ORDER_GUILD_NAME)
#define KOT_MEMBER(x)       (x->query_kot_member())

#endif
