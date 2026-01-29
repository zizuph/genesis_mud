/*
 * Def file for halfling guild
 * Finwe, September 2015
 */

#define HALFGLD_DIR     "/d/Faerun/guilds/halflings/"
#define VILLAGE_DIR     "/d/Faerun/halflings/"
#define EMOTES_DIR      (HALFGLD_DIR + "/emotes/")

#define GUILD_DATA      (HALFGLD_DIR + "data/")
#define GUILD_HELP      (HALFGLD_DIR + "help/")
#define GUILD_NEWS      (GUILD_HELP + "news")
#define GUILD_STD       (HALFGLD_DIR + "std/")
#define GUILD_TRAINER   (HALFGLD_DIR + "rooms/train")
#define GUILD_SHADOW    (HALFGLD_DIR + "half_shadow")
#define GUILD_SOUL      (HALFGLD_DIR + "half_soul")
#define GUILD_ITEM      (HALFGLD_DIR + "pendant")
#define GUILD_ITEM_NAME "pendant"
#define GUILD_LOG       "/d/Faerun/log/halflings_guild"
#define GUILD_SAVE      (HALFGLD_DIR + "halflings_save")
#define GUILD_FOOD      (HALFGLD_DIR + "food/")
#define GUILD_LIB       (HALFGLD_DIR + "lib/")
#define GUILD_TAX       4
#define GUILD_NAME      "Halflings of Faerun"
#define GUILD_STYLE     "race"
#define GUILD_TYPE      "race"
#define GUILD_ALIGN     0
#define GUILD_ROOMS     (HALFGLD_DIR + "base_room")
#define GUILD_GM        ({"finwe"})
#define MEDALLION_NAME  "_halfling_guild_item"

#define PIE_MASTER      (GUILD_FOOD + "pie_master")
#define PIE_CASE        "_halfling_kitchen_pie_case"

#define IS_MEMBER(p)    ((p)->query_guild_name_race() == GUILD_NAME)
#define GUILD_ITEM_ID   "_halflings_guild_item_id_"
// #define LOG_SIZE        25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))
#define START         	(HALFGLD_DIR + "rm_start")

// Master Objects
#define SURNAME_MANAGER     (GUILD_LIB + "halfling_surname_manager")

// minimum mana for hsearch
#define HMIN_MANA       25

// Foods for hsearch 
#define FOOD_TYPES  ({"apple", "dark_beer", "dark_cider", "duck_egg", \
    "large_carrot", "mead", "pork_pie", "quail_egg", "rabbit_pie", \
    "spinach_tart", "spring_water", "sweet_wine"})
