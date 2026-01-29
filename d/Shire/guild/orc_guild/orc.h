/*
	* /d/Shire/guild/orc.h
	*Definitions for the Middle Earth Orc Race Guild
	*Altrus, May 2005
*/

#include "/d/Shire/bits.h"
#ifndef ORC_DEFINITIONS
#define ORC_DEFINITIONS

#ifndef ORCGLD_DIR
#define ORCGLD_DIR "/d/Shire/guild/orc_guild/"
#endif

#define ORC_EMOTES_DIR           		(ORCGLD_DIR + "emotes/")
#define ORC_HELP                 		(ORCGLD_DIR + "help/")
#define ORC_NEWS                 		(ORC_HELP + "news")
#define ORC_RACE_GUILD_TRAINER 	(ORCGLD_DIR + "rooms/train")
#define ORC_RACE_GUILD_SHADOW 	(ORCGLD_DIR + "orc_shadow")
#define ORC_RACE_GUILD_SOUL      	(ORCGLD_DIR + "orc_soul")
#define ORC_RACE_GUILD_BAND  		(ORCGLD_DIR + "obj/orc_band")
#define ORC_RACE_GUILD_LOG        	"/d/Shire/log/orc_guild"
#define ORC_RACE_GUILD_SAVE      	(ORCGLD_DIR+ "orc_save")
#define ORC_RACE_GUILD_TAX       	 3
#define ORC_RACE_GUILD_NAME     	 "Orcs of Middle Earth"
#define URUK_RACE_GUILD_NAME		"Uruk-hai of Middle Earth"
#define MAGE_OCC_GUILD_NAME		"Morgul Mages"
#define ORC_RACE_GUILD_STYLE    	 "race"
#define ORC_RACE_GUILD_TYPE      	 "race"
#define ORC_RACE_GUILD_ALIGN     	 -249
#define ORC_RACE_GUILD_MASTER  	 ({"altrus"})

#define IS_MEMBER(p) ((p)->query_guild_name_race() == ORC_RACE_GUILD_NAME)
#define URUK_MEMBER(p) ((p)->query_guild_name_race() == URUK_RACE_GUILD_NAME)
#define MAGE_MEMBER(p) ((p)->query_guild_name_occ() == MAGE_OCC_GUILD_NAME)
//#define COMMON_INFO (ORCGLD_DIR + "common.c")
#define BAND_ID 		"_orc_race_guild_band_"
#define LOG_SIZE       25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define START         	(ORCGLD_DIR + "rooms/start")

/* No definitions below this line */
#endif ORC_DEFINITIONS

