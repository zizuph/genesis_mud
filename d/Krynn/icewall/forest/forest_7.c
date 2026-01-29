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
   set_short("Deep In Forest");
   set_long(
      "The trees are becoming quite dense now. Very little "
      + "is penetrating the forest and you begin to feel "
      + "uneasy. Very strange sounds are coming from the trees. "
      + "A very large snowdrift is to the southeast. "
      + "\n");
   
   add_item(({"snow","drift","snowdrift"}),"It is off in the distance.\n");
   add_item("trees","They are actually giant spires of ice.\n");
   add_item(({"ice","spires"}),"They resemble trees.\n");
   add_cmd_item(({"trees","sounds"}),({"listen","examine"}),
      "You cannot make out the source of these sounds.\n");
   
   add_exit(ICE_FOREST+"forest_2","west");
   add_exit(ICE_FOREST+"forest_11","southeast");
   add_exit(ICE_FOREST+"forest_8","northeast");
   
   reset_icewall_room();
}
