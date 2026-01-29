#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  The road leads north here,"
	+" approaching the town gate.  South of you stands the"
	+" town bank, while the western wall may be approached"
	+" by heading west.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/westgate","north",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/bywall2","west",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/bank","south",0);

  add_item(({"wall","town wall"}), "The town wall, standing just"
	+" northeast"
	+" of here, is low and made of solidly-packed stones.  It"
	+" would not serve very useful for purposes of defense.\n");
  add_item("bank", "The town bank is just south"
	+" of here.  It looks like a sturdy old building.  The"
	+" doors open, if you'd like to step inside.\n");
}
