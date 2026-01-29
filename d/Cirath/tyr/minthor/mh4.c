inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Path");
  set_long("You are on the beginning of a marble sidewalk which heads "
	+"only east and west. To the west it heads back to the main "
	+"path, while to the east it heads into a lush garden. All "
	+"around you are flowers, and bushes which absorb water almost "
	+"as quickly as the accursed sun. This seems to be such a "
	+"waste of water, not to mention the cost to operate such an "
	+"extreme form of beauty.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item(({"path"}),"The path lies to the west from here.\n");
  add_item(({"house"}),"The house is a large noble manor. It stands "
	+"at least 50 feet tall, and 75 feet long. It has beautiful "
	+"carvings and statues all over and around it.\n");
  add_item(({"statues","carvings"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  add_item("sidewalk","The sidewalk is an amazing marble creation "
	+"that stretches to the east.\n");
add_item(({"plant","plants","flower","flowers","bush","bushes"}),
	"The plants are all blooming and "
	+"brilliantly colored. They look to be watered regularly, and "
	+"probably end up with more water than the slaves here.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh5", "east", 0);
   add_exit(TZ_MINTHOR + "mh3", "west", 0);
}
