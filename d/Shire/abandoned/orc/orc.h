/*
 * /d/Shire/orc/orc.h
 *
 * Some definitions for the orc race guild
 */

#include "/d/Shire/bits.h"
#ifndef ORC_DEFINITIONS
#define ORC_DEFINITIONS

#ifndef ORCGLD_DIR
#define ORCGLD_DIR "/d/Shire/guild/orc/"
#endif

#define ORC_HELP     (ORCGLD_DIR +"help/")

#define ORC_RACE_GUILD_TRAINER (ORCGLD_DIR + "trainroom")
#define ORC_RACE_GUILD_SHADOW (ORCGLD_DIR + "orc_shadow")

#define ORC_RACE_GUILD_SOUL   (ORCGLD_DIR + "orc_soul")

#define ORC_RACE_GUILD_ARMBAND (ORCGLD_DIR + "armband")

#define ORC_RACE_GUILD_LOG    "/d/Shire/log/orc_guild"

#define ORC_NEWS              ORC_HELP + "news"

#define ORC_RACE_GUILD_SAVE   (ORCGLD_DIR + "orc_save")

#define ORC_RACE_GUILD_TAX    3

#define ORC_RACE_GUILD_NAME   "Fearsome Orc Guild"

#define ORC_RACE_GUILD_STYLE  "race"

#define ORC_RACE_GUILD_TYPE   "race"

#define ORC_RACE_GUILD_ALIGN  -150

#define ORC_RACE_GUILD_MASTER  ({"finwe"})

#define IS_MEMBER(p) ((p)->query_guild_name_race() == ORC_RACE_GUILD_NAME)


/* No definitions below this line */
#endif ORC_DEFINITIONS
