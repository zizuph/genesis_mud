/*
 * f14.c
 * The road to Telberin
 * by Alaron September 24, 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
   set_short("Telan Road");
   set_long("   The road here is picturesque and peaceful. The forest "+
	    "sprawls out along the west side of the road, pushing "+
	    "back away from the road as it flows to the north and "+
	    "northwest. Looking east over a dark green, grassy plain, "+
	    "you can see the rocky coastline continue its course "+
	    "heading northeast along the edge of the overgrown fields. Off "+
	    "to the southwest, peering around the edges of the trees, you "+
	    "can see the cliffs bordering an ocean inlet. The sound of "+
	    "waves crashing up against rock can be heard even from "+
	    "this distance. The road continues north as the wood and "+
	    "coastline wander away from the path, leaving in their wake "+
	    "rolling hills of green and overgrown plains. Southeast "+
	    "through the trees you manage to make out the faint glimmer "+
	    "of sunlight shining against softly rippling water.\n\n");

   add_item(({"road","rocks", "pebbles"}),
	    "The road here is picturesque and beatiful. In contrast with "+
	    "the dark, damp dirt road which leads away toward the coast "+
	    "southwest from here, the dirt is dry, light-colored and "+
	    "sandy. Large rocks and pebbles line the road, providing "+
	    "a soft, crunching noise with each step.\n");

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

   add_item( ({"hills of green", "green hills", "hill", "hills"}),
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

   add_item( ({"southwest", "trees", "cliffs", "inlet", "ocean inlet"}),
	    "Peering off to the southwest, looking through and around "+
	    "the trees there, you can make out some of the cliffs "+
	    "which border the ocean inlet far below their peaks. The sound "+
	    "of water crashing up against the rock is still very audible "+
	    "from here.\n");

   add_item( ({"west", "wood", "forest"}),
	    "The wood bordering the road on the west diverges from the "+
	    "road and continues its flowing course to the northwest. The "+
	    "sounds of forest animals can occasionally be heard coming "+
	    "from behind the dense forest rim.\n");

   add_item( ({"southeast", "sunlight", "glimmer", "glint", "water"}),
	    "Peering through the trees to the southeast, you notice "+
	    "a faint glimmer of reflected sunlight on the surface of "+
	    "a body of water. From this distance you can't quite be sure "+
	    "what it is, but it looks like it could be the edge of a lake.\n");
   
   add_item("lake",
	    "You can see the light glinting off the surface of water through "+
	    "the trees to the southeast. You can't quite be sure what the "+
	    "water is, but it looks like it could be a saltwater lake.\n");

   add_exit(OUT_DIR + "f13", "north");
   add_exit(KROAD_DIR + "eroad2", "southwest");
}
