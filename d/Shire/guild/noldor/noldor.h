/*
 * /d/Shire/noldor/noldor.h
 *
 * Definitions for the Noldor Racial Guild 
 */

#include "/d/Shire/bits.h"
#ifndef NOLDOR_DEFINITIONS
#define NOLDOR_DEFINITIONS

#ifndef NOLGLD_DIR
// Defines the guild directory and assigns it to NOLGLD_DIR 
#define NOLGLD_DIR "/d/Shire/guild/noldor/"
#endif

// The number of players that can be in the guild. This was lower, but was 
// instead of removing the code.
#define GUILD_LIMIT                 999
#define NOLDOR_EMOTES_DIR           (NOLGLD_DIR + "emotes/")
#define NOLDOR_HELP                 (NOLGLD_DIR + "help/")
#define NOLDOR_NEWS                 (NOLDOR_HELP + "news")
#define NOLDOR_RACE_GUILD_TRAINER   (NOLGLD_DIR + "train")
#define NOLDOR_RACE_GUILD_SHADOW    (NOLGLD_DIR + "noldor_shadow")
#define NOLDOR_RACE_GUILD_SOUL      (NOLGLD_DIR + "noldor_soul")
#define NOLDOR_RACE_GUILD_GLOW      (NOLGLD_DIR + "obj/glow")
#define NOLDOR_RACE_GUILD_CIRCLET   (NOLGLD_DIR + "obj/circlet")
#define NOLDOR_RACE_GUILD_LOG       "/d/Shire/log/noldor_guild"
// The file holding all guild members
#define NOLDOR_RACE_GUILD_SAVE      (NOLGLD_DIR + "noldor_save")
// How much the playerh is taxed
#define NOLDOR_RACE_GUILD_TAX       3
// The guil'ds long name, used to check if a member, and when you do <guild list>
#define NOLDOR_RACE_GUILD_NAME      "Noldor of Imladris"
// The guild style. Since this is a racial, it will always be racial
#define NOLDOR_RACE_GUILD_STYLE     "race"
// The guild type. It will be occupational, layman, racial, or craft
#define NOLDOR_RACE_GUILD_TYPE      "race"
// The minimum alignment to join
#define NOLDOR_RACE_GUILD_ALIGN     99
// Who the GM is
#define NOLDOR_RACE_GUILD_MASTER    ({"finwe"})
// The number of days before a player gets auto-removed
#define NOLDOR_RACE_GUILD_INACTIVE  365
// The player's title, ie, "Finwe of the Noldor of Imladris"
#define NOLDOR_RACE_GUILD_TITLE     "of the Noldor of Imladris"

// Shortcut used to check if the playerh is a Noldor
#define IS_MEMBER(p) ((p)->query_guild_name_race() == NOLDOR_RACE_GUILD_NAME)
#define START_SINGING (TP->add_prop("_live_i_am_singing", 1))
#define STOP_SINGING  (TP->remove_prop("_live_i_am_singing", 1))
#define IS_SINGING    (TP->query_prop("_live_i_am_singing"))
#define BUILDING_BASE (NOLGLD_DIR + "base_guild_house.c")
#define COMMON_INFO   (NOLGLD_DIR + "common.c")
#define LOG_SIZE       25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
// The guild object id
#define CIRCLET_ID        "_noldor_race_guild_circlet_"
#define START          (NOLGLD_DIR + "start_rm")
#define EMOTE_DIR      (NOLGLD_DIR + "emotes/")
#define ATTACKS_ELFS   "/d/Shire/rivendell/save_info.o"


/* No definitions below this line */
#endif NOLDOR_DEFINITIONS

