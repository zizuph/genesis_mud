#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street heads from north to south here."
        +"  It is not paved, but its dirt surface is easily defined, and"
	+" well-marked.  A small residence stands just east of here.\n");

  add_exit(RHUN_DIR+"ltown_sw/bldgs/house3","east",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st4","north",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st2","south",0);

  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
}
