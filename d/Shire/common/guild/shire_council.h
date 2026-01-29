#define COUNCIL_LOG   "COUNCIL"    /* Filename of the Council logfile */

#define ACTION_NOTHING   0         /* Actions to be taken */
#define ACTION_EXPELL    1
#define ACTION_WARN      2
#define ACTION_SUMMON    3
#define ACTION_RESTORE   4
#define ACTION_ACCEPT    5
#define ACTION_DENY      6
#define ACTION_RESIZE    7
#define ACTION_RELIEVE   8

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

