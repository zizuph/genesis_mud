#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("In a eeling passage");
    set_long(
	"This passage is in fact so narrow, that you have to eel "+
	"yourself through it. To the west there is a shaft and to "+
	"the east the passage opens a little.\n");
    EXIT("smhollow", "east");
    EXIT("deep/shaft1", "west");
}
