inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("As you follow the road you begin to wonder how the farmers "+
	    "wagons can travel down this broken up road to deliever their "+
	    "goods to the city. Further to the northwest you can see the "+
	    "road bend back to the west and disapeer out of sight. To the "+
	    "southeast you can see down onto over grown fields. \n");

   add_exit("/d/Kalad/common/wild/farm/fr6","northwest");
   add_exit("/d/Kalad/common/wild/farm/fr4","southeast");
}
