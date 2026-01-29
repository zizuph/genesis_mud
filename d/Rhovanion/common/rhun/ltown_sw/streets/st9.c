#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk the streets of this large town in Rhun, near the"
	+" northwest edge of the great Sea of Rhun."
	+"  The road continues from northwest to southeast here.  You"
	+" may also approach the town wall by heading east.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st7","northwest",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/bywall3","east",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st10","southeast",0);

  add_item(({"wall","town wall"}), "The town wall, standing just east"
	+" of here, is low and made of solidly-packed stones.  It"
	+" would not serve very useful for purposes of defense.\n");
}
