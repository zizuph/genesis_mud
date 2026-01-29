inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Wall Street");
set_long("There is an intersection here. To the west, you can see "
        +"the trading square, and to the north, the caravan district "
        +"looms closer. A door lies slightly ajar to the east, "
        +"beckoning for someone to come inside.\n");
add_item(({"homes", "home"}),"These are the homes of the lowerclassed "
                            +"merchants of Kabal. The houses are "
                            +"rather plain.\n");
add_item(({"door"}),"The door is slightly ajar, as if someone wants "
                   +"you to come inside.\n");
add_item(({"wall"}),"This is the great wall of Kabal, which seperates "
                  +"the city dwellers from the demihumans who are "
                  +"constantly trying to get into the city.\n");
  add_item(({"road","street","streets","roads","intersection"}),
 	"This is a plain road, "
        +"not at all interesting in the least. It is made of worn "
        +"stone, and is dirty.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
        +"lower-classed people.\n");
hear_bell = 2;
add_exit(TRADE(wall/connect1),"west");
add_exit(TRADE(wall/house1),"east");
add_exit(TRADE(wall/wall6),"north");
add_exit(TRADE(wall/wall4),"south");
}
