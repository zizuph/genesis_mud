/*
 *  /d/Sparkle/guild/new_merc/merc_defs.h
 * 
 *  These are the definition files for the Mercenary Guild of Sparkle.
 *
 *  Created December 2008, by Cooper Sherry (Gorboth)
 */

#define GUILD_NAME    "Free Mercenary Guild"
#define GUILD_STYLE   "fighter"
#define GUILD_TAX     29


#define GUILD_DIR    "/d/Sparkle/guilds/new_merc/"
#define DOORS_DIR    GUILD_DIR + "doors/"
#define DATA_DIR     GUILD_DIR + "data/"
#define OBJ_DIR      GUILD_DIR + "obj/"
#define LOG_DIR      GUILD_DIR + "log/"
#define DOC_DIR      GUILD_DIR + "doc/"
#define NPC_DIR      GUILD_DIR + "npc/"
#define SPECIALS_DIR GUILD_DIR + "specials/"
#define ROOM_DIR     GUILD_DIR + "rooms/"
#define EVENT_DIR    GUILD_DIR + "event/"
#define MEMBER_DIR   DATA_DIR + "member_save/"
#define BOOKS_DIR    GUILD_DIR + "books/"
#define SHADOWS_DIR  GUILD_DIR + "shadows/"
#define SOULS_DIR    GUILD_DIR + "souls/"

#define GUILD_SHADOW   SHADOWS_DIR + "occ_shadow"
#define GUILD_CMDSOUL  SOULS_DIR + "cmdsoul"
#define GUILD_EMBLEM   OBJ_DIR + "insignia"
#define GUILD_POST     "/d/Genesis/start/human/town/post"
#define GUILD_A_TRAIN (ROOM_DIR + "adapt_train")
#define MERC_MASTER   (OBJ_DIR + "merc_master")
#define MERC_ROOM_BASE ROOM_DIR + "merc_room"
#define SPARKLE_NPC_BASE "/d/Sparkle/area/city/npc/sparkle_npc"

#define MERC_ADAPT_ITEM     1
#define MERC_ADAPT_AMOUNT   2

#define MERC_ADAPT_TRAINER  0
#define MERC_ADAPT_LOCATION 1
#define MERC_ADAPT_DESC     2
#define MERC_ADAPT_ATTITUDE 3

#define ADAPT_BEGIN_COST    10
#define ADAPT_RETURN_COST   2

#define RIVERNAME           "Copper"
#define MERC_SCHOLAR        "Mellok"

#define MERC_COST_PROP      "_merc_s_cost_asked"
#define TRAINING_PROP       "_merc_guild_training_prop"
#define MERC_NEW_SKILL_FLAG "_merc_new_skill_flag"
#define MERC_NPC            "_merc_i_npc"
#define MERC_WIPED_FEET     "_merc_wiped_feet"
#define GOBLIN_RUNT         "_event_goblin_runt"
#define EVENT_GOBLIN        "_event_goblin"


/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID GUILD_NAME + " emblem"

/* The skill number for the guild's special skill.
 * Check with the liege of your domain to get your own skills.
 */
#define SS_MERC_ADAPT_SKILL   151010
#define SS_MERC_TACTICS_SKILL 151011

#define GUILD_STARTLOC      ROOM_DIR + "dummy_startloc"

#define     IS_MERC(x)     ((x)->query_guild_name_occ() == GUILD_NAME ||\
                            (x)->id(MERC_NPC))

#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n")