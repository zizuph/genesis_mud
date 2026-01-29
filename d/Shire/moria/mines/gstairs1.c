#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Some wide and gentle stairs up to the west");
    set_long("Some wide and gentle stairs up to the west. To the east it "+
	     "leads into some kind of terrace. Some sparse foot-steps shows "+
	     "on the stairs.\n");
    add_item(({"foot-steps","steps","stair","stairs","footsteps"}),
	     "It looks like a person has carried something heavy up here.");
    EXIT("terrace","east");
    EXIT("dome","west");
}
