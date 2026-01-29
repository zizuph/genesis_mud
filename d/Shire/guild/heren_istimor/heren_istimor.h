/*
 * /d/Shire/guild/heren_istimor/heren_istimor.h
 *
 * Some definitions for the Heren Istimor occupational guild
 */


#include "/d/Shire/bits.h"
#ifndef HEREN_ISTIMOR_DEFINITIONS
#define HEREN_ISTIMOR_DEFINITIONS

#ifndef HEREN_ISTIMOR_DIR
#define HEREN_ISTIMOR_DIR "/d/Shire/guild/heren_istimor/"
#endif

#define HEREN_ISTIMOR_GUILD_TRAINER (HEREN_ISTIMOR_DIR + "train")
#define HEREN_ISTIMOR_GUILD_SHADOW (HEREN_ISTIMOR_DIR + "heren_istimor_shadow")

#define HEREN_ISTIMOR_GUILD_SOUL   (HEREN_ISTIMOR_DIR + "heren_istimor_soul")

#define HEREN_ISTIMOR_GUILD_OBJ   (HEREN_ISTIMOR_DIR + "necklace")

#define HEREN_ISTIMOR_GUILD_SPELLS  (HEREN_ISTIMOR_DIR + "guild_gem")

#define HEREN_ISTIMOR_GUILD_LOG    "/d/Shire/log/heren_istimor"

#define HEREN_ISTIMOR_LOGS         HEREN_ISTIMOR_DIR + "log/"

#define HEREN_ISTIMOR_GUILD_TAX    22

#define HEREN_ISTIMOR_GUILD_NAME   "Heren Istimor"

#define HEREN_ISTIMOR_GUILD_STYLE  "fighter"

#define HEREN_ISTIMOR_GUILD_TYPE   "occupational"

#define HEREN_ISTIMOR_GUILD_ALIGN_MIN   600

#define HEREN_ISTIMOR_GUILD_MASTER ({"palmer"})

#define IS_MEMBER(p) ((p)->query_guild_name_occ() == HEREN_ISTIMOR_GUILD_NAME)


//  Guild member defines
#define MEMBER_TRACKER   "/d/Shire/guild/heren_istimor/tracker.c"
#define MEMBER_SAVE      HEREN_ISTIMOR_DIR + "members"

#define HEREN_ISTIMOR_HELP      HEREN_ISTIMOR_DIR + "help/"
#define HEREN_ISTIMOR_NEWS      HEREN_ISTIMOR_HELP + "news"
/* No definitions below this line */
#endif HEREN_ISTIMOR_DEFINITIONS
