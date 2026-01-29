/* Coded by Ckrik, July 1998 
 * Cliff face, the entrance to the Order of the Dragon.
 * 
 */

inherit "/d/Earthsea/std/room";
#pragma no_clone
#pragma strict_types

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#include "/sys/filter_funs.h"
#include "/sys/composite.h"
#include "/sys/macros.h"

void
create_earthsea_room()
{
  ::create_earthsea_room();
  set_short("A cliff face.");
  set_long("The path abruptly ends in a cliff of rock. You are above " +
	   "the blue mist that covers the area below you. Looking " +
	   "from this vantage point the mist seems to " +
	   "stretch everywhere. Ancient buildings rest on the plateau " +
	   "on top of cliff. There is a stair carved into the " +
	   "cliff rock rising up to the plateau.\n");
  add_item(({"cliff", "rock"}),
	   "The cliff is made of solid rock, weathered by ages of " +
	   "sea winds and blue mist. Several large words are carved " +
	   "into the cliff.  It reads: 'The Order of the Dragon'.\n");
  add_item(("stair"),
	   "It leads up the cliff to the plateau.\n");

  reset_room();
  add_exit("/d/Earthsea/oranea/rooms/mountain_path19", "northeast");
  add_exit("monk guild", "up", "@@block@@");
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_IS, 1);
  ::reset_room();
}

int
block()
{
  this_player()->catch_msg("The stairs have been blocked.\n");
  return 1;
}
