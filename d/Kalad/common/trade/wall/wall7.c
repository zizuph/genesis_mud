inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Wall Street");
set_long("Here, the road widens in anticipation of the intersection "
       +"to the north. Far to the north, the caravan district still "
        +"looms closer. Here, the doors of the homes around you are all"
        +" closed, and most likely locked.\n");
add_item(({"doors","door"}),"These are the doors to homes. They are all "
                           +"locked.\n");
add_item(({"homes", "home"}),"These are the homes of the lowerclassed "
                            +"merchants of Kabal. The houses are "
                            +"rather plain.\n");
add_item(({"wall"}),"This is the great wall of Kabal, which seperates "
                  +"the city dwellers from the demihumans who are "
                  +"constantly trying to get into the city.\n");
  add_item(({"road","street","streets","roads","intersection"}),
 	"This is a plain road, "
        +"not at all interesting in the least. It is made of worn "
        +"stone, and is dirty.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
        +"lower-classed people.\n");
add_exit(TRADE(wall/wall6),"south");
add_exit(TRADE(wall/wall8),"north");
hear_bell = 2;
}
