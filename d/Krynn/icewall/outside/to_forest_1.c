#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("A smooth path");
   set_long(
      "You stand upon a snow-covered path leading east to a forest. "
      + "Because of the cold, wet, wind, it is difficult to see "
      + "much else. To your west is the huge block of ice. "
      + "\n");
   

add_item("path","It is smooth from so much traffic.\n");
add_item(({"block", "block of ice"}), "The block of ice contains a stairway carved into its surface.\n");
add_item("forest", "The forest to your east looks cold, dark, and cold.\n");
   add_exit(ICE_OUT+"to_forest_2","east");
   add_exit(ICE_OUT+"bottom_of_ice","west");
}
