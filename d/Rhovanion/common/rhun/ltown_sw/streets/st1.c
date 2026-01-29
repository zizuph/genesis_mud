#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street heads from east to west here."
    +"  It is not paved, but its dirt surface is easily defined, and"
    +" well-marked.  The town gate lies to the west, and a small"
    +" residence is just south of here.\n");

  add_exit(RHUN_DIR+"ltown_sw/bldgs/house1", "south", 0);
  add_exit(RHUN_DIR+"ltown_sw/streets/westgate", "west", 0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st2", "east", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"house","residence","building"}), "The"
    +" building is a small house, made entirely of wood.  It looks"
    +" as though some impoverished person still lives there.\n");
}
