#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street heads from north to south here."
    +"  It is not paved, but its dirt surface is easily defined, and"
	+" well-marked."
	+"  A large wooden guard house stands east of here, while the"
	+" town shop is just to the south.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st2","north",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/guard_house2","east",0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/shop","south",0);

  add_item(({"house","guard house"}), "The guard house is"
	+" a large, sturdy building made of a darkly-colored wood.  It"
	+" appears to be still in good shape and good use.\n");

  add_item(({"shop","store"}),"The town's one main shop"
     +" lies just south of here. Perhaps you should stop in for a visit?\n");
}
