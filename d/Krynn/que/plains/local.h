/* include the Krynn .h file */
#include "/d/Krynn/common/defs.h"

/* This defines the pathnames of this dir */
#define QUE_DIR        KRYNN_DIR + "que/"
#define TDIR           QUE_DIR + "plains/"

/*special rooms*/
#define CAMP           QUE_DIR + "camp/"
#define CAMP_V_EAST    CAMP + "camp02"
#define CAMP_V_WEST    CAMP + "camp04"
#define CAMP_V_SOUTH   CAMP + "camp03"
#define CAMP_V_NORTH   CAMP + "camp01"

#define PAPER          TDIR + "obj/paper"
#define PAPER_CONTENT  TDIR + "obj/paper.txt"

#define DRACONIAN_GUARD     TDIR + "living/bozak.c"

#ifndef WAR_AREA_NEWPORT
#define WAR_AREA_NEWPORT   "Newports Area"
#endif
#ifndef WAR_AREA_SOLACE
#define WAR_AREA_SOLACE    "Solace Area"
#endif
#ifndef WAR_AREA_CENTRAL_ABANASINIA
#define WAR_AREA_CENTRAL_ABANASINIA    "Central Abanasinian Plains"
#endif
#ifndef WAR_AREA_NORTH_ABANASINIA
#define WAR_AREA_NORTH_ABANASINIA      "North Abanasinian Plains"
#endif

/* connections to the world */
#define QUE_SHU_V_SOUTH     QUE_DIR + "shu/room/vill4"
#define QUE_SHU_V_NORTH     QUE_DIR + "shu/room/vill1"
#define QUE_SHU_V_EAST      QUE_DIR + "shu/room/vill3"
#define QUE_SHU_V_WEST      QUE_DIR + "shu/room/vill2"
#define SOLACE_VILLAGE      "/d/Krynn/wild/plains/meadow"
#define GATEWAY_VILLAGE     "/d/Krynn/solace/road/gateway"
#define XAK_CITY            "/d/Krynn/xak/trail"
#define NEWPORTS_VILLAGE    QUE_DIR + "newports/bridge_end"
