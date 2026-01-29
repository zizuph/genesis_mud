#include "defs.h"

void start_up();

CONSTRUCT_ROOM 
{
    set_short("Top of stone stairs");
    set_long("You are standing at the top of some stairs made of stone. The "+
	     "stairs are about 200 steps long, and lead down to the the "+
	     "doors at the lake. There's an arched passage leading east. You "+
	     "also notice a square opening to the north here, probably being "+
	     "the Gate Room of Durin's Doors.\n");
    add_item(({"steps","stairs","stair"}),"You see nothing special.");
    set_alarm(60.0, 0.0, &start_up());
    DOWN("stair1");
    EAST("mjunc");
    NORTH("gate_room");
}

void
start_up()
{
    int i, r;
    string msg;
    CONTROL->start_loop();
    message("[stair2] Starting loop.\n");
//    (THIS_DIR+"mjunc")->short();
    for (i=0, r=random(4)+4; i<r; i++)
    {
	// msg = (THIS_DIR+"orc_lair")->create_soldier();
    msg = " debug ";
	message("[stair2] " + msg);
    }			     
}
