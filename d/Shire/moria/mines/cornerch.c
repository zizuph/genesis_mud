#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Little corner chamber");
    set_long(
	"This is a little corner chamber. There has been an avalanche "+
	"here blocking the western exit, but there is a round opening "+
	"to the south and a smaller one to the east.\n");
    add_item("avalanche",
        "It seems like a heavy avalanche has dropped into this room.\n");
    add_neg("climb", "[up] [the] 'up' / 'avalanche'",
        "Nah, it seems to be of no use. Try the southern or the eastern exit.\n");
    EXIT("boring","east");
    EXIT("smhollow","south");
}
