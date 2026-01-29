#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("A gallery overlooking a large room");
    set_long(
	"You are standing upon a gallery overlooking a large dark room.\n"+
	"A stone bridge leads northwards to another gallery. You might "+
	"also want to climb down some steep stone stairs here.\n");
    DOWN("longnar2");
    NORTH("shgall1");
    add_item(({"bridge","stone bridge"}),
	"It looks quite solid, so you shouldn't have problems crossing it.");
    add_item("room",
	"It is too dark to see anything special.");
}
