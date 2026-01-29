/*
 * File		:	/d/Genesis/new/start/start.h
 * Creator	:	Gnadnar/Teth
 * Copyright	:
 * Date		:	3-Oct-1998
 * Purpose	:	local defines for start locs
 * Related Files:
 * Comments	:
 * TODO		:
 * Modifications:
 */


#ifndef _START_DEFS
#define _START_DEFS

/*
 * Directories:
 */
/* Do NOT use the "START" definition. Use "START_DIR" ! */
#define START_DIR       "/d/Genesis/new/start/"
#define	START		"/d/Genesis/new/start/"
#define BOARD_DIR       (START_DIR + "boards/")



/* 
 * Macros:
 */
#define TP               this_player()
#define TI               this_interactive()
#define TO               this_object()
#define QVB              query_verb()
#define BS(x)            break_string((x), 75)
#define BSN(x)           (BS(x) + "\n")
#define NF(x)            notify_fail(x)
#define NF0(x)           { NF(x); return 0; }
#define NFN(x)           NF(BSN(x))
#define NFN0(x)          { NFN(x); return 0; }
#define ENV              environment
#define CAP(x)           capitalize(x)
#define LOW(x)           lower_case(x)
#define WRITE(x)         write(BSN(x))

#define POSSESSIVE(x)    ((x)->query_possessive())
#define OBJECTIVE(x)     ((x)->query_objective())
#define PRONOUN(x)       ((x)->query_pronoun())

#endif /* _START_DEFS */
