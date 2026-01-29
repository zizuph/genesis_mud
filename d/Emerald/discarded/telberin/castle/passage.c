inherit "/std/room";

#include "default.h"

void
create_room()
{
  set_short("Cramped passage");
  set_long("This extremely cramped passage is a hideaway, with some stairs "+
	"leading up and a small area to hide in just behind the fire. "+
	"It is very dusty down here, this place having not been used in quite "+
	"a while.\n");

  add_exit("/d/Emerald/telberin/castle/house4","back",0);
  add_exit("/d/Emerald/telberin/castle/roof1","up",0);

  add_item(({"stairs","stair"}),"The stairs lead up to the roof.\n");
  add_item("dust","There's a lot of it down here.\n");
}
