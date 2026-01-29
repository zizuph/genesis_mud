/*
 * Fourth pier - entrance to the village
 * TAPAKAH, 06/2006
 */

#include "../../pier/pier.h"
#include "../../village/village.h"

inherit PIER_BASE;

void
create_khalakhor_room()
{
  ::create_pier();

  set_long(query_long() + "You are standing next to the entrance to a "  +
	   "small village bustling with activity to the east. To the "   +
	   "north steep hills rise and to the east the landing extends " +
	   ".\n"
	   );
  set_daenbraigh_sign_destination("Daenbraigh");
  add_exit("pier2","west",0);
  add_exit(V_ROOM + "we_1","east",0);
  add_item(({"settlement","village"}),
	   "A small village of crude wooden huts, with goblins running " +
	   "around. You notice some kind of military patrols as well.\n");
}

int *
query_local_coords()
{
  return ({-8,0});
}
