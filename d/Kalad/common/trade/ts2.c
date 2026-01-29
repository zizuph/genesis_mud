inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("The road between the Trading Square and Cliffside");
   set_long("You are on a small cobblestoned road between the Trading "+
      "Square and Cliffside Road. The former lies farther to the north "+
      "then Cliffside, which is just a short distance to the south. "+
    "Off to the west, you see what looks like a stable.\n");
   add_item(({"small cobblestoned road","small road","cobblestoned road","road"}),
      "A narrow roadway connecting the Trading Square with the busy "+
      "Cliffside road in the south.\n");
   add_item(({"old buildings","buildings","building"}),
      "Old wooden structures that serve as homes for the people of this district.\n");
   add_exit(TRADE(ts1),"north");
   add_exit(TRADE(ts3),"south");
   add_exit(TRADE(stable),"west");
}
