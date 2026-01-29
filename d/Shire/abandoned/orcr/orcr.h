// #include "/d/Shire/bits.h"
#ifndef ORCR_DEFINITIONS
#define ORCR_DEFINITIONS

#ifndef ORCRGLD_DIR
#define ORCRGLD_DIR "/d/Shire/guild/orcr/"
#endif

#define ORCR_ROOM               (ORCRGLD_DIR + "rooms/")
#define ORCR_RACE_GUILD_MASTER  ({"finwe"})
#define ORCR_RACE_SUBLOC        "orc_race_subloc"

#define SUBLOC_MISCEXTRADESC    "_subloc_misc_extra"
#define MISC_SUBLOC             ("/cmd/live/state")
#define IS_MEMBER(p) ((p)->query_guild_name_race() == ORCR_RACE_GUILD_NAME)
#define ROOM_TELL_TIME     180
#define TUNNEL_BASE             (ORCR_ROOM + "tunnel_base.c")
/* No definitions below this line */
#endif ORCR_DEFINITIONS
