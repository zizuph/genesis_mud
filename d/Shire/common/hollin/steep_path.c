#include "outroom.h"

create_outroom() {
    set_short("You are on a steep mountain path with an opening to the east.");
    set_long("You are on a steep mountain path with an opening to the east. "+
	     "There is a steep passage leading down, but to the east you "+
	     "can see undergrowth stretching towards a hidden cave.");
    add_item(({"path","passage","undergrowth","cave"}),
	     "You see nothing special.\n");
    DOWN("m_path1");
    EAST("crevice");
}

