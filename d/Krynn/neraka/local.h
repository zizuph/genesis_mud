#include "/d/Krynn/common/defs.h"
#include <money.h>

#define TDIR	NERAKA_DIR
#define MON	TDIR + "monster/"
#define OBJ	TDIR + "obj/"

#define DRACOS  COMMON_DIR + "rndtables/tbldraconians"

/* inherit files */
#define TANTALLON_INSIDE   "/d/Krynn/neraka/std/inside_base"
#define TANTALLON_OUTSIDE  "/d/Krynn/neraka/std/outside_base"


/* Connections to the world */
#define C_TUNNEL	TDIR + "level1/tunnel1"
#define ROOM_TO_SOLACE  TDIR + "dragon/landing2"

/* Some other definitions used for the doors and break_string() */
#define SL 		75
#define K_CITY1  	19856370
#define K_CITY2  	19856371
#define K_CITY13 	19856372
#define K_CITY14 	19856373
#define K_CITY20 	19856374
#define K_CITY23 	19856375
#define SALAMIC  	19856376

/* city11.c has got a wizstone in it */

/* The coin and gem drops defined here for draconians spawned
   in Tantallon - 25 Oct 2015 Arman */

#define BAAZ_COIN1 MONEY_MAKE_SC(random(13))
#define BAAZ_COIN2 MONEY_MAKE_GC(random(2))
#define KAPAK_COIN1 MONEY_MAKE_SC(random(5))
#define KAPAK_COIN2 MONEY_MAKE_GC(2 + random(4))
#define BOZAK_COIN1 MONEY_MAKE_GC(4 + random(4))
