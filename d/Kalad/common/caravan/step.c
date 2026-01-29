#include "default.h"
#include <ss_types.h>

int
step()
{
    if(random(TP->query_skill(SS_AWARENESS)) < 10)
    {
	write("You weren't looking and step in a " +
	  "fresh pile of animal refuse. Better be more " +
	  "careful!\n");
	say(QCTNAME(TP) + " " +
	  "steps in a pile of fresh animal refuse.\n"+
	  "Boy does it stink!\n");
	TP->add_prop(LIVE_I_DIRTY, TP->query_prop(LIVE_I_DIRTY) + 10);
    }
    return 0;
}

load()
{
}
