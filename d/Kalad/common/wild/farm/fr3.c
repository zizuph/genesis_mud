inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are now climbing into the hilly parts of Farmers Road. "+
	    "To the southwest you can see a great hill and to the "+
	    "northeast you can make out the bottom of a valley. The "+
	    "road continues to the northwest on towards the Farmers "+
	    "Coop or east towards Kabal. \n");

   add_exit("/d/Kalad/common/wild/farm/fr4","northwest");
   add_exit("/d/Kalad/common/wild/farm/fr2","east");
}
