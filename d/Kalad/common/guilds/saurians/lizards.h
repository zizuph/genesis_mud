/*
 * Def file for Saurian guild
 * Mirandus - Feb, 2018
 */
#include "/d/Kalad/defs.h"
 
//Guild Path Defines

#define LIZGUILD        "/d/Kalad/common/guilds/saurians/"
#define EMOTES_DIR      (LIZGUILD + "/emotes/")

#define GUILD_DATA      (LIZGUILD + "data/")
#define GUILD_LIB       (LIZGUILD + "lib/")
#define GUILD_HELP      (LIZGUILD + "help/")
#define GUILD_NEWS      (LIZGUILD + "news")
#define GUILD_STD       (LIZGUILD + "std/")
#define GUILD_TRAINER   (LZIGUILD + "rooms/train")
#define GUILD_SHADOW_LAY  (LIZGUILD + "lizard_shadow_lay")
#define GUILD_SHADOW_RACE (LIZGUILD + "lizard_shadow_race")
#define GUILD_SOUL      (LIZGUILD + "lizard_soul")
#define GUILD_ITEM      (LIZGUILD + "toothnecklace")
#define GUILD_ITEM_NAME "necklace"
#define GUILD_LOG       (LIZGUILD + "log/")
#define GUILD_SAVE      (LIZGUILD + "lizards_save")
#define GUILD_TAX_LAY       11
#define GUILD_NAME_LAY      "Lizard Fighters"
#define GUILD_STYLE_LAY     "fighter"
#define GUILD_TYPE_LAY      "fighter"
#define GUILD_ALIGN_LAY     0
#define GUILD_TAX_RACE       4
#define GUILD_NAME_RACE      "Saurians of Kalad"
#define GUILD_STYLE_RACE     "race"
#define GUILD_TYPE_RACE      "race"
#define GUILD_ROOMS     (GUILD_STD + "lizards_std")
#define GUILD_GM        ({"mirandus"})
#define MEDALLION_NAME  "_lizard_guild_item"

#define SURNAME_MANAGER     (GUILD_LIB + "saurian_surname_manager.c")
#define SOULDESC(s)         (TP->add_prop(LIVE_S_SOULEXTRA, (s)))
#define LIZARD_S_SUBLOC     "Lizard_SubLoc"

#define IS_MEMBER_RACE(p)    ((p)->query_guild_name_race() == GUILD_NAME_RACE)
#define IS_MEMBER_LAY(p)    ((p)->query_guild_name_lay() == GUILD_NAME_LAY)
#define GUILD_ITEM_ID   "_lizard_guild_item_id_"
#define LOG_SIZE        25000
#define WRITE_NAME(o)   sprintf("%-11s", capitalize((o)->query_real_name()))
#define START           (LIZGUILD + "start")
#define VALID_SUBRACES ({"human", "elf", "dwarf", "goblin"})

//Skill for Special attack
#define SS_GUILD_SPECIAL_SKILL 135100

// Special Attack Defines

#define DAMAGE_LIB          "/d/Genesis/specials/std/damage"
#define DEBUGGER_LIB        "/d/Genesis/specials/debugger/debugger_tell.h"

//History Story Defines

#define HISTORY "_i_get_history"
#define HISTORY1 "_i_get_history1"
#define HISTORY2 "_i_get_history2"
#define HISTORY3 "_i_get_history3"

/*Room Defines */

#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
    "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])