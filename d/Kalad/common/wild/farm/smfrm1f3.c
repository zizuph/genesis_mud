inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small field");
   set_long("You find yourself in the middle of a corn field. The stalks "+
	    "are so tall it is making it hard to find your way through, "+
	    "it seems like every step you take is a wrong direction. As "+
	    "you try to look around you can make out a glimpse of a trail "+
	    "that runs either north or south. \n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1f4","north");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f2","south");
}
