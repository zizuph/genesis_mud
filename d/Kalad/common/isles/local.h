 /******************************************************************************
*  Standard include files
 *****************************************************************************/
#include "/d/Kalad/defs.h"

 /******************************************************************************
*  Paths
 *****************************************************************************/
#define PARENT                   "/d/Kalad/common/isles/"
#define LOG_DIR                  PARENT + "logs/"
#define STDIR                    PARENT + "std/"
#define RDIR                     PARENT + "rooms/"
#define ARM                      PARENT + "arm/"
#define WEP                      PARENT + "wep/"
#define OBJ                      PARENT + "obj/"
#define LIV                      PARENT + "npc/"
#define SPELLS                   PARENT + "spells/"
#define BEAST_BEACH              RDIR   + "beast_beach/"
#define BEAST_BEACH_STD          STDIR  + "beast_beach_std"
#define BEAST_BEACH_PATH_STD     STDIR  + "beast_beach_path_std"
#define BEAST_OCEAN_STD          STDIR  + "beast_ocean_std"

 /******************************************************************************
*  Exits
 *****************************************************************************/
#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
   "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])
	
#define BEAST_BEACH_FOUND_EXIT "_beast_beach_found_exit"
	 
 /******************************************************************************
*  Short Desc - Beach
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

 /******************************************************************************
*  Short Desc - Upper Beach
 *****************************************************************************/
#define B_P "On a path inside a crevice"

 /******************************************************************************
*  Short Desc - Ocean
 *****************************************************************************/
#define O_NW "Swimming in the northwest part of the ocean"
#define O_N  "Swimming in the north part of the ocean"
#define O_NE "Swimming in the northeast part of the ocean"
#define O_E  "Swimming in the east part of the ocean"
#define O_SE "Swimming in the southeast part of the ocean"
#define O_S  "Swimming in the south part of the ocean"
#define O_SW "Swimming in the southwest part of the ocean"
#define O_W  "Swimming in the west part of ocean"
#define O_M  "Swimming in the middle of the ocean"

 /******************************************************************************
*  Short Desc - Below Ocean
 *****************************************************************************/
#define O_B "Swimming below the surface of the ocean"

