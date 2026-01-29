#include "defs.h"
#include "/sys/terrain.h"

CONSTRUCT_ROOM {

    set_short("You are in the vast corridor");
    set_long("You are in the vast corridor. " +
//           "It is damp and cold here, and a hole in the floor leads down. "+
             "There is an opening in the north wall to a stone-chamber.\n");
    add_item("corridor",
	     "It seems to be the main east-west passage of the Mines.");
    add_item(({"wall","walls"}), "You see nothing special.");
    add_item("hole","Which one, the floor hole or the wall hole?");
    add_item(({"floor hole","floor"}),"The room under is not made yet..");
    add_item("wall hole","It seems to lead into a stone-chamber.");
    EXIT("corridor", "west");
    EXIT("stonechb", "north");
    EXIT("corr2", "east");
 /* EXIT("arched_passage", "down"); */
}

/* --- until made --- 
init() {
  ::init();
    add_action("my_down","down");
}

my_down() {
  write("The room under is unfortunately not made yet. Try elsewhere, ok?\n");
  return 1;
}
   --- end until --- */
