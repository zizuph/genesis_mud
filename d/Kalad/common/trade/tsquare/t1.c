inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Trade Square");
set_long("You have entered the commoners' trading square. Around you "
        +"lies shops of all sorts carrying goods for the common man. "
        +"There are signs flapping in the wind displaying shop names "
        +"and beckoning for someone to come inside.\n");
add_item(({"signs"}),"These are the signs hanging outside shops of the "
                            +"lowerclassed merchants of Kabal. The shops are "
                            +"rather plain.\n");
add_item(({"door"}),"The door is slightly ajar, as if someone wants "
                   +"you to come inside.\n");
add_exit(TRADE(tosquare),"south");
add_exit(TRADE(tsquare/t2),"east");
add_exit(TRADE(tsquare/t12),"west");
add_exit(TRADE(tsquare/c1),"north");
}
