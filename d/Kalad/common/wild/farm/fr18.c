inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are on the outskirts of what seems to be a small "+
	    "farming community. Everywhere around you is green and "+
	    "looks as if in full bloom, it must be getting close to "+
	    "harvest time. To the west you can see a couple of small "+
	    "cultivated fields, to the north you can see a small farm "+
	    "house and to the east you can see overgrown fields. \n");

   add_exit("/d/Kalad/common/wild/farm/fr19","north");
   add_exit("/d/Kalad/common/wild/farm/fr17","east");
}
