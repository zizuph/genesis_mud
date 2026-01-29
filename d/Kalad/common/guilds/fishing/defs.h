 /*****************************************************************************
* /d/Kalad/common/guilds/fishing
*
* Define File for Fishing Craft
*
* Created May 2018, Greneth
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/defs.h"

 /*****************************************************************************
* Paths
 *****************************************************************************/
#define F_MAIN       "/d/Kalad/common/guilds/fishing/"
#define F_FISH       F_MAIN + "fish/"
#define F_BAIT       F_MAIN + "bait/"
#define F_NPC        F_MAIN + "npc/"
#define F_OBJ        F_MAIN + "obj/"
#define F_ROD        F_MAIN + "rod/"
#define F_ROOM       F_MAIN + "room/"
#define F_STD        F_MAIN + "std/"
#define F_SPIER      F_STD +  "std_southpier"

 /*****************************************************************************
* Room Check
 *****************************************************************************/
#define LIVE_I_CAN_FISH			"_live_i_can_fish"

 /******************************************************************************
*  Exits
 *****************************************************************************/
#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
   "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])

 /******************************************************************************
*  Short Desc - Kalad Pier
 *****************************************************************************/
#define KP_NW "On the northwest side of the pier"
#define KP_N  "On the north side of the pier"
#define KP_NE "On the northeast side of the pier"
#define KP_E  "On the east side of the pier"
#define KP_SE "On the southeast side of the pier"
#define KP_S  "On the south side of the pier"
#define KP_SW "On the southwest side of the pier"
#define KP_W  "On the west side of the pier"
#define KP_M  "In the middle of the pier"

 /*****************************************************************************
* Skills
 *****************************************************************************/
 
#define SS_FISHING 11500