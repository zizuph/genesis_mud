/* created by Aridor 06/20/93 */
/* December 26th 2006, Fixed bug introduced on file change November 27th 2006.
 * The Griffon landing was changed to the wrong landing, icewall, which
 * has no return possibility for the players.
 *
 * If changing this file, add like with any other file reason for change!
 * -- Navarre
 */

#include "/d/Krynn/common/defs.h"


/* Pathnames used: */
#define PARENT    "/d/Krynn/solamn/"
#define TDIR      PARENT + "vin_mount/"
#define LIV       TDIR + "living/"
#define OBJ       TDIR + "obj/"
#define ROOM      TDIR + "room/"
#define CAVE      TDIR + "cave/"

/* Our base files for this directory */
#define ROOM_BASE ROOM + "room_base";
#define CAVE_BASE CAVE + "room_base";

#define HOBGOBLIN_KNIFE PARENT + "splains/obj/bdagger"
#define HOBGOBLIN_CLUB  PARENT + "splains/obj/bmace"

#define TABLE     "/d/Krynn/common/rndtables/tblmountains"

/* Connections to the World:
Vingaard Mountains */
#define PALAN      PARENT + "palanthas/nobles/ser8"
/* Thief area */
#define THIEF_CAVERN  PARENT + "thief/cavern/hall2"
/* High Clerist Tower */
#define HCTOWER   PARENT + "hctower/room/backex"
/* Icewall */
/* Old Landing to Icewall #define GRIFFON_LANDING "/d/Krynn/icewall/outside/griffon/landing1" */
#define GRIFFON_LANDING "/d/Krynn/neraka/griffon/landing1"
/* Knight's Spur */
#define KSPUR    PARENT + "hctower/spur/room/backex"
/* Dragon quest */
#define DRAGON   TDIR + "dragon_quest/room/dq_room19"

/* Other useful defs: */
#define SL              75	// Obsolete, but required for compatibility.

/*the npc base*/

#define HOB                         LIV + "vmhobgoblin_base"
#define LIVE_I_ATTACKED_SOL_HOBS    "_live_i_attacked_sol_hobs"

/* Code aid */

#define SHORT(x) set_short(x)
#define LONG(x) set_long(x)
#define EXIT(w,x,y,z) add_exit(w,x,y,z)
#define ITEM(x,y) add_item(x,y)
#define RITEM(x) remove_item(x)
#define CMD(x,y,z) add_cmd_item(x,y,z)
#define ACT(x,y) add_act(x,y)
#define RTELL(x) add_tell(x)
