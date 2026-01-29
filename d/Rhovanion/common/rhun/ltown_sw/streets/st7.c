#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street forks here, with branches heading off to the"
	+" northeast, southeast, and west."
    +"  It is not paved, but its dirt surface is easily defined, and"
	+" well-marked."
	+"  A small residence stands just south of here.\n");

  add_exit(RHUN_DIR+"ltown_sw/bldgs/house2","south",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st6","west",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st8","northeast",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st9","southeast",0);

  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
}
