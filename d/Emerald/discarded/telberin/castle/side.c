inherit "/std/room";

#include "default.h"

void
create_room()
{
  set_short("Side of building");
  set_long("You are clinging for dear life on the side of a building "+
	"about forty feet above the road. You could go up from here to the "+
	"relative safety of the roof, but climbing down is impossible from "+
	"here.\n");

  add_exit("/d/Emerald/room/keep/roof4","up",0);

  add_item("building","The building appears to be some sort of outer "+
	"building of the keep.\n");
  add_item("keep","The keep is directly west.\n");
  add_item(({"side of building","side"}),"You are hanging on to the side "+
	"of the building, just beside an open window.\n");
  add_item("outbuildings","You are standing on the roof of one of the "+
        "keep's outbuildings.\n");
  add_item("window","The window is just within your reach; you _may_ be able "+
	"to get to it.\n");
   add_item("roof","Looks like a fairly easy climb.\n");
}

void
init()
{
  ::init();
  add_action("do_enter","enter");
}

int
do_enter(string str)
{
  notify_fail("Enter what?\n");
  if(!str)
	return 0;

  notify_fail("Enter what?\n");
  if(str != "window")
  	return 0;

  write("You enter the open window.\n");
  tell_room(TO, QCTNAME(TP)+" leaves into the window.\n", TP);
  TP->move_living("M","/d/Emerald/room/keep/vamp/v1",0);
  tell_room(ENV(TP), QCTNAME(TP)+" enters the room.\n", TP);
  return 1;
}
