/*     Created by:      Antharanos
 *     Location:         
 *     Modified:        Toby, 970919 (fixed typos)
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   set_short("The Central Trading Square");
   set_long("You have entered the trading square. All around you are "
      +"shops and open doors. Signs are flapping in the wind in "
      +"all directions. "
      +"The shops here sell goods for the common "
      +"man, more exotic items can be found in the north of here, "
      +"in the caravan district.\n");
   add_item(({"sign","signs"}),"They are signs pointing at all the "
      +"various shops in the area.\n");
   add_exit(TRADE(jail),"east","@@block",-1,-1);
   add_exit(TRADE(tsquare/t7),"north");
   add_exit(TRADE(tsquare/c2),"south");
}
block()
{
   write("That way lies the jailhouse! You don't want to go there!\n");
   return 1;
}
