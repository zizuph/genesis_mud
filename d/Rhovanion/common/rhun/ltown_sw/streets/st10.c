#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street curves from south to northwest here."
        +"  It is not paved, but its dirt surface is easily defined, and"
	+" well-marked."
	+"  The town pub-- the busiest place in town-- stands just to the"
	+" south.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st9","northwest",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/bar","south",0);
}
