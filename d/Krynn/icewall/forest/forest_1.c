/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object squirrel;

reset_icewall_room() {
   if (!squirrel) {
      squirrel = clone_object(ICE_CAST_M+"squirrel");
      squirrel->move(TO);
   }
}
create_icewall_room() {
   set_short("Strange Forest");
   set_long(
      "You see before you a very large forest. There are animal "
      + "noises coming from within the trees but you cannot tell "
      + "what makes them. Snow covers the ground everywhere but "
      + "you can still make out a path running north and southwest. "
      + "\n");
   
   add_item(({"snow","ground"}),"Snow lightly blankets the ground.\n");
   add_item("path","It runs north and south through the strange forest.\n");
   add_item("trees","Looking closely, you see they aren't trees "
      + "at all but are giant spires of ice shaped like trees.\n");
   add_item("spires","They are very tree-like.\n");
   
   add_exit(ICE_FOREST+"forest_3","north");
   add_exit(ICE_FOREST+"forest_2","southwest");
   add_exit(ICE_OUT+"to_forest_3","west");
   
   reset_icewall_room();
}
