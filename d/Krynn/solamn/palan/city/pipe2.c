/* created by Aridor 12/14/93 */

#include "windpipe.h"

inherit ROOM_BASE

void
create_palan_room()
{
    set_short("Inside the shaft");
    set_long("You are in the corner of a horizontal and a vertical shaft. " +
	     "A ladder leads up from here, and you can also walk along the " +
	     "floor of the horizontal shaft. The walls of the shaft seem to " +
	     "glow a little.\n");

    INSIDE;

    add_exit(ROOM + "pipewe1","south",0,1);
    add_exit(ROOM + "pipeud2","up",0,5);

    LIGHT;
    add_item(({"shaft"}),
	     "The shaft is a round shaft and it is very wide, you can hardly see the " +
	     "wall on the other side. You wonder what the purpose of the shaft is.\n");
    add_item(({"wall","walls"}),
	     "The wall close to you is made from some unkown material. It is very smooth " +
	     "and the ladder you are standing on is bolted to the wall. You can hardly " +
	     "make out the wall on the other side of the shaft though. The wall give off " +
	     "a strange glow, illuminating the shaft.\n");
    add_item("ladder",
	     "It's a very long ladder going up made from iron. You cannot see " +
	     "the end of it.\n");
}


init()
{
  string where = TP->query_prop(PLAYER_S_BLOWN_DIR);
  ::init();
  if (where)
    {
      write("The wind seems to halt for a moment, only to pick up speed later.\n");
      set_alarm(itof(random(10)+3),0.0,"blow_me_away", where);
    }
}


blow_me_away(string where)
{
  if (where == "south")
    {
      write("The wind now turns sideways and you are blown south by a strong gust of wind along the shaft.\n");
      TP->move_living(where + ", blown by a gust of wind", ROOM + "pipe3",0,1);
    }
  else /*where == "north"*/
    {
      write("The wind now turns and you are blown up by a strong force of wind along the shaft.\n");
      TP->move_living("up, blown by a gust of wind", ROOM + "pipe1",0,0);
    }
}
