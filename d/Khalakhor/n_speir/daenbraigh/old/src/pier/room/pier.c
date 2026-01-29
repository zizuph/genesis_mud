/*
 * Basic pier room
 * TAPAKAH, 06/2006
 */

#include <stdproperties.h>

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrain.h"

#include "../../daenbraigh.h"
#include "../../pier/pier.h"

inherit "/d/Khalakhor/std/room";

string *sign_item = ({"sign",
			"battered sign",
			"wooden sign",
			"battered wooden sign"});

string query_daenbraigh_sign_basetext();
void   set_daenbraigh_sign_destination(string destination);

void
create_pier()
{
  ::create_khalakhor_room();

  set_short("A pier outside Daenbraigh");
  set_long("You are standing on a thin patch of land west of the village " +
	   "of Daenbraigh. Most of it looks like piles of sand and dirt "  +
	   "heaved up next to the sea to provide a landing site for "      + 
	   "transporting forces between Daenbraigh and other parts of "    +
	   "Khalakhor and beyond. "
	   );
  add_prop(ROOM_I_INSIDE,0);
  set_terrain(TERRAIN_SALTBEACH);
  add_item(({"hill","hills"}),
	   "Steep hills prevent any progress to the north.\n");
  add_item(({"water","sea","ocean"}),
	   "This body of water is the Currain Ocean washing the western " +
	   "shores of the continent of Khalakhor.\n");
}

string
query_daenbraigh_sign_basetext()
{
  return "A battered wooden sign reads: ";
}

void
set_daenbraigh_sign_destination(string destination)
{
  add_item(sign_item,
	   query_daenbraigh_sign_basetext() + "'" + destination + "'.\n");
  add_cmd_item(sign_item, "read",
	   query_daenbraigh_sign_basetext() + "'" + destination + "'.\n");
  set_long(query_long() + "A battered wooden sign has been erected here.\n");
}
