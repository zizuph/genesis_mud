/* created by Aridor 06/20/93 */

#include "/d/Krynn/common/defs.h"


/* Pathnames used: */
#define PARENT    "/d/Krynn/solamn/"
#define TDIR      PARENT + "splains/"
#define LIV       TDIR + "living/"
#define OBJ       TDIR + "obj/"
#define ROOM      TDIR + "room/"

/* The inherit files for the rooms */
#define OUTSIDE_BASE   ROOM + "outside_room_base"
#define INSIDE_BASE    ROOM + "inside_room_base"

/* Name of this area */
#define AREA_NAME  "Western Solamnian Plains"


/* Connections to the World:
Vingaard Mountains */
#define HCTOWER    PARENT + "hctower/room/entrance"
#define VKEEP      PARENT + "vkeep/bridge"
#define NEWSEA     "/d/Krynn/newsea/newsea16"
#define THIEF      PARENT + "thief/cavern/pass5"
#define DWARFGATE  PARENT + "thief/theiwar/r11"
#define DWARFGATE_OUTSIDE PARENT + "thief/theiwar/outside"
#define KSPUR      PARENT + "hctower/spur/room/entrance"
#define FORD       (PARENT + "eplains/river3")

#define OTHERSIDE  (PARENT + "eplains/rooms/eplain-4-21-V")


/* Other useful defs: */
#define SL              75

#define BAAZ    "/d/Krynn/common/monster/baaz_base"
#define BOZAK   "/d/Krynn/common/monster/bozak_base"
#define KAPAK   "/d/Krynn/common/monster/kapak_base"
#define SIVAK   "/d/Krynn/common/monster/sivak_base"
#define AURAK   "/d/Krynn/common/monster/aurak_base"

#define TABLE   "/d/Krynn/common/rndtables/tblwar"
#define ROOM_AS_TO_KNIGHTS "_room_as_to_knights"
/* Direction to get to Vingaard Keep and the Knight Spur.
 * Contains an array of two elements, [0] will lead you
 * to the keep and [1] will lead to the high clerist tower.
 * 'X' indicates that you have reached the target, use
 * the troopN files in solamn/splains/living to continue
 * then.
 */
