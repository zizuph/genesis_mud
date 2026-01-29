/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Junction In Forest");
   set_long(
      "A junction in the forest: to the south you can see "
      + "very thick mounds of snow and very cold winds which "
      + "are ruffling the trees uncaringly. East you can hear "
      + "the gurgling of a small stream. The trail squeezes "
      + "into a dense pocket of trees to your west. "
      + "\n");
   
   
   add_item("trail","It goes east, west, and south.\n");
   add_item(({"snow","mounds"}), "The mounds of snow are south of you.\n");
   add_item("stream","You hear it gurgle to the east.\n");
   add_item("trees","They are actually large spires of ice.\n");
   add_item(({"ice","spires"}),"They resemble trees.\n");
   add_item(({"wind","winds"}),"The winds are cold and numbing.\n");
   add_exit(ICE_FOREST+"forest_6","west");
   add_exit(ICE_FOREST+"forest_8","south");
   add_exit(ICE_FOREST+"forest_10","east");
}
