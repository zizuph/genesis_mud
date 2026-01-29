/*
 * /d/Shire/herald/herald.h
 *
 * Some definitions for the Heralds of the Valar layman guild
 */


#include "/d/Shire/bits.h"
#ifndef HERALD_DEFINITIONS
#define HERALD_DEFINITIONS

#ifndef HERALD_DIR
#define HERALD_DIR "/d/Shire/herald/"
#endif

#define HERALD_GUILD_TRAINER (HERALD_DIR + "train")
#define HERALD_GUILD_SHADOW (HERALD_DIR + "herald_shadow")

#define HERALD_GUILD_SOUL   (HERALD_DIR + "herald_soul")

#define HERALD_GUILD_OBJ   (HERALD_DIR + "robe")

#define HERALD_GUILD_SPELLS  (HERALD_DIR + "prayerbook")

#define HERALD_GUILD_LOG    "/d/Shire/log/herald"

#define HERALD_LOGS         HERALD_DIR + "log/"

#define HERALD_GUILD_TAX    11

#define HERALD_GUILD_NAME   "Heralds of the Valar"

#define HERALD_GUILD_STYLE  "cleric"

#define HERALD_GUILD_TYPE   "layman"

#define HERALD_GUILD_ALIGN_MIN   -100

#define HERALD_GUILD_MASTER ({"jaypeg"})

#define IS_MEMBER(p) ((p)->query_guild_name_lay() == HERALD_GUILD_NAME)


//  Guild member defines
#define MEMBER_TRACKER   "/d/Shire/herald/tracker.c"
#define MEMBER_SAVE      HERALD_DIR + "members"

#define HERALD_HELP      HERALD_DIR + "help/"
#define HERALD_NEWS      HERALD_HELP + "news"
/* No definitions below this line */
#endif HERALD_DEFINITIONS
