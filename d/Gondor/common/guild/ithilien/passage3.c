#pragma save_binary

inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
  set_short("A dark stairway");
  set_long(BS("You are standing in a long and dark stairway passage, "+
    "with narrow walls, rough and uneven on both sides, and a great many "+
    "steps both above and below you. You see only darkness in both "+
    "directions.\n"));
  add_item("passage","The passage runs up and down here, both ways leading\n"+
    "to darkness. The rock walls are rough and uneven.\n");
  add_item(({"stairway","steps"}),BS("There are a great many steps in this "+
    "rock-carved stairway. A little water trickles down the rough steps.\n"));
  add_item("water","A little water trickles down the rough steps.\n");
  add_item("walls","The walls are roughly carved out of the rock.\n");
  add_exit(RANGER_ITH_DIR+"passage4","up",0);
  add_exit(RANGER_ITH_DIR+"passage2","down",0);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
}
