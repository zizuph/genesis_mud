/* Definitions for the bury bones quest
 *   Cirion, 040996
 */
#ifndef __BURY_BONES_QUEST__
#define __BURY_BONES_QUEST__

#define BBLOG		"/d/Avenir/log/quest/bury_bones"
#define LOG_THIS(x)	write_file(BBLOG, ctime(time())+" "+x+"\n")

#define GROUP         0
#define BIT           17

#define EXP           50000
#define ALIGNMENT     200
#define PRESTIGE      2000

#define SPOKENTO      "_Avenir_burybones_spokento"
#define BONES_ID      "_avenir_burybones_bones"
#define LOGBOOK_ID    "_avenir_burybones_logbook"
#define RING_ID       "_avenir_captains_ring"
#define HOLE_ID       "_avenir_burybones_hole"

#define VERBOSE

#endif  __BURY_BONES_QUEST__
