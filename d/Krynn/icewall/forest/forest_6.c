/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object bird;

reset_icewall_room() {
   if (!bird) {
      bird = clone_object(ICE_CAST_M+"snowbird");
      bird->move(TO);
   }
}

create_icewall_room() {
   set_short("Tight Path");
   set_long(
      "You are on a tight path winding through the snow"
      + "laden trees. The forest, although peaceful, seems "
      + "deceptive. "
      + "\n");
   
   add_item("forest","It is strangely quiet.\n");
   add_item("trees","They are actually giant spires of ice.\n");
   add_item(({"spires","ice"}),"The giant spires of ice resemble trees.\n");
   add_item("snow","It is covering the icy trees like a blanket.\n");
   add_item("path","It is very narrow leaving you feeling vulnerable.\n");
   
   add_exit(ICE_FOREST+"forest_5","northeast");
   add_exit(ICE_FOREST+"forest_9","east");
   
   reset_icewall_room();
}
