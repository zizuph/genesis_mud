/*********************************************************************
 * - guild.h                                                       - *
 * - Defines for the ladies club                                   - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/
#ifndef GUILD_DEFS
#define GUILD_DEFS

#include "defs.h"

#define GUILD_DIR "/d/Raumdor/guilds/lc/"
#define GUILD_NAME      "Ladies club"
#define GUILD_STYLE     "guild"

#define ARM             (GUILD_DIR + "arm/")
#define HELP            (GUILD_DIR + "help/")
#define LOG             (GUILD_DIR + "log/")
//#define NPC             (GUILD_DIR + "npc/")
#define ROOM            (GUILD_DIR + "room/")
#define BOOKS           (GUILD_DIR + "books/")
#define SCROLLS         (GUILD_DIR + "scrolls/")

#define STARTLOC        (ROOM + "start")
#define CLUB            (ROOM + "club")

#define GUILD_SOUL	(GUILD_DIR + "soul")
#define OBJECT		(GUILD_DIR + "lc_item")

#define JOINROOM        (ROOM + "join")
#define LC_SHADOW       (GUILD_DIR + "lc_shadow")

#define OBJECT_ID       ("_lc_emblem")
#define GUILD_SUBLOC	("_lc_subloc")

#define IS_MEMBER(x)    (present(OBJECT_ID, (x)))

#endif
