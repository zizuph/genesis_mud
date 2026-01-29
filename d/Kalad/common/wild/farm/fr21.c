inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("You have found yourself infront of a little farm house on "+
	    "the outskirt of town. As you gaze at the house it looks as "+
	    "if it has seen better days. To the north and west you can see "+
	    "little fields ready for harvest. \n");

   add_exit("/d/Kalad/common/wild/farm/fr22","northeast");
   add_exit("/d/Kalad/common/wild/farm/smfrm2hse","northwest");
   add_exit("/d/Kalad/common/wild/farm/fr20","south");
}
