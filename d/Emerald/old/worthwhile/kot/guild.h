#ifndef KOT_DEFS
#define KOT_DEFS

#undef  KOT_DIR
#define KOT_DIR "/d/Emerald/guild/kot/"

#define KOT_LOG_DIR    (KOT_DIR + "log/")
#define KOT_OBJ_DIR    (KOT_DIR + "obj/")
#define KOT_SOUL_DIR   (KOT_DIR + "soul/")
#define KOT_SHADOW_DIR (KOT_DIR + "shadow/")
#define KOT_ROOM_DIR   (KOT_DIR + "room/")
#define KOT_HELP_DIR   (KOT_DIR + "help/")
#define KOT_BOOK_DIR   (KOT_LOG_DIR + "books/")
#define KOT_EAGLE_DIR  (KOT_DIR + "eagles/")

#define MANAGER            (KOT_LOG_DIR + "manager")
#define EAGLE_MANAGER      (KOT_EAGLE_DIR + "eagle_manager")
#define TEMP_EAGLE_ROOM    (KOT_EAGLE_DIR + "tmp")

#define CONVEY_COLORS ({"red","orange","yellow","green","blue",\
		        "violet","white","black","grey","gray"})

#define PROT_GUILD_NAME  "Protectorate of the Keepers of Telberin"
#define ORDER_GUILD_NAME "Order of the Keepers of Telberin"

#define LAY_PROT_MEMBER(x)  (x->query_guild_name_lay() == PROT_GUILD_NAME)
#define LAY_ORDER_MEMBER(x) (x->query_guild_name_lay() == ORDER_GUILD_NAME)
#define OCC_PROT_MEMBER(x)  (x->query_guild_name_occ() == PROT_GUILD_NAME)
#define OCC_ORDER_MEMBER(x) (x->query_guild_name_occ() == ORDER_GUILD_NAME)
#define KOT_MEMBER(x)       (x->query_kot_member())

#endif
