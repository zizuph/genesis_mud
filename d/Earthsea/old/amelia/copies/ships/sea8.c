#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room() {
  set_short("Sea\n");
  set_long("You are in the open sea.\n"+
	   "Far away you can see Sparkle.\n");

  WATER

}


 