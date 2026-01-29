#ifndef __UNION_QUEST_BITS__
#define __UNION_QUEST_BITS__

#include <math.h>

#define GUILD_GROUP	3 /*   The bit group for the Union         */
#define QUEST_BIT	0 /* Player has passed the entrance quest  */

/* The quest number for a particular player */
#define QNUM(x)		(NAME_TO_RANDOM((x)->query_name(), 104, 6) + 1)
#define QUEST_OB        "_Union_i_qob_num"
#define QUEST_OB_NAME   "_Union_quest_ob"

#endif
