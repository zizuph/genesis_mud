/*
	* /d/Shire/guild/miners/miners.h
	*Definitions for the Dwarven miners race guild
	*Altrus, August 2005
*/

#include "/d/Shire/bits.h"
#ifndef M_DEFINITIONS
#define M_DEFINITIONS

#ifndef MGLD_DIR
#define MGLD_DIR "/d/Shire/guild/miners/"
#endif

#define M_EMOTES_DIR           	(MGLD_DIR + "emotes/")
#define M_HELP                 		(MGLD_DIR + "help/")
#define M_NEWS                 	(MGLD_DIR + "news")
#define M_RACE_GUILD_TRAINER 	(MGLD_DIR + "rooms/train")
#define M_RACE_GUILD_SHADOW 	(MGLD_DIR + "m_shadow")
#define M_RACE_GUILD_SOUL      	(MGLD_DIR + "m_soul")
#define M_RACE_GUILD_ITEM  	(MGLD_DIR + "obj/m_lantern")
#define M_RACE_GUILD_LOG        	"/d/Shire/log/m_guild"
#define M_RACE_GUILD_SAVE      	(MGLD_DIR + "m_save")
#define M_RACE_GUILD_TAX       	 4
#define M_RACE_GUILD_NAME     	 "Dwarven miners"
#define M_RACE_GUILD_STYLE    	 "race"
#define M_RACE_GUILD_TYPE      	 "race"
#define M_RACE_GUILD_ALIGN     	 0
#define M_RACE_GUILD_MASTER  	 ({"altrus"})

#define IS_MEMBER(p) ((p)->query_guild_name_race() == M_RACE_GUILD_NAME)
#define ITEM_ID 		"_m_race_guild_lantern_"
#define LOG_SIZE       25000
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define START         	(MGLD_DIR + "rooms/start")

/* No definitions below this line */
#endif M_DEFINITIONS

