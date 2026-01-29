/*
**   ARGOS - Metro - On the chariot transport from docks to depot
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   9/9/95     Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "chariot.h"
 
#define  START_ROOM  DOCKS_ROOM
#define  DEST_ROOM   DEPOT_ROOM
#define  DESTINATION AT_DEPOT
#define  START_LOC AT_DOCKS
 
#include "chariot.inc"
