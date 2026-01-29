/*
 *  /d/Shire/guild/dunlinde/dunlinde.h
 *  Definitions for the Dunlinde guild
 *  from the Shire Domain of Genesis
 *  Jaypeg, June 1999
 */


#include "/d/Shire/bits.h"
#ifndef LINDE_DEFINITIONS
#define LINDE_DEFINITIONS

#ifndef LINDE_DIR
#define LINDE_DIR "/d/Shire/guild/dunlinde/"
#define PRIV_SPELL_DIR "/d/Shire/private/SPELLS"
#endif

#define LINDE_GUILD_TRAINER    (LINDE_DIR + "train")
#define LINDE_GUILD_SHADOW     (LINDE_DIR + "linde_shadow")
#define LINDE_GUILD_SOUL       (LINDE_DIR + "linde_soul")
#define LINDE_GUILD_OBJ        (LINDE_DIR + "robe")
#define LINDE_GUILD_SPELLS     (PRIV_SPELL_DIR + "dunlinde/songbook")
#define LINDE_GUILD_LOG        "/d/Shire/log/dunlinde"
#define LINDE_LOGS             LINDE_DIR + "log/"
#define LINDE_GUILD_TAX        11
#define LINDE_GUILD_NAME       "Dunlinde"
#define LINDE_GUILD_STYLE      "cleric"
#define LINDE_GUILD_TYPE       "occupational"
#define LINDE_GUILD_ALIGN_MIN  500
#define LINDE_GUILD_MASTER     ({"jaypeg"})

#define IS_MEMBER(p) ((p)->query_guild_name_occ() == LINDE_GUILD_NAME)


//  Guild member defines
#define MEMBER_TRACKER        "/d/Shire/guild/dunlinde/tracker.c"
#define MEMBER_SAVE            LINDE_DIR + "members"

#define LINDE_HELP             LINDE_DIR + "help/"
#define LINDE_NEWS             LINDE_HELP + "news"
/* No definitions below this line */
#endif LINDE_DEFINITIONS
