#include "/d/Shire/bits.h"
#ifndef SINDAR_DEFINITIONS
#define SINDAR_DEFINITIONS

#ifndef SINDAR_RACE_DIR
#define SINDAR_RACE_DIR "/d/Shire/guild/sindar_racial/"
#endif

#define SINDAR_EMOTES_DIR         (SINDAR_RACE_DIR + "emotes/")
#define SINDAR_RACE_HELP               (SINDAR_RACE_DIR + "help/")
#define SINDAR_RACE_NEWS               (SINDAR_RACE_HELP + "news")
#define SINDAR_RACE_GUILD_TRAINER (SINDAR_RACE_DIR + "train")
#define SINDAR_RACE_GUILD_SHADOW  (SINDAR_RACE_DIR + "sindar_racial_shadow")
#define SINDAR_RACE_GUILD_SOUL    (SINDAR_RACE_DIR + "sindar_racial_soul")
#define SINDAR_RACE_GUILD_GLOW    (SINDAR_RACE_DIR + "obj/glow")
#define SINDAR_RACE_GUILD_OBJ (SINDAR_RACE_DIR + "obj/guild_obj")
#define SINDAR_RACE_GUILD_LOG     "/d/Shire/log/sindar_race_guild"
#define SINDAR_RACE_GUILD_SAVE    (SINDAR_RACE_DIR + "sindar_race_save")
#define SINDAR_RACE_GUILD_TAX     3
#define SINDAR_RACE_GUILD_NAME    "Sindar of Mithlond"
#define SINDAR_RACE_GUILD_STYLE   "race"
#define SINDAR_RACE_GUILD_TYPE    "race"
#define SINDAR_RACE_GUILD_ALIGN    99
#define SINDAR_RACE_GUILD_MASTER  ({"palmer"})
#define IS_MEMBER(p) ((p)->query_guild_name_race() == SINDAR_RACE_GUILD_NAME)
#define BUILDING_BASE (SINDAR_RACE_DIR + "base_guild_house.c")
#define COMMON_INFO   (SINDAR_RACE_DIR + "common.c")
#define LOG_SIZE       25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define GUILD_OBJ_ID   "_sindar_race_guild_obj_"
#define START          (SINDAR_RACE_DIR + "start_rm")
#define EMOTE_DIR      (SINDAR_RACE_DIR + "emotes/")
#define ATTACKS_ELFS   "/d/Shire/greyhavens/save_info.o"

/* No definitions below this line */
#endif SINDAR_DEFINITIONS