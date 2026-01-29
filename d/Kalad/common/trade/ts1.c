inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("The road between the Trading Square and Cliffside");
   set_long("You are on a small cobblestoned road between the Trading "+
      "Square and Cliffside Road. The former lies to the north, while the "+
      "latter is to the south. Numerous buildings line the road.\n");
   add_item(({"small cobblestoned road","small road","cobblestoned road","road"}),
      "A narrow roadway connecting the Trading Square with the busy "+
      "Cliffside road in the south.\n");
   add_item(({"buildings","building"}),"Old wooden structures that "+
      "house the merchants and traders of the district.\n");
   add_exit(TRADE(tosquare),"north");
   add_exit(TRADE(ts2),"south");
}
