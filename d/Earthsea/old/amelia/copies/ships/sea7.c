#pragma save_binary

inherit "/std/room";

#include "/d/Roke/common/defs.h"

void
create_room() {
  set_short("Sea\n");
  set_long("You are in the open sea.\n"+
	   "You see some seagulls far away.\n");

  WATER

}


 