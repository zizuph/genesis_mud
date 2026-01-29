inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("the trading square");
   set_long("You have entered the trading square. All around you are "
      +"shops and open doors. Signs are flapping in the wind in "
      +"all directions. A brilliant red sign catches your eye too. "
      +"The shops here sell goods for the common "
      +"man, more exotic items can be found in the north of here, "
      +"in the caravan district.\n");
   add_item(({"sign","signs"}),"The signs are emblazoned with shop and "
      +"merchant names.\n");
   add_item(({"door"}),"The door is slightly ajar, as if someone wants "
      +"you to come inside.\n");
   add_item(({"red sign"}),"It says: Xavier's Jewel Shop.\n");
   add_exit(TRADE(tsquare/t10),"south");
   add_exit(TRADE(tsquare/t8),"northeast");
   add_exit(TRADE(tsquare/jewel_shop),"east");
}

