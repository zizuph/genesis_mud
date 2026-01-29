inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   
   set_short("High Street");
   set_long("You walk along the High Street. Northwards you can see some "+
      "buildings, while to the south there is a basket that can ferry "+
      "you or goods in general downwards.\n");
   
   hear_bell = 3; /* loud: outdoors in the central district */
   
   add_exit(CENTRAL(high-circle-south), "north", 0, 1);
   add_exit(CENTRAL(high/s5),"south");
   
}
