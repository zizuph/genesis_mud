/* Guild.h */

#define GUILD_NAME    "Mariners of Genesis"
#define GUILD_STYLE   "craft"
#define GUILD_TAX     2


#define GUILD_DIR   "/d/Ansalon/guild/mariner/"

#define GUILD_SHADOW  GUILD_DIR + "craft_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "cmdsoul"
#define GUILD_EMBLEM  GUILD_DIR + "emblem"
#define HELP_DIR      GUILD_DIR + "help/"

#define JOINED        "mariner/joined_mariner"
#define LEFT          "mariner/left_mariner" 

#define MARINER_BOARD GUILD_DIR + "board/"

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"
#define MEMBER(ob) ob->query_guild_member("Mariners of Genesis")

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */

#define SS_GUILD_SPECIAL_SKILL   143020



#define GUILD_STARTLOC           GUILD_DIR + "start"
