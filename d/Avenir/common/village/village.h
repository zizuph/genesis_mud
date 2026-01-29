// file name:        /d/Avenir/common/village/village.h
// creator(s):       Lilith, Oct '98
// revisions:        Lucius, Oct 2008: Stripped & cleaned.
// purpose:          Put defines and includes here that are needed
//                   in all the village area files
// note:
// bug(s):
// to-do:
#ifndef __AVENIR_VILLAGE__
#define __AVENIR_VILLAGE__

#include <stdproperties.h>

#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/defs.h"

/* Area defines and connections */
/* VILL is defined in paths.h   */
#define V_OBJ		(VILL + "obj/")
#define V_NPC		(VILL + "npc/")
#define MERC		(VILL + "merc/")

#define MERC_BASE	(MERC + "base")
#define BASE_MERCHANT	(V_NPC + "base_merch")


#endif /* __AVENIR_VILLAGE__ */
