/* default include file for all files in Calia */

/* some abbreviations */

#ifndef CALIA_DOMAIN_DEFS_DEFINED
#define CALIA_DOMAIN_DEFS_DEFINED

#define TP this_player()
#define TO this_object()
#define THIS this_object()
#define BS(x) break_string(x, 79)
#define NF(x) notify_fail(x)
#define member(e, s) (member_array(e, s) != -1)
#define IN                 add_prop(ROOM_I_INSIDE,1)
#define OUT                add_prop(ROOM_I_INSIDE,0)
#define AE       add_exit
#define AI       add_item
#define ACI       add_cmd_item
#define NEVERKNOWN    add_prop(LIVE_I_NEVERKNOWN,1)
#define ALWAYSKNOWN    add_prop(LIVE_I_ALWAYSKNOWN,1)

/* domain specific defines, these should be the only ones !! */

#define DOMAIN "Calia"
#define STAND_DIR "/d/Calia/"
#define DOMAIN_DIR "/d/Calia/"

#define CALIA_FILE_DEFS "/d/Calia/sys/files.h"

#endif
