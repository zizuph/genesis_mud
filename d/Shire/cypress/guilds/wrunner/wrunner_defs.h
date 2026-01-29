/* 
 * This is a set of handy definitions for the Wild Elves guild.          
 * Coded on 26/08/1995 by Tulix III. Based on the Grunts- no change there. 
 * Note: WRUNNER_DIR is defined in the file /d/Emerald/defs.h so make sure 
 * all objects that include this file also include the above file first!
 *
 * Updated June/July 2001 by Finwe for Cypress. Guild 'renamed' the Wild Elves,
 * though it still retains the titles for wildrunners and deathstalkers.

#ifndef GUILD_NAME

/* Define the general race guild characteristics */
#define GUILD_NAME          "Wild Elves Guild"
#define GUILD_TYPE          "race"
#define GUILD_STYLE         "elven wild elves"
#define GUILD_SOUL_ID       "wild elves"
#define GUILD_TAX           4
#define WRUNNER_DIR         "/d/Shire/cypress/guilds/wrunner/"
#define GUILD_OBJECT        WRUNNER_DIR + "wrunner_ring"
#define GUILD_SOUL          WRUNNER_DIR + "wrunner_soul"
#define GUILD_SHADOW        WRUNNER_DIR + "wrunner_shadow"
#define GUILD_HELP_DIR      WRUNNER_DIR + "help/"
#define GUILD_LOG           CYPRESS_DIR + "log/wrunner_guild"
#define GUILD_HELP          WRUNNER_DIR + "help/"
#define GUILD_NEWS          GUILD_HELP  + "news"
#define GUILD_TRAINER       WRUNNER_DIR + "train"
#define GUILD_RING          WRUNNER_DIR + "wrunner_ring"
#define GUILD_SAVE          WRUNNER_DIR + "wrunner_save"
#define GUILD_SPELLS_DIR    WRUNNER_DIR + "spells/"
#define GUILD_OBJ_DIR       WRUNNER_DIR + "obj/"
#define GUILD_MASTER        ({"finwe"})

#define IS_WIZ(x)           (x->query_wiz_level())
#define IS_MEMBER(p)        ((p)->query_guild_name_race() == GUILD_NAME)

#define BUILDING_BASE       WRUNNER_DIR + "base_guild_house.c"
#define LOG_SIZE            25000
#define WRITE_NAME(o)       sprintf("%-11s", capitalize((o)->query_real_name()))
#define RING_ID             "_wrunner_race_guild_ring_"
#define START               WRUNNER_DIR + "start_rm"
#define ROOM_DIR            WRUNNER_DIR + "rooms/"


