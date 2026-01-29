#include "/d/Shire/common/defs.h"
#include "shire_council.h"

/* Shire Guild defines: */
#define SHIRE_PIPE    (HIN_DIR + "pipe")
#define SHIRE_NEWPIPE (HIN_DIR + "newpipe")
#define SHIRE_SOUL    (HIN_DIR + "shire_soul_cmd")
#define SHIRE_SHADOW  (HIN_DIR + "shire_shadow")
#define SHIRE_COUNCIL (HIN_DIR + "shire_council")

#define COUNCIL_LOG   "COUNCIL"    /* Filename of the Council logfile */

#define ACTION_NOTHING   0         /* Actions to be taken */
#define ACTION_EXPELL    1
#define ACTION_WARN      2
#define ACTION_SUMMON    3
#define ACTION_RESTORE   4
#define ACTION_ACCEPT    5
#define ACTION_DENY      6
#define ACTION_RESIZE    7

/*
 * How much do we need to accept a proposal?
 * VOTES_NEEDED[SHIRE_COUNCIL->sizeof_council()] will give the answer.
 * Make the array larger if the maximum members of the council expands.
 * Up to 15 members now supported.
 */
#define VOTES_NEEDED ({ 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10 })

/*
 * How much members should the Council have? The Council itself may
 * decide between these two boundaries.
 */
#define MIN_MEMBERS 3
#define MAX_MEMBERS 10

