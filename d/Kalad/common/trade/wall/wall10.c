inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;

void
create_room()
{
  set_short("Wall Street");
  set_long("This road seems to stretch on forever. The homes of the "+
    "lower class fill your vision. The only relief lies to the north, "+
    "where the fabled Kabal caravan district, home of exotic imports "+
    "and wares lies. The doorsof the homes around you are all closed, "+
    "and most likely locked.\n");
  add_item(({"doors","door"}),
    "These are the doors to homes. They are all locked.\n");
  add_item(({"homes", "home"}),
    "These are the homes of the lower classed merchants of Kabal. "+
    "The houses are rather plain.\n");
  add_item(({"wall"}),"This is the great wall of Kabal, which seperates "
                  +"the city dwellers from the demihumans who are "
                  +"constantly trying to get into the city.\n");
  add_item(({"road","street","streets","roads","intersection"}),
 	"This is a plain road, "
        +"not at all interesting in the least. It is made of worn "
        +"stone, and is dirty.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
        +"lower-classed people.\n");
add_exit(TRADE(wall/wall9),"south");
add_exit(TRADE(wall/wall11),"north");
hear_bell = 2;
set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
        if (!ob1)
        {
        ob1 = clone_object("/d/Kalad/common/trade/tmil.c");
        ob1 ->move_living("xxx", this_object());
        }
}
