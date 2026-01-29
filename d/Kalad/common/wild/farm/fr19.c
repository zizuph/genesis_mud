inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are on the outskirts of the Farmers Coop, which is "+
	    "the agriculture center of Kalad. To the west is a small "+
	    "run down farm house and a few small cultivated fields. "+
	    "As you look to the northeast and south you can see more "+
	    "fields that are ready to be harvested. \n");

   add_exit("/d/Kalad/common/wild/farm/fr20","northeast");
   add_exit("/d/Kalad/common/wild/farm/smfrm1hse","west");
   add_exit("/d/Kalad/common/wild/farm/fr18","south");
}
