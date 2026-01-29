#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Gallery of Queen's Ballroom");
    set_long("The enourmous Queen's Ballroom lies in front of you. You are "+
	     "standing on a gallery overlooking the remains of the once "+
	     "prominent ballroom. It looks empty and deserted now. The "+
	     "ballroom extends to the north, south and west. There is an "+
	     "exit from the gallery to the east and some stairs leading "+
	     "down to the ballroom.\n");
    add_item(({"gallery","podium"}),
	     "This is the podium overlooking the area.");
    add_item("ballroom","Why not go down there?");
    EAST("losttrck");
    DOWN("ballr");
}

		  
		    
