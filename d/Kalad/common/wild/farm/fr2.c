inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You are traveling down farmers road. On either the north or "+
	    "south side of you are fields over grown with unwanted plant "+
	    "life, it seems as if no one has worked these fields in some "+
	    "time. \n");

   add_exit("/d/Kalad/common/wild/farm/fr3","west");
   add_exit("/d/Kalad/common/wild/farm/fr1","east");
}
