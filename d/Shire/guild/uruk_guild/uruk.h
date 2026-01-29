/*
	* /d/Shire/guild/uruk_guild/uruk.h
	*Definitions for the Middle Earth Uruk Race Guild
	*Altrus, December 2005
*/

#include "/d/Shire/bits.h"
#ifndef URUK_DEFINITIONS
#define URUK_DEFINITIONS

#ifndef URUKGLD_DIR
#define URUKGLD_DIR "/d/Shire/guild/uruk_guild/"
#endif

#define URUK_EMOTES_DIR           		(URUKGLD_DIR + "emotes/")
#define URUK_HELP                 		(URUKGLD_DIR + "help/")
#define URUK_NEWS                 		(URUK_HELP + "news")
#define URUK_RACE_ISENGARD_TRAINER 	(URUKGLD_DIR + "rooms/isengard_train")
#define URUK_RACE_MORGUL_TRAINER 	(URUKGLD_DIR + "rooms/morgul_train")
#define URUK_RACE_GUILD_SHADOW 	(URUKGLD_DIR + "uruk_shadow")
#define URUK_RACE_GUILD_SOUL    	(URUKGLD_DIR + "uruk_soul")
//need to put in a guild item later
//#define URUK_RACE_GUILD_BAND  		(URUKGLD_DIR + "obj/orc_band")
#define URUK_RACE_GUILD_LOG        	"/d/Shire/log/uruk_guild"
#define URUK_RACE_GUILD_SAVE      	(URUKGLD_DIR+ "uruk_save")
#define URUK_RACE_GUILD_TAX       	3
#define ORC_RACE_GUILD_NAME     	"Orcs of Middle Earth"
#define URUK_RACE_GUILD_NAME		"Uruk-hai of Middle Earth"
#define MAGE_OCC_GUILD_NAME		"Morgul Mages"
#define URUK_RACE_GUILD_STYLE    	"race"
#define URUK_RACE_GUILD_TYPE      	"race"
#define URUK_RACE_GUILD_ALIGN     	-249
#define URUK_RACE_GUILD_MASTER  	({"altrus"})
#define URUK_MORDOR				1
#define URUK_ISENGARD			2
#define URUK_RM					(URUKGLD_DIR + "rooms/")
#define MANAGER				(URUKGLD_DIR + "uruk_manager")
#define I_URUK					"_uruk_of_isengard"
#define M_URUK					"_uruk_of_mordor"

#define IS_MEMBER(p) ((p)->query_guild_name_race() == URUK_RACE_GUILD_NAME)
#define ORC_MEMBER(p) ((p)->query_guild_name_race() == ORC_RACE_GUILD_NAME)
#define MAGE_MEMBER(p) ((p)->query_guild_name_occ() == MAGE_OCC_GUILD_NAME)
//#define COMMON_INFO (URUKGLD_DIR + "common.c")
#define ITEM_ID 		"_uruk_race_guild_item_"
#define LOG_SIZE        25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define I_START         (URUKGLD_DIR + "rooms/isengard_start")
#define M_START        (URUKGLD_DIR + "rooms/morgul_start")

/* No definitions below this line */
#endif URUK_DEFINITIONS

