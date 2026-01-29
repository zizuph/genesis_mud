/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Path in forest");
   set_long(
      "You are within a great, icy forest. The trees are "
      + "covered with a blanket of snow. On the ground, you can make "
      + "out some fresh tracks in the snow."
      + "\n");
   
   add_item(({"forest","trees"}),
      "You notice that the trees are actually spires of ice.\n");
   add_item(({"ice","spires"}),"They resemble trees.\n");
   
   add_item("tracks","They are unlike any tracks you have ever seen.\n");
   
   add_exit(ICE_FOREST+"forest_1","south");
   add_exit(ICE_FOREST+"forest_4","northeast");
}
