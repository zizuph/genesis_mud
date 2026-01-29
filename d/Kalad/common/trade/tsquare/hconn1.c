inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
   void
create_room()
{
   set_short("Between districts");
   set_long("The road is a bit narrower here, but is leading straight "
      +"north to the caravan district, and south to the tradesman "
      +"district.\n");
   hear_bell = 2;
   add_exit(TRADE(tsquare/hc1),"north");
   add_exit(TRADE(tsquare/t6),"south");
}
