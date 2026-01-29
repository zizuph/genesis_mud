/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object squirrel;

reset_icewall_room() {
   if (!squirrel) {
      squirrel=clone_object(ICE_CAST_M+"squirrel");
      squirrel->move(TO);
   }
}

create_icewall_room() {
   set_short("Dark Thicket");
   set_long(
      "The trees are becoming quite dense now. Very little "
      + "light is penetrating the forest and you begin to feel "
      + "uneasy. Very strange sounds are coming from the trees. "
      + "\n");
   
   add_item("path","You can barely see it because of the sparse light.\n");
   add_item("trees","They resemble spires of ice and are very thick.\n");
   add_item(({"ice","spires"}),"They are very dense here.\n");
   add_cmd_item(({"trees","sounds"}),({"listen","examine"}),
      "You cannot make out the source of these sounds.\n");
   
   add_exit(ICE_FOREST+"forest_5","southeast");
   add_exit(ICE_FOREST+"forest_3","southwest");
   
   reset_icewall_room();
}
