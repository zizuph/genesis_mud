/*Created by Stevenson*/
/* Wolf added by Macker 10/27/94 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object wolf;

reset_icewall_room() {
   if (!wolf) {
	wolf = clone_object(PLAINS_L + "wolf");
      wolf->move(TO);
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
   add_item(({"spires","ice"}),"They giant spires of ice resemble trees.\n");
   add_item("snow","It is covering the icy trees like a blanket.\n");
   add_item("path","It is very narrow leaving you feeling vulerable.\n");
   
   add_exit(ICE_FOREST+"forest_4","northwest");
   add_exit(ICE_FOREST+"forest_6","southwest");
   reset_icewall_room();
}
