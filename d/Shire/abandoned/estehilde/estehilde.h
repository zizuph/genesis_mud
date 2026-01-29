/*
 *  /d/Shire/guild/estehilde/estehilde.h
 *  Definitions for the Estehilde guild
 *  from the Shire Domain of Genesis
 *  Jaypeg, June 1999
 */


#include "/d/Shire/bits.h"
#ifndef ESTE_DEFINITIONS
#define ESTE_DEFINITIONS

#ifndef ESTE_DIR
#define ESTE_DIR "/d/Shire/guild/estehilde/"
#endif

#define ESTE_GUILD_TRAINER    (ESTE_DIR + "train")
#define ESTE_GUILD_SHADOW     (ESTE_DIR + "este_shadow")
#define ESTE_GUILD_SOUL       (ESTE_DIR + "este_soul")
#define ESTE_GUILD_OBJ        (ESTE_DIR + "robe")
#define ESTE_GUILD_SPELLS     (ESTE_DIR + "prayerbook")
#define ESTE_GUILD_LOG        "/d/Shire/log/estehide"
#define ESTE_LOGS             ESTE_DIR + "log/"
#define ESTE_GUILD_TAX        11
#define ESTE_GUILD_NAME       "Estehilde"
#define ESTE_GUILD_STYLE      "cleric"
#define ESTE_GUILD_TYPE       "occupational"
#define ESTE_GUILD_ALIGN_MIN  -100
#define ESTE_GUILD_MASTER     ({"jaypeg"})

#define IS_MEMBER(p) ((p)->query_guild_name_occ() == ESTE_GUILD_NAME)


//  Guild member defines
#define MEMBER_TRACKER        "/d/Shire/guild/estehilde/tracker.c"
#define MEMBER_SAVE           ESTE_DIR + "members"

#define ESTE_HELP             ESTE_DIR + "help/"
#define ESTE_NEWS             ESTE_HELP + "news"
/* No definitions below this line */
#endif HERALD_DEFINITIONS
