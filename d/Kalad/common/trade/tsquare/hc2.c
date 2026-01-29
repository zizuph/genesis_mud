inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("Between districts");
   set_long("The road is quite narrow here and leads straight north "+
      "into the Caravan District, and south to the Trade District.\n");
   add_item(({"road"}),"A narrow road between the Caravan and Trade "+
      "districts.\n");
   add_exit(CVAN(road1-harvest),"north");
   add_exit(TRADE(tsquare/hconn2),"south");
}
