#ifndef _SHIRE_PARTY_DEFS_
#define _SHIRE_PARTY_DEFS_

#include "/d/Shire/sys/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#ifndef PARTY_DIR
#define PARTY_DIR "/d/Shire/party/"
#endif  PARTY_DIR

#define PARTY_HELP PARTY_DIR+"help/"
#define PARTY_LOG  PARTY_DIR+"log/"
#define PARTY_OBJ  PARTY_DIR+"obj/"
#define PARTY_NPC  PARTY_DIR+"npc/"
#define PARTY_ARM  PARTY_DIR+"arm/"
#define PARTY_WEP  PARTY_DIR+"wep/"


#define PARTY_BANISHED_PROP       "_i_was_banished_from_shire_party"
#define LIVE_O_ROOM_BEFORE_PARTY  "_live_o_room_before_party"

// Important rooms
#define PARTY_START  (PARTY_DIR + "entrance")
#define PARTY_MASTER  (PARTY_DIR + "master")

// Save map defines.
#define MAP_FILE      (PARTY_DIR + "guilds")
#define MAP_NAME      0
#define MAP_OCC       1
#define MAP_LAY       2
#define MAP_RACE      3

#define MASTER_INVITE PARTY_OBJ+"master_invite"
#define INVITATION  PARTY_OBJ+"invite"

// Inheritable files
#define PARTY_COMMANDS  (PARTY_DIR + "commands.c")
#define PARTY_BASE      (PARTY_DIR + "party_room_base.c")


#define READ(x)   this_player()->more(read_file(x , 1))
#define HELP(x)   this_player()->more(read_file(PARTY_HELP + "x" ,1))
/* NO definitions beyond this line. */
#endif _SHIRE_PARTY_DEFS_
