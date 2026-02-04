#ifndef WHITE_DEFS
#define WHITE_DEFS

/* Information */

#define GUILD_NAME          "Order of the White"
#define GUILD_TAX      20
#define GUILD_TYPE     "occupational"
#define GUILD_STYLE    "fighter"
#define GUILD_CMDSOUL    "/d/Terel/guilds/white/soul"
#define GUILD_SHADOW     "/d/Terel/guilds/white/shadow"



/* Useful macros */
#define MEMBER(xx)     ((xx)->query_guild_member(GUILD_NAME))
#define WHITE_LOG WHITE+"obj/white_log_object"


/* Props */

#define WHITE_ACCEPTED "_white_accepted"
#define WHITE_SEAL "_white_seal"
#define WHITE_SUBLOC "_white_subloc"
#define LIVE_I_ALACRITY "_live_i_alacrity"
#define LIVE_I_ALACRITY_RESET "_live_i_alacrity_reset"

/* Skills */

#define WHITE_ALACRITY 130040

#endif
