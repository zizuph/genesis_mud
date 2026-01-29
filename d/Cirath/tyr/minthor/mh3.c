inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Path");
  set_long("You are inside the gate of the Minthor's estate. The path "
	+"extends northward towards the actual house, east down a "
	+"marble sidewalk into some beautiful plants, and west into a "
	+"small loading area.\n"); 
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item(({"path"}),"The path narrows as it enters the compound, but "
	+"still is at least 10 feet wide. It leads northward to the "
	+"house, and southward back towards the entrance.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
  add_item(({"house"}),"The house is a large noble manor. It stands "
	+"at least 50 feet tall, and 75 feet long. It has beautiful "
	+"carvings and statues all over and around it.\n");
  add_item(({"statues","carvings"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  add_item("sidewalk","It is a shining marble sidewalk that disappears "
	+"into the large variety of plants on the eastern side of the "
	+"house.\n");
  add_item(({"plant","plants"}),"The plants are all blooming and "
	+"brilliantly colored. They look to be watered regularly, and "
	+"probably end up with more water than the slaves here.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh4", "east", 0);
  add_exit(TZ_MINTHOR + "mh2", "south", 0);
  add_exit(TZ_MINTHOR + "mh11", "north", "@@door");
  add_exit(TZ_MINTHOR + "mh8", "west", 0);
}
door()
{
	write("You step from under the hot Athasian sun "
	+"into the confines of the house.\n");
	return 0;
}
