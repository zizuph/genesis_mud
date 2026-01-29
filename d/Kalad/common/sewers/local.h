 /******************************************************************************
*  Standard include files
 *****************************************************************************/
#include "/d/Kalad/defs.h"

 /******************************************************************************
*  Paths
 *****************************************************************************/
#define PARENT                   "/d/Kalad/common/sewers/"
#define LOG_DIR                  PARENT + "logs/"
#define STDIR                    PARENT + "std/"
#define RDIR                     PARENT + "rooms/"
#define ARM                      PARENT + "arm/"
#define WEP                      PARENT + "wep/"
#define OBJ                      PARENT + "obj/"
#define LIV                      PARENT + "npc/"
#define SPELLS                   PARENT + "spells/"
#define FIRST_FLOOR              RDIR   + "first_floor/"
#define SEWERS_STD               STDIR  + "sewers_std"

 /******************************************************************************
*  Exits
 *****************************************************************************/
#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
   "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])
	 
 /******************************************************************************
*  Short Desc - First Floor
 *****************************************************************************/
#define B_NW "On the northwest side of the beach"
#define B_N  "On the north side of the beach"
#define B_NE "On the northeast side of the beach"
#define B_E  "On the east side of the beach"
#define B_SE "On the southeast side of the beach"
#define B_S  "On the south side of the beach"
#define B_SW "On the southwest side of the beach"
#define B_W  "On the west side of the beach"
#define B_M  "In the middle of the beach"