/* Guild.h */

#define GUILD_NAME    "Bloodsea Minotaurs"
#define GUILD_STYLE   "fighter"
#define GUILD_TAX     13


#define GUILD_DIR   "/d/Ansalon/guild/minotaurs/"

#define GUILD_SHADOW  GUILD_DIR + "lay_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "cmdsoul"
#define GUILD_EMBLEM  GUILD_DIR + "emblem"
#define GUILD_POST    GUILD_DIR + "post"
#define HELP_DIR      GUILD_DIR + "help/"

#define JOINED        "mino/joined_minotaurs"
#define LEFT          "mino/left_minotaurs" 

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"
#define MEMBER(ob) ob->query_guild_member("Bloodsea Minotaurs")

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */

#define SS_GUILD_SPECIAL_SKILL   143015

/* The default sailing skill used by Mariners, Minotaurs, and Pirates */
#define SS_SAILING_SKILL         143020

#define GUILD_STARTLOC           GUILD_DIR + "start"
