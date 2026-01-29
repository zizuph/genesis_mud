#include "defs.h"

CONSTRUCT_ROOM {

    set_short("The Stone Chamber");
    set_long("The Stone Chamber. This big squared room in the mountain has "+
	     "three exits. Passages going west and east, and an opening in "+
	     "the wall to the south.\n");
    EXIT("sqchambe","west");
    EXIT("lpass1","east");
    EXIT("corr1","south");
}
