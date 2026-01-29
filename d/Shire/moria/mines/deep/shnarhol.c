#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("A small hole");
    set_long(
	"You are in a small and dirty hole in the end of a crawling-passage. "+
	"The passage leads south.\n");
    SOUTH("crawling");
}
