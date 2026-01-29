inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small orchard");
   set_long("You seem to have found the orchard, the air here is filled "+
	    "with the sweet fragrance of fruit. You can see apple, peach, "+
	    "pear, and plum trees scattered amid the orchard. You can tell "+
	    "by the smell that everything is ripening for the harvest. \n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1hse","south");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f4","west");
}
