inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
    set_short("Trade Square");
    set_long("You are in the commoners trading square. Around you "
      +"lies shops of all sorts carrying goods for the common man. "
      +"There are signs flapping in the wind displaying shop names "
      +"and beckoning for someone to come inside.\n");
    add_item(({"signs"}),"These are the signs hanging outside shops of the "
      +"lowerclassed merchants of Kabal. The shops are "
      +"rather plain. You see a brilliant red sign "
      +"hanging outside a door to the east.\n");
    add_item(({"door"}),"The door is slightly ajar, as if someone wants "
      +"you to come inside.\n");
    add_item(({"red sign"}),"It says 'Barney's Wine Store'.\n");
    add_exit(TRADE(tsquare/t4),"north");
    add_exit(TRADE(tsquare/t2),"southwest");
    add_exit(TRADE(tsquare/wine_shop),"east");
}
