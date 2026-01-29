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
      "then Cliffside, which is immediately to the south. Lining both "+
      "sides of the street are many old wooden buildings.\n");
   add_item(({"small cobblestoned road","small road","cobblestoned road","road","street"}),
      "A narrow roadway connecting the Trading Square with the busy "+
      "Cliffside road in the south.\n");
   add_item(({"old buildings","buildings","building"}),
      "Old wooden structures that serve as homes for the people of this district.\n");
   add_exit(TRADE(ts2),"north");
   add_exit(TRADE(cliffside/cliffside_junc),"south");
}
