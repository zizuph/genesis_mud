#include "defs.h"

/* #define XXX_QUEST 0(Change nr for each quest) */
/* Example */
/* #define A_QUEST 0 */
/* #define B_QUEST 1 */
/* #define C_QUEST 2 */

/* use LOG_QUESTS!=0 to log quests */

#define LOG_QUESTS 1
#define QUESTLOG "/d/Genesis/start/dwarf/log/quests"

#define QDONE(apa) (this_player()->test_bit("Genesis", 2, apa))
#define QSET(bepa)  this_player()->set_bit(2,bepa)
#define QLOG(cepa) if(LOG_QUESTS) write_file(QUESTLOG, extract(ctime(time()), \
		  4,15)+" "+cepa+" "+capitalize(TP->query_real_name()) + "\n")


#define HELPKING  0

