inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are now surrounded by overgrown fields, there seems "+
	    "to be no end of these fields and no sign of civilization "+
	    "to be seen. To both the east and west you can see nothing "+
	    "but overgrown and abandoned fields. \n");

   add_exit("/d/Kalad/common/wild/farm/fr17","west");
   add_exit("/d/Kalad/common/wild/farm/fr15","east");
}
