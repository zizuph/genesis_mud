/*
*
*    Created by Vencar 13/08/2003
*
*    Copyright by Peter Bech Lund (Vencar)
*    08/2003
*
*    Header file pointing to directories Thanks
*    to Aridor for the designpattern (nicked from
*    file /d/Krynn/solamn/vin_mount/local.h
*
*    Primarily for the caravan code.
*/

#include "/d/Krynn/common/defs.h"

#define DEBUG_WIZ       "vencar"
#define DEBUG_MSG(x)   find_player(DEBUG_WIZ)->catch_msg("Debug msg: " + x + ".\n");

/* Pathnames used: */
#define VBASE      "/w/vencar/"
#define PARENT    "/w/vencar/"
#define TDIR      VBASE + "caravan/"
#define LIB       TDIR + "lib/"
#define NPC       TDIR + "npc/"
#define OBJ       TDIR + "obj/"
#define ROOM      TDIR + "room/"
#define WAGON     TDIR + "wagon/"
#define WEP       TDIR + "weapon/"
#define ARM       TDIR + "armour/"

/* Our base files for this directory */
#define ROOM_BASE ROOM + "room_base";

/* Connections to the World:
Back to the workroom */
#define VENCARWORK      PARENT + "workroom"



