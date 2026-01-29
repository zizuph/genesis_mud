/*
 * f13.c
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
    set_long("   The road here is picturesque and peaceful. The west side "+
      "of the road is bordered by an enormous, sprawling forest which "+
      "pushes back away from the road as it flows to the northwest. "+
      "Beyond dark green, grassy plains to the east you can see the "+
      "rocky coastline continue along its course heading northeast along "+
      "the edge of the overgrown fields. Off in the distance to the south "+
      "and a bit southwest you can peer through the trees to see bits "+
      "and pieces of some large cliffs. The road continues "+
      "north as the wood and coastline wander away from the path, "+
      "leaving in their wake rolling hills of green and overgrown "+
      "plains. Far to the southeast, peering through the trees you "+
      "can barely make out the faint glimmer of sunlight glinting "+
      "off of the surface of softly rippling water.\n\n");

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

    add_item( ({"trees", "cliffs"}),
      "Peering off to the southwest, looking through and around "+
      "the trees there, you can make out some of the cliffs "+
      "which border the ocean inlet far below their peaks. The sound "+
      "of water crashing up against can barely be heard from this "+
      "point.\n");

    add_item( ({"west", "wood", "forest"}),
      "The wood bordering the road on the west diverges from the "+
      "road and continues its flowing course to the northwest.\n");

    add_item( ({"southeast", "sunlight", "glimmer", "glint", "water"}),
      "Peering through the trees to the southeast, you notice "+
      "a faint glimmer of reflected sunlight on the surface of "+
      "a body of water. From this distance you can't quite be sure "+
      "what it is, but it looks like it could be the edge of a lake.\n");

    add_item("lake",
      "You can see the light glinting off the surface of water through "+
      "the trees to the southeast. You can't quite be sure what the "+
      "water is, but it looks like it could be a saltwater lake.\n");

    add_exit(OUT_DIR + "f12", "north");
    add_exit(OUT_DIR + "f14", "south");
}
