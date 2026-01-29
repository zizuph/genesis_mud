#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Dead-end");
    set_long("You have arrived at a dead end.\n");
    SOUTH("bottom");
    add_item(({"end","dead-end", "dead end"}),
	"Not especially interesting, but that's a fact of life.\n"+
	"Dead ends do exist.\n");
}
