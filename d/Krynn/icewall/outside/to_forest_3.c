#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Edge of the forest");
   set_long(
      "You are right next to the icy forest. You can feel strange "
      + "eyes staring at you. From somewhere you can hear chittering. "
      + "The only exits are east into the forest, and west along the "
      + "path."
      + "\n");
   
   add_item("path","You are standing on it.\n");
   add_item("forest","It doesn't look too inviting.\n");
   add_item("trees","They look funny.\n");
   
   add_exit(ICE_OUT+"to_forest_2","west");
   add_exit(ICE_FOREST+"forest_1","east");
}
