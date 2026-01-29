#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("A smooth path");
   set_long(
      "This is a path going between the block of ice and the forest."
      + "\n");
   
   add_item("path","It is smooth from constant traffic.\n");
	add_item(({"block", "block of ice"}), "The block of ice contains a stairway carved into its surface.\n"); 
	add_item("forest", "The forest to your east looks cold, dark, and cold.\n");

   
   add_exit(ICE_OUT+"to_forest_1","west","@@chill");
   add_exit(ICE_OUT+"to_forest_3","east","@@chill");
}

chill() {
   write("A sudden blast of arctic wind numbs you to the bone.\n");
   return 0;
}
