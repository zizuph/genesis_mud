/*
 * /d/Shire/guild/peredhil/pered.h
 * Definitions for Peredhil
 */

#include "/d/Shire/bits.h"


#define PERED_DIR "/d/Shire/guild/peredhil/"

#define PERED_HELP      (PERED_DIR +"help/")

#define PERED_TRAIN     (PERED_DIR + "trainroom")
#define PERED_SHADOW    (PERED_DIR + "pered_shadow")
#define PERED_SOUL      (PERED_DIR + "pered_soul")
#define PERED_OBJ       (PERED_DIR + "obj/brooch")
#define PERED_LOG       "/d/Shire/log/pered_guild"
#define PERED_NEWS      PERED_HELP + "news"
#define PERED_SAVE      (PERED_DIR + "pered_save")
#define PERED_TAX       3
#define PERED_NAME      "Peredhil Guild"
#define PERED_STYLE     "race"
#define PERED_TYPE      "race"
#define PERED_ALIGN     -150
#define PERED_MASTER    ({"finwe"})
#define PERED_OBJ_ID    ("_pered_guild_obj")
#define PERED_RACE_NAME "half-elf"

#define BUILDING_BASE   (PERED_DIR + "base_guild_house.c")
#define LOG_SIZE        25000

#define IS_MEMBER(p)    ((p)->query_guild_name_race() == PERED_NAME)
// Neutral, must be neutral or better to join
#define MIN_ALIGN       -79 
// Disagreeable, If players are untrustworthy or evil, booted
#define BOOT_ALIGN      -160
