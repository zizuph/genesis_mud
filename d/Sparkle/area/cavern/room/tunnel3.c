
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

  set_short("Merging of two tunnels.");

  set_long(break_string(
    "Here the narrow passage you have been following joins a wider tunnel. " +
    "The new tunnel runs northeast to southwest. " +
    "\n\n",70));

  add_exit(GOBLIN_CAVERN_DIR + "throne" ,"northeast","@@turns",0);
  add_exit(GOBLIN_CAVERN_DIR + "nbridge","south",0,0);
  add_exit(GOBLIN_CAVERN_DIR + "armoury","southwest",0,0);

}

int
turns()
{
  write("The tunnel turns south.\n");
  return 0;
}
