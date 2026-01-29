#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room() {
  set_short("Sea\n");
  set_long("You are in the open sea. A small volcano island is\n"+
	   "visible northeast of here, very far away.\n");

  WATER

}


 