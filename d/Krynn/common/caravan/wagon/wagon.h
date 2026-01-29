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
#define PARENT      "/w/vencar/"
#define TDIR        PARENT + "caravan/"
#define LIV         TDIR + "living/"
#define OBJ         TDIR + "obj/"
#define ROOM        TDIR + "room/"
#define WAGON       TDIR + "wagon/"
#define WAGON_ROOM  WAGON + "room/"

/* our rooms */
#define WAGON_ROOM_LEFT          WAGON_ROOM + "left"
#define WAGON_ROOM_RIGHT         WAGON_ROOM + "right"
#define WAGON_ROOM_FRONT         WAGON_ROOM + "front"
#define WAGON_ROOM_BACK          WAGON_ROOM + "back"
#define WAGON_ROOM_ARMOURED      WAGON + "armouredroom"

/* Our base files for this directory */
#define ROOM_BASE                WAGON_ROOM + "room_base";
#define WAGON_ROOM_INDOOR        WAGON_ROOM + "wagonroom.c"

/* Connections to the World:
Back to the workroom */
#define VENCARWORK      PARENT + "workroom"

#define ID_BACK_ROOM    1
#define ID_FRONT_ROOM   2
#define ID_LEFT_ROOM    3
#define ID_RIGHT_ROOM   4

#define MOVE_FORWARD_FAT    15
#define MOVE_BACK_FAT       2

/* Room definitions, */

#define R_LEFT              "left"
#define R_RIGHT             "right"
#define R_FRONT             "front"
#define R_BACK              "back"
#define R_WAGON             "wagon"


/*definition of the mapping structure */

#define MAP_FILE            0
#define M_OBJECT            1

/*definitions of the burn mapping structure */
#define ROOM_MSG            0
#define WAGON_SHORT         1
#define WAGON_LONG          2
#define IGNITION_MSG        3


/* default definition of the rooms */

#define DEFAULT_LEFT        (( { WAGON_ROOM_LEFT, 0 } ))
#define DEFAULT_RIGHT       (( { WAGON_ROOM_RIGHT, 0 } ))
#define DEFAULT_FRONT       (( { WAGON_ROOM_FRONT, 0 } ))
#define DEFAULT_BACK        (( { WAGON_ROOM_BACK, 0 } ))
#define DEFAULT_WAGON       (( { WAGON_ROOM_ARMOURED, 0 } ))

/* Other wagon definitions */
#define CAGE_KEY            "7110004"
#define ARM_KEY             "7110005"
#define CHEST_KEY           "7110006"
#define STDDOOR "/std/door"

/* wagon types to the conestoga wagon type */
#define F_WAGON_CONESTOGA WAGON + "w_conestoga"

#define WAGON_FLETCHER      1
#define WAGON_ALCHEMIST     2
#define WAGON_WEAPONRY      3
#define WAGON_ARMOURY       4
#define WAGON_INN           5
#define WAGON_BUTCHER       6
#define WAGON_MERCHANT      21
#define WAGON_TREASURY      22
#define WAGON_FARMER        23
#define WAGON_SMITH         24
#define WAGON_PRISON        25
#define WAGON_D_OFFICER     27
#define WAGON_K_OFFICER     28
#define WAGON_D_TROOPS      30
#define WAGON_K_TROOPS      31
#define WAGON_B_TROOPS      32
#define NONSPECIFIC         99

/* all the other wagons */
#define F_WAGON_MERCHANT  WAGON + "w_merchant"
#define F_WAGON_TREASURY  WAGON + "armoured"
#define F_WAGON_FARMER    WAGON + "w_cattle"
#define F_WAGON_SMITH     WAGON + "w_smith"
#define F_WAGON_PRISON    WAGON + "w_prison"
#define F_WAGON_TROOP     WAGON + "w_trooptransport"
#define F_WAGON_KOFFICER  WAGON + "w_kofficer"
#define F_WAGON_DOFFICER  WAGON + "w_dofficer"
#define F_WAGON_DWARF     WAGON + "w_dwarf"
#define F_WAGON_ALCHEMIST WAGON + "w_alchemist"

#define STANDARD_EXA_ITEM_BURNING  "There is not much time to look around while the wagon is burning!\n"
#define STANDARD_EXA_ITEM_OUTSIDE_BURNING  "The wagon is burning!\n"
