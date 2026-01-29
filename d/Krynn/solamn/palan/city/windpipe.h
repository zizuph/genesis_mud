/* created by Aridor 12/14/93 */
/* the include file for windpipes */

#include "../local.h"



/* Connections to the World:
Palanthas & Neraka */
#define IN_WALL      ROOM + "wall"
#define NERAKA_EXIT  "/d/Krynn/neraka/hole23"


/* Other useful defs: */
#define PLAYER_S_BLOWN_DIR   "_player_s_blown_dir"
    /* contains the (general) direction a player is blown to
     * maybe "east" even if it is temporarily going up ;)
     * every room should know what to do with the possible
     * directions though. 
     */
