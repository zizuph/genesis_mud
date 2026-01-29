/* Guild.h */

#define GUILD_NAME    "Orcs of Middle-earth"
#define GUILD_STYLE   "racial"
#define GUILD_TAX     2


#define GUILD_DIR    "/d/Shire/guild/orcr/"

#define GUILD_SHADOW  GUILD_DIR + "orcr_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "orcr_soul"
#define GUILD_EMBLEM  GUILD_DIR + "armband"
#define GUILD_POST    GUILD_DIR + "post"
#define ORCR_ROOM     GUILD_DIR + "rooms"

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + "armband"

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define SS_GUILD_SPECIAL_SKILL 100001

#define GUILD_STARTLOC GUILD_DIR + "start"
#define TUNNEL_BASE    (ORCR_ROOM + "tunnel_base.c")
#define ROOM_TELL_TIME     180

