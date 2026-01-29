#include "defs.h"

CONSTRUCT_ROOM {
    set_short("King Durin's guest room");
    set_long("This is King Durin's guest room. Once upon a time it must have "+
	     "been a nice place, but due to the trolls invasion of the "+
	     "mines, the drapery and the pictures have been grabbed, and "+
	     "the floor got full of filth. You can go north to a grand hall, "+
	     "or go through an opening in the floor, probably due to a rock-"+
	     "slide, down to a quite bigger room.\n");
    add_item(({"room","drapery","picture","pictures","floor"}),
	     "You see nothing special.");
    EXIT("durhall","north");
    EXIT("sqchambe","down");
}
