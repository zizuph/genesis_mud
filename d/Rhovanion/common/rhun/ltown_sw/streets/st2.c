#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  Two paths meet here to form a crossroads, with branches"
	+" leading off to the north, south, east, and west.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st3","north",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st5","south",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st1","west",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st6","east",0);
}
