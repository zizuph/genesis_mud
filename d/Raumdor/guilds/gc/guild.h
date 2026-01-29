/* Defines for the club
 * Gentlemans club
 * Created by Damaris 10/2001
 * Updated to be used in Genesis 
 * By Damaris 11/Y2K
 */
#ifndef GUILD_DEFS
#define GUILD_DEFS

#include "defs.h"

#define GUILD_DIR "/d/Raumdor/guilds/gc/"
#define GUILD_NAME      "Gentleman's club"
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
#define OBJECT		(GUILD_DIR + "gc_item")

#define JOINROOM        (ROOM + "join")
#define GC_SHADOW       (GUILD_DIR + "gc_shadow")

#define OBJECT_ID       ("_gc_emblem")
#define GUILD_SUBLOC	("_gc_subloc")

#define IS_MEMBER(x)    (present(OBJECT_ID, (x)))

#endif
