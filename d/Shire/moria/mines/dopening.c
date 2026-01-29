#include "defs.h"

CONSTRUCT_ROOM {
    set_short("A door opening to the south");
    set_long(
	"You are standing in front of an opened door to the south. "+
	"You might also go to the east through an opening to "+
	"a big hall.\n");
    EXIT("boring","south");
    EXIT("big_hall","east");
}
