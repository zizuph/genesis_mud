/*
 * Second pier - Internal Khalakhor line.
 * TAPAKAH, 06/2006
 */

#include "../../pier/pier.h"

inherit PIER_BASE;

void
create_khalakhor_room()
{
  ::create_pier();

  set_long(query_long() + "This pier is the center of the landing. "     +
	   "To the west and south the landing continues. To the "        +
	   "north steep hills rise and to the east you notice some kind "+
	   "of a settlement.\n"
	   );
  set_daenbraigh_sign_destination("Tabor Sogh");
  add_exit("pier1","west",0);
  add_exit("pier3","south",0);
  add_exit("pier4","east",0);
  add_item(({"settlement","village"}),
	   "Some kind of village can be seen to the east.\n");
}

int *
query_local_coords()
{
  return ({-9,0});
}
