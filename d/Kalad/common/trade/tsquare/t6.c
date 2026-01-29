inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("The Trading Square");
set_long("You have entered the trading square. All around you are "
        +"shops and open doors. Signs are flapping in the wind in "
	+"all directions. A brilliant red sign catches your eye too. "
        +"The shops here sell goods for the common "
       +"man, more exotic items can be found north of here, "
       +"in the caravan district.\n");
add_item(({"signs"}),"The signs are emblazoned with shop and "
                            +"merchant names.\n");
add_item(({"red sign"}),"This sign says Ahkmed's Basket Shop.\n");
add_cmd_item("sign","read","Ahkmed's Basket Shop\n");
add_item(({"door"}),"The door is slightly ajar, as if someone wants "
                   +"you to come inside.\n");
add_exit(TRADE(tsquare/t5),"southeast");
add_exit(TRADE(tsquare/t7),"west");
add_exit(TRADE(tsquare/basket_shop),"east");
add_exit(TRADE(tsquare/hconn1),"north");
}
