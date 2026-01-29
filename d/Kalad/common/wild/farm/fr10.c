inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are now standing in the shadow of a great hill just "+
	    "to your east, it seems to just loom there in front of you. "+
	    "You can see a bend in the road not to far to the northeast "+
	    "and some fields to the southwest. \n");

   add_exit("/d/Kalad/common/wild/farm/fr11","southwest");
   add_exit("/d/Kalad/common/wild/farm/fr9","northeast");
}
