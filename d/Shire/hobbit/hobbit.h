/*
 * /d/Shire/hobbit/hobbit.h
 *
 * Some definitions for the hobbit race guild
 */

#include "/d/Shire/bits.h"
#ifndef HOBBIT_DEFINITIONS
#define HOBBIT_DEFINITIONS

#ifndef HOBGLD_DIR
#define HOBGLD_DIR "/d/Shire/hobbit/"
#endif

#define HOBBIT_HELP     (HOBGLD_DIR +"help/")

#define HOBBIT_RACE_GUILD_TRAINER (HOBGLD_DIR + "trainroom")
#define HOBBIT_RACE_GUILD_SHADOW (HOBGLD_DIR + "hobbit_shadow")

#define HOBBIT_RACE_GUILD_SOUL   (HOBGLD_DIR + "hobbit_soul")

#define HOBBIT_RACE_GUILD_PIPE   (HOBGLD_DIR + "pipe")

#define HOBBIT_RACE_GUILD_LOG    "/d/Shire/log/hobbit_guild"

#define HOBBIT_NEWS              HOBBIT_HELP + "news"

#define HOBBIT_RACE_GUILD_SAVE   (HOBGLD_DIR + "hobbit_save")

#define HOBBIT_RACE_GUILD_TAX    3

#define HOBBIT_RACE_GUILD_NAME   "Adventuresome Hobbits Guild"

#define HOBBIT_RACE_GUILD_STYLE  "race"

#define HOBBIT_RACE_GUILD_TYPE   "race"

#define HOBBIT_RACE_GUILD_ALIGN  -150

#define HOBBIT_RACE_GUILD_MASTER  ({"jaypeg"})

#define IS_MEMBER(p) ((p)->query_guild_name_race() == HOBBIT_RACE_GUILD_NAME)


/* No definitions below this line */
#endif HOBBIT_DEFINITIONS
