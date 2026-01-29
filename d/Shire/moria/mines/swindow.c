#include "defs.h"

CONSTRUCT_ROOM {
    set_short("South of a window");
    set_long("You are on top of a very long spiral staircase. This room has "+
	     "got to be on the higher levels of the mountain. The air is "+
	     "fresh here and in the north wall there is a window! Maybe it "+
	     "is an exit out of the mountain!!\n");
    add_item(({"window","exit"}), 
	     "Maybe you should go closer north to examine it!");
    add_item(({"stairs","staircase"}), 
	     "I wouldn't jump there, but I think it will hold.");
    NORTH("window");
    DOWN("spirals");
}

init() {
  ::init();
    add_action("my_jump","jump");
}

my_jump(arg) {
  if (!arg) {
    notify_fail("B O I N G !!!\n");
    return 0;
  }
  if (arg == "stairs" || arg == "staircase") {
    write("B O I N G !!! You land safely.\n");
    return 1;
  }
}
