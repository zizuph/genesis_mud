inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Path");
  set_long("The marble sidewalk extends back to the west, and then "
	+"north. To the north lies a huge mansion. Statues adorn the "
	+"house, making it look larger and more fierce. Most of the "
	+"statues are fierce looking monsters, and are used to keep "
	+"thieves out by the sheer ferocity of the images. Plants "
	+"surround you on all sides. There are flowers, and bushes, "
	+"and other organic matter that saps the water worse than "
	+"a thirsty half-giant.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item("sidewalk","It is made of a brilliantly polished marble, "
	+"and seems to be kept impeccably clean.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
   add_item(({"bush","bushes","flower","flowers","plant","plants"}),
	"They are brilliantly colored plants that must cost an "
	+"incredible amount of money to maintain.\n");
  add_item(({"building","house","mansion"}),"The building is somewhere "
	+"around four  stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh6", "north", 0);
  add_exit(TZ_MINTHOR + "mh4","west", 0);
}
