#ifndef _SDIR_DEFS_
#define _SDIR_DEFS_ 1

#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/include/lib.h"

#include "std/spell.h"
#include "std/effect.h"
#include "list/spell.h"
#include "list/task.h"

/* Additional directories. */

#ifndef D_SDIR
#  define D_SDIR "/d/Shire/rogon/sdir/"
#endif

#define D_STD	D_SDIR + "std/"
#define D_LIST	D_SDIR + "list/"
#define D_GUILD D_SDIR + "guild/"
#define D_SLIB	D_SDIR + "lib/"

#define D_CW   D_SDIR + "cw/"
#define D_DM   D_SDIR + "dm/"
#define D_LW   D_SDIR + "lw/"
#define D_FL   D_SDIR + "fl/"

#define EXTRA_FILE	   "/d/Shire/rogon/sdir/lib/slextra"
#define SPELL_MESSAGE_FILE "/d/Shire/rogon/sdir/lib/spellmsg"
#define PARSE_FILE	   "/d/Shire/rogon/sdir/lib/parse"
#define MESSAGE_FILE	   "/d/Shire/rogon/sdir/lib/message"
#define ELEMENTAL_BOLT	   "/d/Shire/rogon/sdir/lib/elembolt"

#define SPELL_LIST_FILE    "/d/Shire/rogon/sdir/list/splist"
#define SPELL_FILE	   "/d/Shire/rogon/sdir/list/spellobj"

#define STD_SPELL_FILE	   "/d/Shire/rogon/sdir/std/spell"
#define REDUCE_FILE	   "/d/Shire/rogon/sdir/std/reducing"
#define EFFECT_SHADOW_FILE "/d/Shire/rogon/sdir/std/effect"
#define EFFECT_OBJECT_FILE "/d/Shire/rogon/sdir/std/effobj"
#define PROP_PART_FILE	   "/d/Shire/rogon/sdir/std/proppart"

#define TELLEM_FILE	   "/d/Shire/common/lib/tell"

#define BARRIER_LAW	  "/d/Shire/rogon/sdir/bl/bl"
#define DETECTION_MASTERY "/d/Shire/rogon/sdir/dm/dm"
#define SPELL_DEFENCE	  "/d/Shire/rogon/sdir/sd/sd"
#define CONCUSSIONS_WAY   "/d/Shire/rogon/sdir/cw/cw"
#define FIRE_LAW	  "/d/Shire/rogon/sdir/fl/fl"
#define LIGHTS_WAY	  "/d/Shire/rogon/sdir/lw/lw"

#define LIST_MASTER	  "/d/Shire/rogon/sdir/guild/listmast"

#define SPELL_ERROR(x) notify_fail(x+query_syntax())
#define FIX_UID        setuid(); seteuid(getuid())

#endif
