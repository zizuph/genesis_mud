inherit "/std/room";
 
#include "/d/Emerald/defs.h"

object guard;

void
reset_room()
{
    if (guard)
	return;
    guard=clone_object(TCASTLE_DIR + "npc/guard");
    guard->arm_me();
    guard->move_living("into a room", this_object());
    guard=clone_object(TCASTLE_DIR + "npc/guard");
    guard->arm_me();
    guard->move_living("into a room", this_object());
}
 
void
create_room()
{
    set_short("On battlement");
    set_long( "You are standing on the battlement above the "+
	     "drawbridge. Below, you can see a path winding away, "+
	     "and in the moat surrounding the castle, you can see some "+
	     "fish swimming around. The way around the battlement is "+
	     "blocked by debris, so the only possible exit is back down "+
	     "the stairs.\n" );
 
    add_item( ({ "debris", "slabs", "stones", "stone slabs" }),
	       "It is mostly big stone slabs that has "+
	      "loosened from the walls of the battlement. It looks "+
	      "like it happened a long time ago, perhaps in a "+
               "battle.\n");
 
    add_exit(TCASTLE_DIR + "stairs", "down");
 
    set_alarm(1.0, 0.0, reset_room);
}
