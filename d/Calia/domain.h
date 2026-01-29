/* default include file for all files in Calia */

/* some abbreviations */

#ifndef CALIA_DOMAIN_DEFS_DEFINED
#define CALIA_DOMAIN_DEFS_DEFINED

#ifndef TP
#define TP this_player()
#endif

#ifndef TO
#define TO this_object()
#endif

#ifndef THIS
#define THIS this_object()
#endif

#ifndef BS
#define BS(x) break_string(x, 79)
#endif

#ifndef NF
#define NF(x) notify_fail(x)
#endif

#define member(e, s) (member_array(e, s) != -1)
#define IN                 add_prop(ROOM_I_INSIDE,1)
#define OUT                add_prop(ROOM_I_INSIDE,0)
#define AE       add_exit
#define AI       add_item
#define ACI       add_cmd_item

#ifndef NEVERKNOWN
#define NEVERKNOWN    add_prop(LIVE_I_NEVERKNOWN,1)
#endif

#ifndef ALWAYSKNOWN
#define ALWAYSKNOWN    add_prop(LIVE_I_ALWAYSKNOWN,1)
#endif

/* domain specific defines, these should be the only ones !! */

#define DOMAIN "Calia"
#define STAND_DIR "/d/Calia/"
#define DOMAIN_DIR "/d/Calia/"
#define CALIAN_GUILD_BASE_DIR "/d/Calia/guilds/calians/"
#define CALIAN_GUILD_BASE_DEF "/d/Calia/guilds/calians/defs.h"

#define GSL_SHIP_INCLUDES     "/d/Genesis/ship_new/ships.h"

#define CALIA_FILE_DEFS "/d/Calia/sys/files.h"

#endif
