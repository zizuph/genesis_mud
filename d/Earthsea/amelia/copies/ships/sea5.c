#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room() {
  set_short("Sea\n");

  set_long(
  "You are in the open sea.\n");
 
 set_long("You are in the open sea. To the east you can see a small island.\n"+
	  "You can also hear some sounds from the island.\n");
  WATER;

}

init()
{
  ::init();

    add_action("swim","swim");
  }
swim(string s)
{
  NF("You think it might be too dangerous to swim in that direction.\n");
  if(s!="east")
    return 0;

  TP->move_living("east",SHIPS+"island/s1");
  return 1;
}
 
