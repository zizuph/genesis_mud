/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Center Of Forest");
   set_long("You are in the middle of the icy forest.  North and east you "
      +"can see the mighty Icewall Mountains.  East you hear "
      + "the sound of running water and south are mighty drifts "
      + "of snow.\n");
   add_item("water", "You know it is out there somewhere.\n");
   add_item("snow","It is everywhere and quite cold.\n");
   add_item("mountains","They are off in the distance.\n");
   
   add_exit(ICE_FOREST+"forest_9","north");
   add_exit(ICE_FOREST+"forest_7","southwest");
}
