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
   set_short("Path Along Mountain");
   set_long(
      "You are at the base of the eastern edge of the Icewall "
      + "Mountains. The stream continues its downward path from "
      + "the south. The ground is very rocky here and you can "
      + "see some footholds carved into the rocky wall to the "
      + "east. "
      + "\n");
   
   add_item("footholds","Perhaps you should climb them.\n");
   add_item("ground","It is studded with rocks and pebbles.\n");
   add_item("stream","It flows north and south.\n");
   add_item(({"wall","mountain"}),"It is quite steep but you "
      + "could climb it via the footholds.\n");
   
   add_item(({"rocks","pebbles"}),"The rocks and pebbles are strewn about "
      + "absentmindedly by a Krynn Wizard to impress you with detail.\n");
   add_exit(ICE_FOREST+"forest_13","up","@@climb");
   add_exit(ICE_FOREST+"forest_10","northwest");
   add_exit(ICE_FOREST+"forest_14","southeast");
   reset_icewall_room();
}


/* how do I use the climb skill for this room??? */

climb() {
   write("You expertly climb, one foothold at a time.\n");
   return 0;
}
