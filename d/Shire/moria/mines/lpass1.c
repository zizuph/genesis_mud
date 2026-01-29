#include "defs.h"

CONSTRUCT_ROOM {

    set_short("West end of a low passage");
    set_long("West end of a low passage. The passage is so low, that it is "+
	     "bound to be dwarf-made.\n");
    EXIT("stonechb", "west");
    EXIT("lpass2", "east");
}
