
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "../goblins.h"

create_room()
{
  ::create_room();
  change_prop(ROOM_I_LIGHT,1);
  change_prop(ROOM_I_INSIDE,1);

set_short("Sink hole");

  set_long(break_string(
    "Here the cavern opens up somewhat into a small chamber. " +
    "A small sinkhole has formed here. " +
    "In order to secure the sinkhole, the goblins have placed a grate over it."+
    "\n\n",70));

  add_exit(GOBLIN_CAVERN_DIR + "tunnel2","west","@@turns",0);
  add_exit(GOBLIN_CAVERN_DIR + "CLOSED","down","@@closed",0);

  add_item(({"hole","sinkhole"}), 
    break_string("The sinkhole has formed because the ground underneath " + 
    "eroded until it collapsed. There is probably some water down there!\n",
    70));

  add_item(({"water"}),"You cannot see any, but there must have been some once.\n");
  add_item(({"grate"}),"There is no way you could possibly open it.\n");


}



int
turns()
{
  write("\nThe tunnel turns west.\n\n");
  return 0;
}

int
closed()
{
  write(break_string("The sinkhole is actually under construction. " +
    "A note will be posted on the goblin board when it is open.\n",70));
  return 1;
}


