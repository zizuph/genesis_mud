/* modified by Antharanos */
   inherit "/d/Kalad/room_std";
# include "/d/Kalad/defs.h"
create_room()
{
   ::create_room();
   set_short("Cliffside Junction");
   set_long("You are at a T-junction on Cliffside road. To the "
      +"north you see the road leading to the trading square "
      +"and here Cliffside Road continues along the cliff ledge to "
      +"both the east and west.\n");
   add_item(({"road"}),"A small road that leads north.\n");
   add_item(({"cliffside road"}),"A large concourse heading both to the "+
      "west and east.\n");
   add_exit(TRADE(cliffside/cliffside3),"west");
   add_exit(TRADE(cliffside/cliffside2),"east");
   add_exit(TRADE(ts3),"north");
   hear_bell = 2;
}
