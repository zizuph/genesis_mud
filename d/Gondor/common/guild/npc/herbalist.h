/*
 * /d/Gondor/common/guild/npc/herbalist.h
 *
 * Modification history:
 * 6-june-1998, gnandar:
 *	this file originally contained skill code.  ick. i moved
 *	all that into herbalist.c, moved #defines from herbalist.c,
 *	changed defs to use standard paths from ~gondor/defs.h, etc.
 */

#ifndef _HERBALIST_DEFINITIONS
#define _HERBALIST_DEFINITIONS

#define	HERB_LIST \
({ \
    "angurth", "astaldo", "athelas", "attanar", "basil", \
    "black potato", "blueberry", "blung", "caraway", "catnip", \
    "chervil", "clove", "curugwath", "dill", "fennel", "foxglove", \
    "frostheal", "fungiarbo", "garlic", "ginger", "green onion", \
    "handasse", "hemlock", "holly berry", "huckleberry", "laurel", \
    "lissuin", "lothore", "madwort", "marjoram", "mint", "morgurth", \
    "myrtleberry", "oregano", "parsley", "pawnrose", "red potato", \
    "redweed", "rosemary", "saffron", "sage", "savory", "seregon", \
    "sumac", "suranie", "tarragon", "thyme", "tuo", "tyelka", \
    "ungolestel", \
})

#define	LOTHMIR_S_HERB		"_lothmir_s_herb"
#define	LOTHMIR_S_HERB_SOLD	"_lothmir_s_herb_sold"
#define	LOTHMIR_I_INTROD	"_lothmir_i_introd"

#define RECRUITHALL     (RANGER_DIR + "recruithall")
#define	HERBAL_SAVE 	(RANGER_DIR + "npc/herbalist_herbs") 
#define	HERB_BOOK	(LIBRARY_DIR + "books/herb-guide.txt")
#define RANGER_HERBS_I_BOUGHT "_ranger_herbs_i_bought"
#define	LOG_REPORT_FILE	"herbs"
#define	LOG_BUG		"herbs.bug"
#define	LOG_VIOLATIONS	"violations"

#define	LOG_PURCHASE	"herbs_purchase"
/* different cases for LOG_PURCHASE: */
#define LOG_TOO_MANY            0
#define	LOG_RESTRICTED		1
#define	LOG_OUT_OF_STOCK	2
#define	LOG_CANT_AFFORD		3
#define	LOG_BOUGHT_IT		4

#define MAX_ALLOW_BUY   30
#define	MAX_XFER	20	/* buy/sell <= 20 at a time */
#define	MAX_XFER_WORD	"twenty"
#define	MAX_INV	50	/* if have > 50, only pay half price */
#define	NUM		sizeof(MONEY_TYPES)

/* indices into herb data */
#define	H_FILE	0
#define	H_COUNT	1
#define	H_VALUE	2

#endif /* _HERBALIST_DEFINITIONS */
