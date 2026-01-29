/*
**   ARGOS - Metro - On the chariot transport from depot to docks
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
 
#define  START_ROOM  DEPOT_ROOM
#define  DEST_ROOM   DOCKS_ROOM
#define  DESTINATION AT_DOCKS
#define  START_LOC AT_DEPOT
 
#include "chariot.inc"
