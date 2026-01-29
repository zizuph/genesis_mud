inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Small field");
   set_long("You are standing in the middle of a small grain field. "+
	    "As the wind blows by moving the grain, it makes the field "+
	    "look like you are floating in a golden sea with calm waves "+
	    "flowing by you. To the east you can see a small garden and "+
	    "to the north you can see another field.\n");

   add_exit("/d/Kalad/common/wild/farm/smfrm1f3","north");
   add_exit("/d/Kalad/common/wild/farm/smfrm1f1","east");
}
