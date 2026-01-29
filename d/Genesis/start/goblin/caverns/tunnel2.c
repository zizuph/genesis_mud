
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

  set_short("Intersection of two tunnels.");

  set_long(break_string(
    "The narrow passage you have been following crosses a broad tunnel here. " +
    "To the north, you sense, rather than hear, the faint sound of running water. " +
    "To the east, there is a silent, ominous tunnel. " +
    "To the southwest, the ground looks very well travelled. " +
    "The tunnel southeast seems to lead upwards. " +
    "\n\n",70));

  add_exit(GOBLIN_CAVERN_DIR + "sbridge","north",0,0);
  add_exit(GOBLIN_CAVERN_DIR + "sinkhole","east","@@turns",0);
  add_exit(GOBLIN_CAVERN_DIR + "altar","southwest",0,0);
  add_exit(GOBLIN_CAVERN_DIR + "tunnel1","southeast",0,0);

}

int
turns()
{
  write("The tunnel turns northeast.\n");
  return 0;
}
