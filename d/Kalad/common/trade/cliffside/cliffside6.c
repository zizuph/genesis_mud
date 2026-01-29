inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
object ob1;

void
create_room()
{
set_short("Cliffside Road");
set_long("The road continues here. It stretches far to the east and "
	+"west, but there are also houses to both the north and south. "
	+"The southern house looks plain, while the northern one is "
	+"actually two stories and is one of the larger houses you "
	+"have seen.\n");
add_item(({"house"}),"These houses belong to the underpriveleged merchants of this "
       +"area. The houses are dirty, small, and uninteresting.\n");
  add_item(({"cliff"}),"It is a massive cliff to your south. Below "
   +"it is the port district of Kabal.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
   +"not at all interesting in the least, it is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
add_item(({"southern house","south house"}),"It is very small and "
	+"looks very uninteresting.\n");
add_item(({"northern house","north house"}),"It is one of the "
	+"larger houses you have seen. It stands two stories tall "
	+"and looks to be in fairly good shape. It's door is standing "
	+"ajar.\n");
add_exit(TRADE(cliffside/cliffside5),"east");
add_exit(TRADE(cliffside/cliffside7),"west");
add_exit(TRADE(cliffside/house1),"south");
add_exit(TRADE(cliffside/house2),"north");
hear_bell = 1;
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
