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
   set_short("Eastern Forest");
   set_long(
      "You find yourself at the foot of a small path leading away "
      + "from the icy forest and up into the mountains. Icy snow "
      + "covers the path so you better be careful in climbing it. "
      + "\n");
   
   add_item("path","The path climbing up the mountain is covered "
      + "with ice and snow.\n");
   add_item(({"ice","snow"}),"It covers just about everything.\n");
   add_item("forest","It is to the west and north of you.\n");
   add_item("mountains","They are huge and menacing.\n");
   
   add_exit(ICE_FOREST+"forest_12","northwest");
   add_exit(ICE_FOREST+"forest_15","northeast");
   
   reset_icewall_room();
}
