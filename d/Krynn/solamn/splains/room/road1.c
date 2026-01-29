/* created by Aridor 06/21/93 */

#include "../local.h"

inherit OUTSIDE_BASE;

void
area_conquered(string newarmy, string oldarmy)
{
    "/d/Krynn/solamn/hctower/spur/room/entrance"->area_conquered(newarmy,oldarmy);
}

void
create_splains_room()
{
    set_short("On the road");
    set_long("You are on a road through the Plains of Solamnia. To your " +
	     "northwest you can see the High Clerist Tower, protecting the " +
	     "entrance to a valley into the Vingaard Mountains which are " +
	     "spreading out to the north and southwest. To the east and " +
	     "south you can see nothing but grass all the way to the " +
	     "horizon.\n");

    add_exit(KSPUR, "northwest", 0);
    add_exit(ROOM + "road1a","southeast",0);
    add_invis_exit(ROOM + "plain1","east",0,3);
    add_invis_exit(ROOM + "plain4","south",0,3);
    add_invis_exit(ROOM + "mount4","southwest",0,3);
    add_invis_exit(ROOM + "mount1","northeast",0,3);

    add_item(({"road","gravel","gravel road"}),BS("It's just a gravel road.",SL)); 
    add_item(({"tower","high clerist tower","high tower","clerist tower",
	     "fortress","base"}),
	     BS("It is a very tall white tower, almost poking the clouds. "
		+"It is very impressive and the base of the it is like a fortress"
		+" blocking the entrance to the valley beyond.",SL));
    add_item(({"mountains","vingaard mountains","peak","high peak"}),
	     BS("These mountains are "
		+ "very high indeed. To north-northwest of you, you can make out "
		+ "an especially high peak.",SL));
    add_item(({"valley","vale"}),BS("All you can make out from here is "
				    + "that there must something like a valley behind the tower.",SL));
}

