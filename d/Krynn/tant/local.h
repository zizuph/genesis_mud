#ifndef TANT_DEF
#define TANT_DEF

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>

#define PARENT  "/d/Krynn/"
#define TDIR	PARENT + "tant/"
#define TSTD	TDIR + "std/"
#define TNPC    TDIR + "npc/"
#define TOBJ	TDIR + "obj/"
#define TARM    TDIR + "arm/"
#define TWEP    TDIR + "weap/"
#define TLOG    TDIR + "log/"
#define TROOM   TDIR + "room/"
#define KSTD    PARENT + "std/"

/* inherit files */
#define INROOM   TSTD + "inside_base"
#define OUTROOM  TSTD + "outside_base"

/* places to visit */
#define DEFAULT      0
#define MOUNTAIN     1
#define ROAD         2
#define STREET       3
#define FOREST       4
#define VALLEY       5
#define CASTLE       6

/* Connections to the world */
#define C_TUNNEL	TDIR + "level1/tunnel1"
#define S_FOREST        PARENT + "solace/forest/hill3"
#define W_ROAD          PARENT + "wild/east7"

/* Some other definitions used for the doors */
#define K_CITY1  	19856370
#define K_CITY2  	19856371
#define K_CITY13 	19856372
#define K_CITY14 	19856373
#define K_CITY20 	19856374
#define K_CITY23 	19856375
#define SALAMIC  	19856376

/* city11.c has got a wizstone in it */

/* Some helpful coding definitions */

#define AI   add_item
#define ACI  add_cmd_item
#define AE   add_exit

#define RESPONSIBLE ({"teth"})

#endif TANT_DEF

