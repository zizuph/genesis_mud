#include "/d/Emerald/defs.h"
#include "/d/Emerald/kroad/vamp/vchasm.h"
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>

static varargs int climb_test(object ob, int difficulty = TASK_DIFFICULT)
{
    return (IS_WIZ(ob) || 
        (ob->resolve_task(TASK_DIFFICULT, ({ SKILL_AVG, TS_STR, TS_DEX,
        SS_ACROBAT, SS_CLIMB, SKILL_END })) > 0));
}

void fall_down(object pl, string *rooms)
{
    pl->catch_msg("In an attempt to find another hand-hold, you lose "+
 		  "your grip and are cast down the side of the cliff "+
		  "to the water!!\n\n");
    tell_room(environment(pl),
	      QCTNAME(pl)+" loses "+pl->query_possessive()+" grip!!\n",pl);
    pl->move_living("plummeting into the chasm", 
		    VAMP_AREA_DIR + "fallroom", 1, 0);

    map(rooms, &tell_room( , QCTNAME(pl) + " plummets by you, " +
        "screaming all way way to the bottom of the cavern, landing with " +
        "a splash!.\n", pl));
}
    
