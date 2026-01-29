#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("Bottom of Shaft");
    set_long(
	"You have arrived at the bottom of a deep shaft!\n"+
   "There are small exits to the north, south, and west.\n");
    add_exit(THIS_DIR+"shaft1", "up", "@@chk_rope@@");
    EXIT("deadend", "north");
    EXIT("shroomnw", "south");
    EXIT("sheast", "west");
}

object
link_room(string lfile, mixed dest, int pos)
{
    object ob;
    ob = clone_object(THIS_DIR+"shaftcor");
    ob -> setup_pos(pos);
    return ob;
}

int
chk_rope()
{
    if((THIS_DIR+"shaft1")->query_rope_length()>200) {
	(THIS_DIR+"shaft1")->add_climber(TP);
	return -10;
    }
    write("The shaft is to steep to climb. You'll need a rope from the "+
	    "top of the shaft to manage this.\n");
    return 1;
}
