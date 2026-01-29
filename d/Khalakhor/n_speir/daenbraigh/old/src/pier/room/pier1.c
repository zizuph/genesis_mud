/*
 * First pier - Mordor connection.
 * TAPAKAH, 06/2006
 */

#include "../../pier/pier.h"

inherit PIER_BASE;

void
create_khalakhor_room()
{
  ::create_pier();

  set_long(query_long() + "This pier is the western end of the landing. " +
	   "To the west and south you can see nothing but water. To the " +
	   "north steep hills rise and to the east the pier continues.\n"
	   );
  set_daenbraigh_sign_destination("Fords of Poros");
  add_exit("pier2","east",0);
}

int *
query_local_coords()
{
  return ({-10,0});
}
