inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

void
create_room()
 {
  set_short("Closet");
  set_long("You are in a small closet off of the master bedroom in the "
	+"Minthor House.  Elegant, expensive clothes hang on hooks all "
	+"around, as well as lying folded on some shelves.  There are "
	+"shoes and some other miscellaneous items on the floor here, "
	+"but nothing that seems too interesting.\n");
  add_item(({"clothes","shoes"}),"They look very nice, and most likely "
	+"extremely costly.\n");
  add_item("items","You notice things from belts to canes to other "
	+"clothing accessories.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_prop(ROOM_I_LIGHT,0);
  INSIDE
   add_exit(TZ_MINTHOR + "mh33","north");

}


