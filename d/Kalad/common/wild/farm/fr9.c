inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have reached a bend as the road continues around the "+
	    "base of this massive hill. You can see fields around the "+
	    "base of the hill to the southwest and a flowing stream to "+
	    "the east. \n");

   add_exit("/d/Kalad/common/wild/farm/fr10","southwest");
   add_exit("/d/Kalad/common/wild/farm/fr8","east");
}
