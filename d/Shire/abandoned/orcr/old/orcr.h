// #include "/d/Shire/bits.h"
#ifndef ORCR_DEFINITIONS
#define ORCR_DEFINITIONS

#ifndef ORCRGLD_DIR
#define ORCRGLD_DIR "/d/Shire/guild/orcr/"
#endif

#define ORCR_ROOM               (ORCRGLD_DIR + "rooms/")
#define ORCR_HELP               (ORCRGLD_DIR + "help/")
#define ORCR_RACE_GUILD_TRAINER (ORCRGLD_DIR + "trainroom")
#define ORCR_RACE_GUILD_SHADOW  (ORCRGLD_DIR + "orcr_shadow")
#define ORCR_RACE_GUILD_SOUL    (ORCRGLD_DIR + "orcr_soul")
#define ORCR_RACE_GUILD_BAND    (ORCRGLD_DIR + "armband")
#define ORCR_RACE_GUILD_LOG     "/d/Shire/log/orcr_guild"
#define ORCR_NEWS               (ORCR_HELP + "news")
#define ORCR_RACE_GUILD_SAVE    (ORCRGLD_DIR + "orcr_save")
#define ORCR_RACE_GUILD_TAX     3
#define ORCR_RACE_GUILD_NAME    "Orcs of Middle-earth"
#define ORCR_RACE_GUILD_STYLE   "race"
#define ORCR_RACE_GUILD_TYPE    "race"
#define ORCR_RACE_GUILD_ALIGN   -150
#define ORCR_RACE_GUILD_MASTER  ({"finwe"})
#define ORCR_RACE_SUBLOC        "orc_race_subloc"

#define SUBLOC_MISCEXTRADESC    "_subloc_misc_extra"
#define MISC_SUBLOC             ("/cmd/live/state")
#define DEFAULT_TITLE           "of Shire"
#define DEFAULT_REGION          "shireish being"
#define IS_MEMBER(p) ((p)->query_guild_name_race() == ORCR_RACE_GUILD_NAME)
#define ROOM_TELL_TIME     180
#define TUNNEL_BASE             (ORCR_ROOM + "tunnel_base.c")
/* No definitions below this line */
#endif ORCR_DEFINITIONS
