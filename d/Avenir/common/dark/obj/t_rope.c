// Piece of rope which is carried by goblin digger for unknown reason
// Made by Boriska, Feb 28 1995
// Used by dark/mon/t_goblin

inherit "/std/rope";

#include "stdproperties.h"

void
create_rope()
{
  set_name("rope");
  set_short("piece of rope");
  set_pshort("pieces of rope");
  set_long("There's nothing unusual about that piece of rope.\n" +
	   "It might tie things together or even help you to climb\n" +
	   "somewhere.\n");
  // todo: actually implement these tiable things or climbable clefts :)
  add_prop(OBJ_I_VALUE, 50);
}
  
