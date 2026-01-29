inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("Narrow alleyway");
   set_long("You are standing in a narrow alleyway between the Central "+
      "District in the northwest, home to many important governmental buildings "+
      "and the Trade District to the east, where goods are sold to the "+
      "common man. Various bits of filth litter the alleyway, their stench "+
      "seeming to pervade the entire area.\n");
   add_item(({"narrow alleyway","alleyway","alley"}),
      "A tight lane that looks as if it were added in as an afterthought. Dirty "+
      "old buildings line both sides of the alley, leaning over it as if "+
      "to block out the light of the sun.\n");
   add_item(({"dirty old buildings","dirty buildings","old buildings","buildings","building"}),
      "Weathered and in disrepair, the wooden structures look in great need "+
      "of proper care and management.\n");
   add_item(({"sun"}),
      "It lies far above you, its light terrible in its intensity.\n");
   add_item(({"bits of filth","filth"}),
      "The refuse of the poor souls that inhabit the buildings lining this alley.\n");
   add_exit(CENTRAL(caravan-gladiator),"northwest");
   add_exit(TRADE(cliff_connect3),"east");
   set_alarm(1.0,120.0,"msg");
}
block()
{
   write("The way is blocked by a barricade.\n");
   return 1;
}
msg()
{
   tell_room(TO,"A foul stench reaches your nostrils, making you want to leave "+
      "this alleyway as fast as possible.\n");
   return 1;
}
