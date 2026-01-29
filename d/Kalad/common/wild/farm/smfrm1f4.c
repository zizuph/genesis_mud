inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small field");
   set_long("This field looks like it has just been harvested, it is "+
	    "completely barren, except for a bit of stuble left behind "+
	    "during the harvest. To the south you can see a tall corn "+
	    "field and to the east you can see an orchard. \n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1f5","east");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f3","south");
}
