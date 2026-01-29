inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
   create_room()
{
   ::create_room();
   set_short("A dark alley");
   set_long("The alley continues along, but ahead of you, it opens up. "
      +"You see people wandering along, and you hurry from the alley "
      +"to join in with the crowd.\n");
   add_item(({"people"}),"They look like people shopping in the trade "
      +"square.\n");
   add_exit(TRADE(to_central),"west");
   add_exit(TRADE(cliff_connect2),"south");
   add_exit(TRADE(tsquare/t11),"east");
   hear_bell = 1;
}
