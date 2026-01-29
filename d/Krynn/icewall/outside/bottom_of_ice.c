#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("In front of a huge block of ice");
   set_long(
      "Towering in front of you is an enormous block of ice. "
      + "Carved into its face is a stairway leading up. To your east "
      + "is what looks like an Ice Forest, while a path leads off to the "
      + "west. "
      + "\n");

   add_item("forest","It is off in the distance to the east.\n");

   add_item("path","It leads both east and west.\n");

   add_item(({"ice","block","block of ice","stairs","stairway"}),
      "The block of ice contains a stairway carved into its surface.\n");

   add_exit(ICE_OUT+"up_stairs1","up");
   add_exit(ICE_OUT + "grif_1", "south");
   add_exit(ICE_OUT + "path_1", "west");
   add_exit(ICE_OUT+"to_forest_1","east");
   add_exit("/d/Krynn/icewall/castle2/rooms/west_path3","northwest");
   add_exit("/d/Krynn/icewall/castle2/rooms/east_path1","northeast");


}

closed() {
   write("This area is closed.  See Stevenson to open it.\n");
   return 1;
}
