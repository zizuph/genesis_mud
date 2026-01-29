/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

/*object goblin;

void
reset_road_room()
{
    if (goblin)
      return;
    goblin = clone_object(GOBLIN);
    goblin->move_living("xxx",TO);
}
*/

void
create_road_room()
{
    set_short("On a road before the dark forests of Throtl");
    set_long("You are on a road leading east and west. West, the " +
      "Plains of Solamnia stretch out before you. To the east, " +
      "you can see a forest. A border watch is standing here, " +
      "guarding the road.\n");
    add_item(({"road","ancient road"}),
      "This is an ancient road, a bit overgrown with grass, but " +
      "usable.\n");
    add_item(({"plains","plains of solamnia","bushes"}),
      "The plains stretch out to the west from here, all you can " +
      "see is the light green of the bushes and the grass.\n");
    add_item(({"trees", "forest", "forests", "woods", "throtl"}),
      "A bit to the east, a dense forest can be seen. It looks gloomy, " +
      "and a sense of danger lies in the air. The road disappears " +
      "into the forest.\n");
    add_item(({"border watch","watch","borderwatch","guard","border guard"}),
      "These are two goblins stationed here to prevent anyone from " +
      "continuing east on the road and from entering the forest.\n");


    if (LOAD_ERR(ROAD_OBJECT))
    {
	write("Bug! please report immediately...\n");
	return;
    }
    add_exit("", "west", "@@enter_map:" + ROAD_OBJECT + "|T@@",3,0);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|T@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|T@@",6,1);
    add_exit(THROTL_LINK,"east","@@closed@@",3,0);
}

int
closed()
{
    write("The goblin border guard says: No enter!\n");
    return 1;
}

