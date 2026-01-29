/* Created by Stevenson */
/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object peng1, peng2;

reset_icewall_room() {
   if (!peng1) {
      peng1 = clone_object(ICE_CAST_M+"penguin");
      peng1->move(TO);
   }
   if (!peng2) {
      peng2 = clone_object(ICE_CAST_M+"penguin");
      peng2->move(TO);
   }
}

create_icewall_room() {
   set_short("Cave Entrance");
   set_long(
      "You are in the middle of a raging wind. The storm "
      + "threatens your safety with its severity. To the "
      + "east is a cave which might be safe. The plains "
      + "stretch out to the south and southwest. "
      + "\n");
   
   add_item("wind","It blows about mercilessly.\n");
   add_item("storm","You better seek safety before it claims you.\n");
   add_item("cave","It looks like it might be safe but maybe not.\n");
   add_item("plains","The plains stretch out covering all.\n");
   add_item("all","The plains cover all.\n");
   
   add_exit(ICE_PLAINS+"plain_8","southwest");
   add_exit(ICE_PLAINS+"plain_12","south");
   add_exit(ICE_PLAINS+"plain_13","east");
   
   reset_icewall_room();
}
