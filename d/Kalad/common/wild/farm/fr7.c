inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have come to a point in the road that is covered by "+
	    "a stream, although it does not look deep the water seems "+
	    "to be extreamly cold. You can see a good crossing spot "+
	    "to the west. \n");

   add_exit("/d/Kalad/common/wild/farm/fr8","west");
   add_exit("/d/Kalad/common/wild/farm/fr6","east");
}
