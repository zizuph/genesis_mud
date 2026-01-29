inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are traveling along Farmers Road just outside of the "+
	    "Farmers Coop. To the north and south you can see small "+
	    "farms that are struggling to stay alive and compete with "+
	    "the Coop. \n");

   add_exit("/d/Kalad/common/wild/farm/fr21","north");
   add_exit("/d/Kalad/common/wild/farm/fr19","southwest");
}
