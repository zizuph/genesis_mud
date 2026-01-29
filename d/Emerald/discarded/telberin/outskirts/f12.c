/*
 * f12.c
 * The road to Telberin
 * by Alaron October 4, 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
   set_short("Telan Road");
   set_long("   Telan road rounds a gradual, wide curve here. The road "+
	    "continues on to the northwest and to the south. Examining "+
	    "the west side of the road, you can't help but admire the "+
	    "sheer size of the immense forest. The incredible green "+
	    "treeline pushes back away from the road heading further "+
	    "northwest, leaving a span of rolling green hills and "+
	    "fields between the woodline and the road. The east side of the "+
	    "road is equally impressive; bordered by dark green hills and "+
	    "plains which eventually reach the coastline. The coastline "+
	    "continues northeast and southwest, pushing further away from the "+
	    "road as it continues to the north.\n\n");

   add_item(({"road","rocks", "pebbles"}),
	    "The road here is picturesque and beatiful. The dirt is "+
	    "dry, light-colored and sandy. Large rocks and pebbles "+
	    "line the road, providing a soft, crunching noise with each "+
	    "step.\n");

   add_item( ({"east", "plain", "grassy plain", "green plain",
	       "dark green plain", "green plains", "plains",
	       "overgrown plains"}),
	    "Looking east you see a dark green, grassy plain. It "+
	    "seems to roll over small hills and dips in the landscape "+
	    "almost like a smooth ocean wave. Beyond the plain, past "+
	    "several sandy patches which look like they might be part "+
	    "of a path (but you can't quite be sure from this distance), "+
	    "you can see the rocky coastline continue its coarse diverging "+
	    "from the road and heading northeast.\n");

   add_item( ({"hills of green", "green hills", "hill", "hills",
	       "rolling hills", "rolling green hills"}),
	    "The rolling hills of green appear gradually as the "+
	    "forest rolls away from the road on the west side and the "+
	    "coastline wanders northeast away from the road. The hills "+
	    "are a wide variety, some small, some very large, preventing "+
	    "a view of anything behind them. They are covered with "+
	    "flourishing, dark green grass.\n");
   
   add_item( ({"patches", "sandy patches", "path"}),
	    "The sandy patches which are barely visible beyond the rolling "+
	    "hills of the green plain look like they might belong to a "+
	    "small path, but you can't quite be sure from this distance "+
	    "with the large, green hills preventing a good view.\n");

   add_item( ({"west", "wood", "forest", "woodline"}),
	    "The wood bordering the road on the west diverges and "+
	    "continues its flowing course to the northwest.\n");

   add_exit(OUT_DIR + "f8", "northwest");
   add_exit(OUT_DIR + "f13", "south");
}
