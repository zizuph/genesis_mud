#ifndef _IMLADRIS_FILE_DEFS_
#define _IMLADRIS_FILE_DEFS_
#include "/d/Shire/common/defs.h"
#ifdef 0
# include "spell.h"
# include "effect.h"
# include "list/spell.h"
# include "list/task.h"
#endif

// Root directories.
#define HEALER_DIR              "/d/Shire/healers/"
#define H_DIR                   HEALER_DIR
#define STD_SPELL_DIR           H_DIR + "lib/spell/"

// Sub directories
#define H_GUILD_DIR    	        H_DIR + "guild/"
#define H_LIB_DIR      	        H_DIR + "lib/"
#define H_OBJ_DIR      	        H_DIR + "obj/"
#define H_ARM_DIR      	        H_DIR + "arm/"
#define H_WEP_DIR      	        H_DIR + "wep/"
#define H_HERB_DIR              H_DIR + "herb/"
#define H_NPC_DIR      	        H_DIR + "npc/"
#define H_ROOM_DIR     	        H_DIR + "room/"
#define H_SPELL_DIR    	        H_DIR + "spell/"
#define H_COUNCIL_DIR  	        H_DIR + "council/"
#define H_LIB_SPELL_DIR         H_LIB_DIR + "spell/"

// Specific spell directories.
#define CW_DIR                  H_SPELL_DIR + "cw/"
#define DM_DIR                  H_SPELL_DIR + "dm/"
#define LW_DIR                  H_SPELL_DIR + "lw/"
#define BL_DIR                  H_SPELL_DIR + "bl/"

// Library files.
#define EXTRA_FILE              H_LIB_DIR + "extra"
#define SPELL_MESSAGE_FILE      H_LIB_DIR + "spellmsg"
#define ELEMENTAL_BOLT          H_LIB_DIR + "elembolt"
//#define STRING_FILE           H_LIB_DIR + "strings"

// Nice to have functions.
#define PARSE_FILE              H_LIB_DIR + "parse"
#define MESSAGE_FILE 	        H_LIB_DIR + "message"

// Spell list base file, and spell object base file.
#define SPELL_LIST_FILE         H_LIB_DIR + "spell_list"
#define SPELL_FILE              H_LIB_DIR + "spellobj"
#define LIST_MASTER             H_GUILD_DIR + "listmast"

// Where are the mudlib spell files? Currently in Rogon's open dir.
//#define STD_SPELL_FILE        "/d/Immortal/rogon/open/spell/spell"
//#define EFFECT_SHADOW_FILE    "/d/Immortal/rogon/open/spell/effect"
//#define EFFECT_OBJECT_FILE    "/d/Immortal/rogon/open/spell/effobj"
#define STD_SPELL_FILE          STD_SPELL_DIR + "spell" //ok.
#define EFFECT_SHADOW_FILE      STD_SPELL_DIR + "effect" //ok.
#define EFFECT_OBJECT_FILE      STD_SPELL_DIR + "effobj" //ok.

// Where are standard spell headers?
//#define STD_SPELL_H           "/d/Immortal/rogon/open/spell/spell.h"
//#define STD_EFFECT_H          "/d/Immortal/rogon/open/spell/effect.h"
#define STD_SPELL_H             STD_SPELL_DIR + "spell.h"
#define STD_EFFECT_H            STD_SPELL_DIR + "effect.h"

// Nice to know where to find the action() and tellem() routines.
//#define TELLEM_FILE           "/d/Immortal/rogon/open/tell"
#define TELLEM_FILE             H_LIB_DIR +"tell"

// Ok, now follows the spell lists, which are souls.
#define BARRIER_LAW             "/d/Shire/healers/spells/bl/bl"
#define DETECTION_MASTERY       "/d/Shire/healers/spells/dm/dm"
#define SPELL_DEFENCE           "/d/Shire/healers/spells/sd/sd"
#define CONCUSSIONS_WAY         "/d/Shire/healers/spells/cw/cw"
#define LIGHTS_WAY              "/d/Shire/healers/spells/lw/lw"

#define SPELL_ERROR(x)          notify_fail(x+query_syntax())
#ifndef FIXEUID
#define FIXEUID                 setuid(); seteuid(getuid())
#endif
#endif
