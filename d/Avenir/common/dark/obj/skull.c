// Skull with no particular usage so far.
// Let the players find out what to do with it, I have no idea.
// Made by Boriska, Dec 1994

#include <macros.h>
#include <stdproperties.h>

inherit "/std/object";

create_object()
{
  set_name ("skull");
  set_short ("skull");
  set_long ("A skull of some humanoid creature. You catch a dim reflection\n" +
	    "of yourself looking at its surface polished by time.\n");
  add_prop (OBJ_I_WEIGHT, 2000);
  add_prop (OBJ_I_VOLUME, 1000);
  add_prop (OBJ_I_VALUE, 30);
}
