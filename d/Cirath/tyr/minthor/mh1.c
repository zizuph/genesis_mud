inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/minthor/defs.h"
create_room()
 {
   set_short("Path");
  set_long("The Caravan Way falls behind you, as you turn northward "
	+"onto a large path. To both the east and west stands a large "
	+"stone wall, while to the north is a gate. Over the top of "
	+"the wall to the north a building is visible. It seems to "
	+"be about 4 stories tall, and decorated with statues. A "
	+"strange smell assails your nostrils, a smell that is utterly "
	+"alien on Athas. High above you, the crimson sun shimmers in "
	+"the olive-tinged sky like a puddle of fiery blood.\n");
  add_item(({"smell"}),"It smells like moisture, maybe even free "
	+"standing water!\n");
  add_item(({"path"}),"This is a large path, about half as large as "
	+"Caravan Way, and this appears to be the frontal entrance "
	+"to a house. This must be the house of some noble.\n");
  add_item(({"wall"}),"The wall is about 9 feet tall, and is made of "
	+"a dark grey granite. It would seem to protect decently well "
	+"against thugs and the like, as well as keep slaves in.\n");
  add_item(({"building"}),"The building is somewhere around four "
	+"stories tall(about 50 feet), and is covered in statues and "
	+"other decorative items.\n");
  add_item(({"statues","items"}),"They are nicely crafted and must "
	+"be very expensive, probably worth their weight in water.\n");
  ADD_ZIG_ITEM
  add_exit(TZ_MINTHOR + "mh2", "north", 0);
  add_exit(TZ_CARAVAN + "rd_cw_05","south", 0);
}
