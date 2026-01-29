#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("Tower of Domains");
  set_long(break_string(
   "This mighty tower is as old as time itself. It was built at the "
  +"creation of the world, as to connect the far reaching places and "
  +"making them accessible by simply walking through an archway. "
   +"The levels of the tower cross time and space, bringing the lands "
   +"together in some arcane way. "
  +"The tower is formed of an ancient multi-coloured swirling "
  +"rock, not yet cooled from the primal days of the world. "
   +"An enormous staircase leads up and down from here."
  +"\n", 70));

	add_exit(THIS_DIR + "dom_a1", "up");
	add_exit(THIS_DIR + "dom_b1", "down");
	add_exit(THIS_DIR + "park_n", "south");
	add_default_exits();
	change_prop(ROOM_I_LIGHT, 10);
	load_board("domains");
}

reset_room()
{
    tell_room(this_object(), "The tower rumbles\n");
}
