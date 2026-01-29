inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have started along Farmers Road which provides travel "+
            "between the agriculture center of Kalad and Kabal. To the "+
	    "west you see the well beeten path that leads towards the "+
	    "Farmers Coop and to the east you see the Kabal City gates. \n");

   add_exit("/d/Kalad/common/wild/farm/fr2","west");
   add_exit("/d/Kalad/common/wild/farm/farm_gate","east");
}
