inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Path");
  set_long("To the east lies the end of the marble sidewalk, while "
	+"the sidewalk leads back to the main path to the south. To "
	+"the north lies the edge of the large mansion which dominates "
	+"the scenery here. Surrounding you are are blooming plants, "
	+"the like which haven't been seen in the open on Athas for "
	+"eons. Flowers and bushes bath in the harsh rays of the sun, "
	+"kept alive by liters of water per hour. The sheer wealth it "
	+"takes to accomplish a feat like this is amazing.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
        +"standing water!\n");
  add_item("sidewalk","It is made of a brilliantly polished marble, "
	+"and seems to be kept impeccably clean.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
        +"a dark grey granite. It would seem to protect decently well "
        +"against thugs and the like, as well as keep slaves in.\n");
   add_item(({"plant","plants","flower","flowers","bush","bushes"}),
	"They are brilliantly colored plants that must cost an "
	+"incredible amount of money to maintain.\n");
  add_item(({"building","house","mansion"}),"The building is somewhere "
	+"around four  stories tall(about 50 feet), and is covered in statues and "
        +"other decorative items.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
        +"be very expensive, probably worth their weight in water.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh7", "east", 0);
  add_exit(TZ_MINTHOR + "mh5","south", 0);
}
