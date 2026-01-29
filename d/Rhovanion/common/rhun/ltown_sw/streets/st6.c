#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  The road leads east to west from here.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st7","east",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st2","west",0);
}
