#ifndef __DARK_DOM__
#define __DARK_DOM__

#include "../defs.h"

#define ARM(X)  (DARK_DOM + "arm/"  + X)
#define NPC(X)  (DARK_DOM + "npc/"  + X)
#define OBJ(X)  (DARK_DOM + "obj/"  + X)
#define WEP(X)  (DARK_DOM + "wep/"  + X)
#define STD(X)  (DARK_DOM + "std/"  + X)
#define ROOM(X) (DARK_DOM + "room/" + X)

/* Directory reference Kabal. */
#define KABAL(X)   ("/d/Kalad/common/wild/pass/" + X)
#define KABALU(X)  KABAL("underdark/" + X)

/* For a Kabal Quest.  Given by ShadowGloom. */
#define SW_SOLARA  KABAL("wep/sword_of_solara")

#endif  __DARK_DOM__
