inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
   create_room()
{
   ::create_room();
   set_short("The Central Trading Square");
   set_long("You have entered the trading square. All around you are "
      +"shops and open doors. Signs are flapping in the wind in "
      +"all directions. Southeast of you is a building and a sign. "
      +"Directly east from here is a small, ramshackle building. "
      +"The shops here sell goods for the common "
      +"man, more exotic items can be found in the north of here, "
      +"in the caravan district.\n");
   add_item(({"sign","signs"}),"The sign says The Rickety Roaring Restaurant.\n");
   add_item(({"red sign"}),"This sign says Guido's Clothes Shop");
   add_item(({"door"}),"The door is slightly ajar, as if someone wants "
      +"you to come inside.\n");
   add_cmd_item("sign","read","The Rickety Roaring Restaurant.\n");
   add_item(({"building"}),"A large building with a sign in front of it.\n");
   add_item(({"small building","ramshackle building"}),
      "A small wooden structure that has been squeezed in among the other "+
      "buildings of the Trading Square.\n");
   add_item(({"buildings"}),"Which one?\n");
   add_exit(TRADE(tsquare/c3),"north");
   add_exit(TRADE(tsquare/c1),"south");
   add_exit(TRADE(restaurant),"southeast",0,-1,-1);
   add_exit(TRADE(shop/pierce_shop),"east",0,-1,-1);
}
