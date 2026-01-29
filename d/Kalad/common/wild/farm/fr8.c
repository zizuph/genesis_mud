inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You seem to have reached a point in the road that is blocked "+
	    "by a stream. To continue you must either cross its cold "+
	    "waters to the east or head west towards the Farmers Coop. \n");

   add_exit("/d/Kalad/common/wild/farm/fr9","west");
   add_exit("/d/Kalad/common/wild/farm/fr7","east");
}
