
/* 
   Gully Dwarf Definitions

   Based on code by Maniac@Genesis, March 1997 
   Copyright (C) Miguel Leith 1997
*/ 

#ifndef GULLY_DEFS
#define GULLY_DEFS

#define GULLY_DIR "/d/Krynn/xak/gully/guild/"

/* admin defs */ 
#define GULLY_GUILD_NAME "Aghar of Krynn" 
#define GULLY_GUILD_TYPE "race"
#define GULLY_GUILD_STYLE "race" 
#define GULLY_GUILD_TAX 1
#define GULLY_GM_NAME "Karath"

#define GULLY_GROUP 3 
#define GULLY_BIT 0 
#define GULLY_BIT2 1 
#define GULLY_DOM "Krynn" 

#define IS_GULLY(pl) (pl->query_guild_name_race() == GULLY_GUILD_NAME) 

#define GULLY_SHADOW (GULLY_DIR+"gully_shadow") 

#define GULLY_SOUL (GULLY_DIR+"gully_soul")

#define GULLY_LEVEL_TITLE_ARR \
 ({ "Apprentice Grub Gatherer", "Assistant Mushroom Taster", "Speedy Evader of Dragons", "Famous Rat-Basher", "Prospective Highbulp" })

#define GULLY_NUM_LEVEL_TITLES 5
#define GULLY_BASE_TITLE "of the Aghar"


/* room defs */ 
#define GULLY_ROOMS GULLY_DIR
#define GULLY_TRAINROOM (GULLY_ROOMS+"gully_trainroom") 
#define GULLY_STARTROOM (GULLY_ROOMS+"gully_startroom") 
#define GULLY_BOARDROOM (GULLY_ROOMS+"gully_boardroom") 
#define GULLY_POSTROOM (GULLY_ROOMS+"gully_post") 
#define GULLY_COMMONROOM (GULLY_ROOMS+"gully_commonroom") 

/* object defs */ 
#define GULLY_GUILDMASTER (GULLY_DIR + "guildmaster")
#define GULLY_BOARD (GULLY_DIR + "gully_board")
#define GULLY_JOIN_INFO (GULLY_DIR + "gully_join_info.txt")
#define GULLY_COMMAND_INFO (GULLY_DIR + "gully_command_info.txt")
#define GULLY_BOARD_NOTES (GULLY_DIR+"notes/")

/* save related defs */ 
#define GULLY_SAVE (GULLY_DIR + "GULLY_save")

#endif
