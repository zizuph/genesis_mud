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
   set_short("Forest Path");
   set_long(
      "You are within a great, icy forest. The trees are "
      + "snowcovered like a blanket. On the ground you can make "
      + "out some fresh tracks in the snow."
      + "\n");
   
   add_item(({"trees","ice","spires"}),"You notice that the trees are actually "
      + "spires of ice.\n");
   add_item("snow","There are tracks in it.\n");
   add_item("path","It leads east into the forest and north.\n");
   add_item("tracks","They are unlike any tracks you have ever seen.\n");
   
   add_exit(ICE_FOREST+"forest_1","northeast");
   add_exit(ICE_FOREST+"forest_7","east");
   
   reset_icewall_room();
}
