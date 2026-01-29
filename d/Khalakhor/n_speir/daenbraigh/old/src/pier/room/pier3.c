/*
 * Third pier - Sanction connection.
 * TAPAKAH, 06/2006
 */

#include "../../pier/pier.h"

inherit PIER_BASE;

void
create_khalakhor_room()
{
  ::create_pier();

  set_long(query_long() + "This pier is the southern end of the landing. " +
	   "To the west, south and east you can see nothing but water. "   +
	   "To the north the pier continues, and further to it you notice "+
	   "some hills.\n"
	   );
  set_daenbraigh_sign_destination("Sanction");
  add_exit("pier2","north",0);
}

int *
query_local_coords()
{
  return ({-9,1});
}
