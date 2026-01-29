/*
 * /d/Gondor/common/guild/npc/herbalist.h
 *
 * Modification history:
 * 6-june-1998, gnandar:
 *  this file originally contained skill code.  ick. i moved
 *  all that into herbalist.c, moved #defines from herbalist.c,
 *  changed defs to use standard paths from ~gondor/defs.h, etc.
 * 5 May 2004: Gwyneth:
 *  Removed several unused definitions
 */

#ifndef _HERBALIST_DEFINITIONS
#define _HERBALIST_DEFINITIONS

#define HERB_LIST ({ \
    "angurth", "astaldo", "athelas", "attanar", "basil", \
    "black potato", "blueberry", "blung", "caraway", "catnip", \
    "chervil", "clove", "curugwath", "dill", "fennel", "foxglove", \
    "frostheal", "fungiarbo", "garlic", "ginger", "green onion", \
    "handasse", "hemlock", "holly berry", "huckleberry", "laurel", \
    "lissuin", "lothore", "madwort", "marjoram", "mint", "morgurth", \
    "myrtleberry", "oregano", "parsley", "pawnrose", "red potato", \
    "redweed", "rosemary", "saffron", "sage", "savory", "seregon", \
    "sumac", "suranie", "tarragon", "thyme", "tuo", "tyelka", \
    "ungolestel", })

#define RANGER_HERBS ({ \
    "athelas", "lothore", "redweed", "suranie", "curugwath", "alfirin", \
    "ungolestel", "foxglove", "red_pepper", "handasse", "morgurth" })

#define LOTHMIR_S_HERB        "_lothmir_s_herb"
#define LOTHMIR_S_HERB_SOLD   "_lothmir_s_herb_sold"
#define LOTHMIR_I_INTROD      "_lothmir_i_introd"

#define HERBAL_SAVE           (RANGERS_NPC + "herbalist_herbs") 
#define RANGER_HERBS_I_BOUGHT "_ranger_herbs_i_bought"
#define LOG_BUG               "herbs.bug_newranger"

#define MAX_ALLOW_BUY         30
#define MAX_XFER              20  /* buy/sell <= 20 at a time */
#define MAX_XFER_WORD         "twenty"
#define MAX_INV               50  /* if have > 50, only pay half price */
#define NUM                   sizeof(MONEY_TYPES)

/* indices into herb data */
#define H_FILE                0
#define H_COUNT               1
#define H_VALUE               2

#endif /* _HERBALIST_DEFINITIONS */
