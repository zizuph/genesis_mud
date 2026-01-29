/* include the Krynn defines */
#include "/d/Krynn/common/defs.h"

/* Standard room definetions */
#define CREATE "create_newport_room"
#define RESET  "reset_newport_room"

/* Warfare names */
#ifndef WAR_AREA_NEWPORT
#define WAR_AREA_NEWPORT   "Newports Area"
#endif


/* Special defines for the Newport rooms */

#define QUE_DIR             KRYNN_DIR + "que/"
#define TDIR                QUE_DIR + "newports/"
#define PLAINS              QUE_DIR + "plains/"
#define LIV                 TDIR + "living/"
#define OBJ                 TDIR + "obj/"

/* base file for the outdoor rooms */
#define PLAINS_BASE         PLAINS + "plains_base";
#define BASE_FILE         	TDIR + "newport_base"

/* special rooms*/
#define NEWPORTS_TO_PLAINS  PLAINS + "newports_link"
#define PIER                TDIR + "pier"
#define PIER2             TDIR + "ship/pier"
#define SHIPLINE_OTHER_PIER SOLAMN_DIR + "palan/ship3/pier"
#define SHIPLINE_OTHER_PIER3  "/d/Krynn/solace/ship/pier"
#define PIER3                 TDIR + "pier3"
#define PAX                 "/d/Krynn/pax/road/"

/* Note: the ship arriving at PIER is defined in
 *       /d/Krynn/solamn/palan/ship4/
 */

/* NPCs */
#define GUARD            LIV + "mercenary"

/*special include files*/
#define LEVEL_ME         "/d/Krynn/solamn/splains/living/level_me.h"
#define ARM_ME           "/d/Krynn/solamn/splains/living/arm_me.h"
