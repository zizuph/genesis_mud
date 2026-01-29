inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have found your self in the middle of a number of "+
	    "abandoned fields. Even though there is an errie sense about "+
	    "this place, you seem to have a strange calm come over "+
	    "you. To the east all you can see is more fields that look "+
	    "oddly familiar and to the west you can see some pleasant "+
	    "looking green fields. \n");

   add_exit("/d/Kalad/common/wild/farm/fr18","west");
   add_exit("/d/Kalad/common/wild/farm/fr16","east");
}
