#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()
{
  set_short("in the ocean");

  set_long("You are swimming in the cold sea, somewhere between Re Albi\n"+
	   "and Sparkle. North of here you see a small pirate ship, and\n"+
	   "back south goes the ships to Gont.\n");

  add_item("ship","It's an old and dirty pirate ship. A small rope ladder\n"+
	   "hangs on the side of it.\n");
  WATER;
}
init()
{
  ::init();
    add_action("climb","climb");
    add_action("swim","swim");
  }
swim(string s)
{
  NF("Swim where?\n");
  if(s!="south")
    return 0;

  TP->move_living("south",SHIPS+"gontsparkle/sea5");
  return 1;
}
climb(string s)
{
  NF("Climb what?\n");
  if(s!="ladder")
    return 0;

  TP->move_living("up the ladder",SHIPS+"pirate/sh1");
  return 1;
}