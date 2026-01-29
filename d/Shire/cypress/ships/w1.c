#include "/sys/stdproperties.h"
#include "defs.h"
#pragma save_binary

inherit "/std/room";

create_room() {

  set_short("Off the coast of a large island");
  set_long(break_string("You are surrounded by water in all directions "
			+ "except to the west were you can see "
			+ "Sparkle.\n",75));

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);

  add_exit("/d/Genesis/start/human/town/pier3", "west", 0,1,1);
  add_exit(STAND_DIR + "w2", "east", 0,1,1);

}
