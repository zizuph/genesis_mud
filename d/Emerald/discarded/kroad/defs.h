/*
 * DEFS.h
 * Telroad header file - useful definitions.
 */

#include "/d/Emerald/defs.h"

#define PATH "/d/Emerald/kroad/"
#define KPATH "/d/Emerald/kroad/path/"
#define NFOREST "/d/Emerald/forest/north/"
#define TNPC PATH + "npc/"
#define TOBJ PATH + "obj/"


#define OUTSIDE add_prop(ROOM_I_INSIDE,0)
#define DARK    add_prop(ROOM_I_LIGHT,-1)
#define LIGHT(x) add_prop(ROOM_I_LIGHT, x);

#define BASEROAD PATH + "fbaseroad"
#define OUT_DIR "/d/Emerald/telberin/outskirts/"
#define SFOREST "/d/Emerald/forest/south/"
