inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("The road seems to turn here, to the west it heads through "+
	    "the middle of some old fields that seem to have been "+
	    "neglected for quite some time and to the northeast the "+
	    "road heads into a more hilly region. \n");

   add_exit("/d/Kalad/common/wild/farm/fr13","west");
   add_exit("/d/Kalad/common/wild/farm/fr11","northeast");
}
