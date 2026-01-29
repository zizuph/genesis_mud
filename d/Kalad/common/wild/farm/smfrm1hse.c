inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small farm house");
   set_long("This is a small run down farm house there really isn't "+
	    "much to this place. As you look around you can't see many "+
	    "possesions or luxuries, just the bare necessities to get "+
	    "by on. You can see that you can exit to the north and "+
	    "south to get to the fields from here. \n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1f5","north");
   add_exit("/d/Kalad/common/wild/farm/fr19.c","east");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f1","south");
}
