inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small garden");
   set_long("You have steped out into a small garden. There are many "+
	    "different kinds of things growing here, but not enough to "+
	    "sell, this must be the private garden for the farmer. To "+
	    "the west you can see a field of grain ready to harvest. \n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1hse","north");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f2","west");
}
