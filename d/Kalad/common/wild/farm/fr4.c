inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are traveling along the side of a large hill, the "+
	    "surface of the road is getting worse as you go on making "+
	    "travel dificult. As you look to the northwest you can "+
	    "can tell the road continues to break up and seems to get "+
	    "better to the southeast. \n");

   add_exit("/d/Kalad/common/wild/farm/fr5","northwest");
   add_exit("/d/Kalad/common/wild/farm/fr3","southeast");
}
