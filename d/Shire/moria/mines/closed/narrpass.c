#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Narrow passage");
    set_long(
	"You are in a narrow passage. It winds into the mountain in the north "+
	"and opens in the east.\n");

    add_item("floor",
	"The floor is made of hard-tramped sand.\n");
    NORTH("maritime");
    EAST("westhall");
}
