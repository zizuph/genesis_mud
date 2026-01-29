/*
 * /d/Gondor/open/fireplace/fireplace.h
 * included by /d/Gondor/open/fireplace/fireplace.c and rooms that inherit it
 * 
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * this file should be included last.
 * it #define's a lot of macros, many of which are already defined
 * in the defs.h of various domains.  since it checks before each
 * #define, if it comes last, things will work fine.  if you include
 * your domain files after this, things are likely to break.
 */

#ifndef	FIREPLACE_DEFS
#define	FIREPLACE_DEFS

#include	<stdproperties.h>	/* for ROOM_I_LIGHT	*/

/* misc macros copied from ~Gondor/defs.h */
#ifndef TP
#define TP               this_player()
#endif

#ifndef TO
#define TO               this_object()
#endif

#ifndef BS
#define BS(x)            break_string((x), 75)
#endif

#ifndef BSN
#define BSN(x)           (BS(x) + "\n")
#endif

#ifndef NF
#define NF(x)            notify_fail(x)
#endif

#ifndef NF0
#define NF0(x)           { NF(x); return 0; }
#endif

#ifndef NFN
#define NFN(x)           NF(BSN(x))
#endif

#ifndef NFN0
#define NFN0(x)          { NFN(x); return 0; }
#endif

#ifndef ENV
#define ENV              environment
#endif

#ifndef CAP
#define CAP(x)           capitalize(x)
#endif

#ifndef LOW
#define LOW(x)           lower_case(x)
#endif

#ifndef WRITE
#define WRITE(x)         write(BSN(x))
#endif

#ifndef FIX_EUID
#define FIX_EUID         { setuid(); seteuid(getuid()); }
#endif


#ifndef SAY
#define SAY(x)                           \
    say( ({ BSN(TP->query_name() + (x)),  \
          BSN("The " + TP->query_nonmet_name() + (x)), \
          BSN("Someone" + (x)) }) )
#endif

/* fireplace states */
#define FIRE_ASHES	0
#define FIRE_UNLIT_WOOD	1
#define FIRE_BURNING    2

/* check light before doing say ... */
#define	IF_LIGHT_SAY(r, s) \
	if ( (r)->query_prop(ROOM_I_LIGHT) > 0 ) { SAY(s); }

/* how long (in seconds) a single piece of firewood burns */
#define	BURN_TIME	300.0
#define	BURN_TIME_I	300	/* sometimes we don't need float */

/* how long (in seconds) between noise/light effects */
#define	EFFECTS_TIME	60.0

/* # of pieces of wood per reset */
#define	WOOD_AMT	5

/* path to firewood */
#define	FIREWOOD	"/d/Gondor/open/fireplace/firewood"

/* macro to log errors */
#ifndef ERR_LOG_FIRE
#define	ERR_LOG_FIRE(x)	log_file("fireplace", \
	"ERR "+ctime(time())+" "+file_name(this_object())+"\nERR\t"+x);
#endif

#endif /* FIREPLACE_DEFS */
