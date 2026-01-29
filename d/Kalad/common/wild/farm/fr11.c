inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are now at the foot of a hill surrounded by fields "+
	    "overgrown with weeds and bushes, it doesn't look like "+
	    "anyone has taken car of these fields in quite some time. "+
	    "To the southwest you can see the road take a turn to the "+
	    "west and head through the fields and to the northeast you "+
	    "can see the road travel by a large hill. \n");

   add_exit("/d/Kalad/common/wild/farm/fr12","southwest");
   add_exit("/d/Kalad/common/wild/farm/fr10","northeast");
}
