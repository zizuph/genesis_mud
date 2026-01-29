inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;

void
create_room()
{
set_short("Wall Street");
set_long("The street continues along the wall here, extending far "
        +"to the north. The road here is very plain, and around you "
        +"sit the homes of the lowerclass merchants.\n");
add_item(({"homes", "home"}),"These are the homes of the lowerclassed "
                            +"merchants of Kabal. The houses are "
                            +"rather plain.\n");
add_item(({"wall"}),"This is the great wall of Kabal, which seperates "
                  +"city dwellers from the demihumans who try to get "
                  +"into the city.\n");
  add_item(({"road","street","streets","roads","intersection"}),
 	"This is a plain road, "
        +"not at all interesting in the least. It is made of worn "
        +"stone, and is dirty.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
        +"lower-classed people.\n");
add_exit(TRADE(wall/wall1),"south");
hear_bell = 2;
set_alarm(1.0,0.0,"reset_room");
add_exit(TRADE(wall/wall3),"north");
}
reset_room()
{
        if (!ob1)
        {
        ob1 = clone_object("/d/Kalad/common/trade/tmil.c");
        ob1 ->move_living("xxx", this_object());
        }
}
