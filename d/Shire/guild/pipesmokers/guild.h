/* Guild.h file 
 *
 * Standard guild defines added here
 */

#define GUILD_NAME    "Pipesmokers of the Shire"
#define GUILD_STYLE   "craft"
#define GUILD_TAX     0


#define GUILD_DIR   "/d/Shire/guild/pipesmokers/"
//#define GUILD_DIR   "/w/arman/open/pipesmokers/"

#define GUILD_SHADOW  GUILD_DIR + "craft_shadow"
#define GUILD_CMDSOUL GUILD_DIR + "cmdsoul"
#define GUILD_EMBLEM  GUILD_DIR + "emblem"
#define HELP_DIR      GUILD_DIR + "help/"

/* Defines for logging of joining and leaving */
#define JOINED        "joined_pipesmokers"
#define LEFT          "left_pipesmokers" 

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID "pipesmokers_guild_object"

/* Useful macros you can call 
#define MEMBER(x)   x->query_guild_member("Pipesmokers of the Shire")
#define E(ob)        environment(ob)
#define HIS(x)        ((x)->query_possessive())
#define HIM(x)        ((x)->query_objective())
#define HE(x)         ((x)->query_pronoun())


/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 *
 * For the Shire, skills should be outlined in /d/Shire/skills.h
 * The one outlined below SHOULD be confirmed and added to the above file.
 */

#define SS_GUILD_SPECIAL_SKILL   112300

/* Room defines if required          */
#define GUILD_STARTLOC           GUILD_DIR + "start"
