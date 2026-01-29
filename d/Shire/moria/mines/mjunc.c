#include "defs.h"

// void start_captain();

CONSTRUCT_ROOM
{
    set_short("Main junction");
    set_long("This must once have been the main junction in the Mines of "+
      "Moria. There are exits everywhere. Westwards there is a "+
      "rough opening which leads to the top of a wide stairway. "+
      "To the north and south there are wide openings. To the east, "+
      "there is a small round hole, which may be 6 feet (2 meters) "+
      "wide, but it is still small when compared to the other exits. "+
      "In the floor, just near your feet, a steep shaft leads down "+
      "into the deep. Small steps have been made out of the rock, but "+
      "it looks dangerous all the same. A steep spiral staircase "+
      "rises from a corner of the room.\n");
    add_item( ({"junction","moria","exits","opening","stairway","floor",
	"hole","shaft","staircase" }), "Read the text, adventurer!");

    NORTH("npass1");
    WEST("stair2");		 
    EAST("litt");
    SOUTH("cavern");
    UP("spirals");
    DOWN("deep/shaft1");
    reset_room();

    add_prop(ROOM_I_NO_CLEANUP, 1);
//    set_alarm(120.0, 0.0, &start_captain());

    /*    set_deep(1); set_pos(350, 0); set_rect(100, 100, 100); */
}

void
start_captain()
{
    string msg = (THIS_DIR+"orc_lair")->start_captain();
    message(msg+"\n");
}


void reset_room()
{
}
