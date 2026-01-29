inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have reached a bend in the road, You can now see clearly "+
	    "down both directions the road travels. To the west you see "+
	    "stream crossing the road and to the southeast you can see "+
	    "the road is in need of some major repairs. \n");

   add_exit("/d/Kalad/common/wild/farm/fr7","west");
   add_exit("/d/Kalad/common/wild/farm/fr5","southeast");
}
