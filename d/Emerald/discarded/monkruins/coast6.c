/*
 * COAST6.c
 * Coastal Path outside the Monk Ruins in Emerald.
 * - Alaron December 1996
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>

void
create_room()
{
  set_short("Dark, foggy path");
  set_long("   A thick mist hangs over the area, distorting the trees "+
	   "and wood in blue-gray shadows. The road here is more of a "+
	   "well-trod path, ancient ruts in the ground displaying where "+
	   "wagons once travelled these ways. The road continues into the "+
	   "mist to the west and heads toward a cluster of tall, building-"+
	   "shaped shadows looming beyond the mist. Further south you notice "+
	   "a dark, strange shape lurking on the road. You can't quite make "+
	   "out the details of it from here, however.\n\n");

   
  add_prop(ROOM_I_INSIDE, 0);

  add_item( ({"mist", "thick mist", "fog"}),
	   "The thick mist hangs over the area, casting a gloomy, moist "+
	   "haze over everything and cloaking the surrounding wood "+
	   "in dark bluish-gray shadows.\n");

  add_item( ({"trees", "wood", "woods", "forest"}),
	   "The trees surrounding the path are obscured by the thick "+
	   "layer of mist and fog which hangs heavily over the entire "+
	   "area, blanketing as far as the eye can see with a dark gloom "+
	   "and moisture.\n");

  add_item( ({"road", "path", "ruts", "ground", "ancient ruts",
	      "down"}),
	   "The road here is fairly well-defined by well-trod dit amid "+
	   "thick green growth on either side of the road. Occasionally "+
	   "you notice an ancient, deep rut in the road where wagons "+
	   "once travelled here daily in ages long gone.\n");

  add_item( ({"shadows", "building-shaped shadows", "buildings",
	      "tall buildings", "tall shadows"}),
	   "The shadows lurking off in the distance to the south "+
	   "seem to resemble buildings. However, pieces of the buildings "+
	   "seem to be missing, with jagged, incomplete walls. It looks "+
	   "as though these could be the ruins of old buildings.\n");

  add_item( ({"shape", "dark shape", "dark strange shape", "stange shape"}),
	   "There is something in the road to the south, but the mist "+
	   "distorts it too much to resemble anything. It is a large, "+
	   "dark shape which runs the width of the road. You also notice "+
	   "two more faint, taller shapes on either side of the road.\n");

  add_exit(MONKRUIN_DIR + "coast5", "west");
  add_exit(MONKRUIN_DIR + "coast7", "south");
   
}
