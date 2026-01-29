/*
 * Base path file for the path to Hammerhands.
 * TAPAKAH, 10/2005
 */

#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../hhands/hhands.h"

void
create_hhands_path()
{
  ::create_khalakhor_room();

  set_short("A path inside Foraois Deanach");
  set_long("You are walking on a path through Foraois Deanach, the last "+
	   "forest of Khalakhor before the northern tundra and the waste "+
	   "beyond it. Peaceful lands of humans and elves are far to the "+
	   "south, and even dwarven mines at the hub of the continent are "+
	   "very distant. The elves and the humans lay ambushes in it, "+
	   "trying to prevent the advance of the goblins to south and you "+
	   "see the pines and the firs marked with arrow and blade scars. "+
	   "Yet the path seems well-trodden, with almost no broken branches "+
	   "on it.\n");
  add_item(({"trees","firs","pines","pine","tree","fir","forest"}),
	   "Mighty trees compete in reaching the sun, growing thickly. "+
	   "Some of them bear marks of arrow heads, sword blades and club "+
	   "thumps.\n");
  add_item(({"path","trail"}),
	   "The path is obviously well-kept and cleaned regularly.\n");
  add_item(({"branch","branches"}),
	   "Quite a few branches are broken, but they are all piled on "+
	   "the sides of the path, and almost none of them on it.\n");

  add_prop(ROOM_I_INSIDE,0);
  set_terrain(TERRAIN_CONIFEROUS);
  
}
