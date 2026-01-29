
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "../goblins.h"
#include "/sys/stdproperties.h"

create_room()
{
  ::create_room();
  change_prop(ROOM_I_LIGHT,1);
  change_prop(ROOM_I_INSIDE,1);

  set_short("A fork in the tunnel.");

  set_long(break_string(
    "The narrow passage you have been following branches here. " +
    "To the east, you can hear the occasional voice over some loud snores. " +
    "To the northwest, the tunnel winds further into the mountains. " +
    "The tunnel south seems to lead upwards and you think you can see " +
    "some light coming from that direction. " +
    "\n\n",70));

  add_exit(GOBLIN_STARTLOC,"east",0,0);
  add_exit(GOBLIN_CAVERN_DIR + "tunnel2","northwest",0,0);
  add_exit(GOBLIN_CAVERN_DIR + "entrance2","south",0,0);

/*
    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
*/
}
