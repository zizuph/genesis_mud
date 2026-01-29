#include "valley.h"

create_valley() {
    set_short("Entrance of an open valley!");
    set_long("You are standing at the entrance of an open valley! It seems "+
	     "almost ill-placed amongst the bare rocks and steep slopes. A "+
	     "path continues some yards to the east, where it turns north. "+
	     "A small crack leads west. ");
    add_item(({"valley","entrance","path","crack"}),
	     "What about investigating the area?\n");
    add_item(({"rock","rocks","slope","slopes"}),
	     "Yes. The scenery is rocky..\n");
    WEST("cleft");
    EAST("junction");
}

init() {
    ::init();
    add_action("my_enter","enter");
}
		    
my_enter(string arg) {
  if(!arg) {
    notify_fail("Enter what?\n");
    return 0;
  }
  if(arg == "valley") {
    this_player()->move_living("enters",STAND_DIR+"junction");
    return 1;
  }
}
