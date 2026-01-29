/*
 * /d/Gondor/met_defs.h
 *
 * These defines are used to ensure that people get a nice description
 * without having to juggle with QCTNAME macros and break_string. If you
 * try to follow these macros, don't let the brackets get you for you
 * must remember that you can never use a variable in a macro without
 * it being bracketed.
 *
 * /Mercade
 *
 * Revision history:
 *	5 Feb 98 Gnadnar
 * 	something has changed somewhere ... this file hadn't changed since '94,
 *	but suddenly we're getting "previously defined" errors for SAY.
 *	for now, i've added an #undef before our #define
 *      29 Aug 98 Gnadnar
 *      add SAYBUTWIZ
 */
 
#ifndef GONDORIAN_MET_DEFINITIONS
#define GONDORIAN_MET_DEFINITIONS
 
#define G_TP          (this_player())
#define G_BSN(x)      (break_string((x), 74) + "\n")
#define G_METNAME(x)  ((x)->query_name())
#define G_TNONMET(x)  ("the " + (x)->query_nonmet_name())
#define G_CTNONMET(x) ("The " + (x)->query_nonmet_name())
 

#undef SAY
#define SAY(x)                           \
    say( ({ BSN(G_METNAME(G_TP) + (x)),  \
          BSN(G_CTNONMET(G_TP) + (x)), \
          BSN("Someone" + (x)) }) )

#undef SAYBB
#define SAYBB(x)                         \
    say( ({ BSN(G_METNAME(G_TP) + (x)),  \
	    BSN(G_CTNONMET(G_TP) + (x)), \
	    "" }) )

/* a version of SAY that will reveal stealthy players, but
 * not invisible wizards
 */
#undef	SAYBUTWIZ
#define	SAYBUTWIZ(x) \
	if (!G_TP->query_wiz_level()) { SAY(x); } \
	else { SAYBB(x); }

 
#define LSAY(x, y)                            \
    say( ({ BSN((x) + G_METNAME(G_TP) + (y)), \
	    BSN((x) + G_TNONMET(G_TP) + (y)), \
	    BSN((x) + "someone" + (y)) }) )
#define LSAYBB(x, y)                          \
    say( ({ BSN((x) + G_METNAME(G_TP) + (y)), \
	    BSN((x) + G_TNONMET(G_TP) + (y)), \
	    "" }) )
 
#define CATCH_MSG(x, o)                     \
    catch_msg( ({ BSN(G_METNAME(o) + (x)),  \
		  BSN(G_CTNONMET(o) + (x)), \
		  BSN("Someone" + (x)) }), (o))
#define CATCH_MSGBB(x, o)                   \
    catch_msg( ({ BSN(G_METNAME(o) + (x)),  \
		  BSN(G_CTNONMET(o) + (x)), \
		  "" }), (o))
 
#define LCATCH_MSG(x, y, o)                      \
    catch_msg( ({ BSN((x) + G_METNAME(o) + (y)), \
		  BSN((x) + G_TNONMET(o) + (y)), \
		  BSN((x) + "someone" + (y)) }), (o))
#define LCATCH_MSGBB(x, y, o)                    \
    catch_msg( ({ BSN((x) + G_METNAME(o) + (y)), \
		  BSN((x) + G_TNONMET(o) + (y)), \
		  "" }), (o))
 
#define TELL_ROOM(r, o, x, n)                   \
    tell_room((r), ({ BSN(G_METNAME(o) + (x)),  \
		      BSN(G_CTNONMET(o) + (x)), \
		      BSN("Someone" + (x)) }), (n), (o))
#define TELL_ROOMBB(r, o, x, n)                 \
    tell_room((r), ({ BSN(G_METNAME(o) + (x)),  \
		      BSN(G_CTNONMET(o) + (x)), \
		      "" }), (n), (o))
 
#define LTELL_ROOM(r, o, x, y, n)                    \
    tell_room((r), ({ BSN((x) + G_METNAME(o) + (y)), \
		      BSN((x) + G_TNONMET(o) + (y)), \
		      BSN((x) + "someone" + (y)) }), (n), (o))
#define LTELL_ROOMBB(r, o, x, y, n)                  \
    tell_room((r), ({ BSN((x) + G_METNAME(o) + (y)), \
		      BSN((x) + G_TNONMET(o) + (y)), \
		      "" }), (n), (o))
 
/* Lets clean up after ourselves.
 * Sure, nice idea, except it doesn't work.
 * It just makes the defines using these defines unusable.
 * SO DO _NOT_ BURN YOUR BRIDGES BEFORE YOU COME TO THEM!!!!!
 */
 
/* To guard against redefinition, do not add anything beyond this line.
 */
#endif GONDORIAN_MET_DEFINITIONS
