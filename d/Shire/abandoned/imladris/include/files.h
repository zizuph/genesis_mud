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
#define IMLADRIS_DIR   "/d/Shire/imladris/"
#define H_DIR          IMLADRIS_DIR
#define ROGON_DIR      "/d/Immortal/rogon/open/"
#define STD_SPELL_DIR  ROGON_DIR + "spell/"

// Sub directories
#define H_SPELL_DIR    H_DIR + "spell/"
#define H_GUILD_DIR    H_DIR + "guild/"
#define H_LIB_DIR      H_DIR + "lib/"
#define H_OBJ_DIR      H_DIR + "obj/"
#define H_ARM_DIR      H_DIR + "arm/"
#define H_WEP_DIR      H_DIR + "wep/"
#define H_HERB_DIR     H_DIR + "herb/"
#define H_NPC_DIR      H_DIR + "npc/"
#define H_ROOM_DIR     H_DIR + "room/"
#define H_SPELL_DIR    H_DIR + "spell/"

// Specific spell directories.
#define CW_DIR         H_SPELL_DIR + "cw/"
#define DM_DIR         H_SPELL_DIR + "dm/"
#define LW_DIR         H_SPELL_DIR + "lw/"
#define BL_DIR         D_SPELL_DIR + "fl/"

// Library files.
#define EXTRA_FILE	   H_LIB_DIR + "extra"
#define SPELL_MESSAGE_FILE H_LIB_DIR + "spellmsg"
#define ELEMENTAL_BOLT	   H_LIB_DIR + "elembolt"

// Nice to have functions.
#define PARSE_FILE	   "/d/Immortal/rogon/lib/parse"
#define MESSAGE_FILE	   "/d/Immortal/rogon/open/message"

// Spell list base file, and spell object base file.
#define SPELL_LIST_FILE    H_LIB_DIR + "splist"
#define SPELL_FILE	   H_LIB_DIR + "spellobj"
#define LIST_MASTER        H_GUILD_DIR + "listmast"

// Where are the mudlib spell files? Currently in Rogon's open dir.
#define STD_SPELL_FILE	   "/d/Immortal/rogon/open/spell/spell"
#define EFFECT_SHADOW_FILE "/d/Immortal/rogon/open/spell/effect"
#define EFFECT_OBJECT_FILE "/d/Immortal/rogon/open/spell/effobj"

// Where are standard spell headers?
#define STD_SPELL_H        "/d/Immortal/rogon/open/spell/spell.h"
#define STD_EFFECT_H       "/d/Immortal/rogon/open/spell/effect.h"

// Nice to know where to find the action() and tellem() routines.
#define TELLEM_FILE	   "/d/Immortal/rogon/open/tell"

// Ok, now follows the spell lists, which are shadows.
#define BARRIER_LAW	  "/d/Shire/imladris/spell/bl/bl"
#define DETECTION_MASTERY "/d/Shire/imladris/spell/dm/dm"
#define SPELL_DEFENCE	  "/d/Shire/imladris/spell/sd/sd"
#define CONCUSSIONS_WAY   "/d/Shire/imladris/spell/cw/cw"
#define LIGHTS_WAY	  "/d/Shire/imladris/spell/lw/lw"

#define SPELL_ERROR(x) notify_fail(x+query_syntax())

#ifndef FIXEUID
#  define FIXEUID        setuid(); seteuid(getuid())
#endif

#endif
