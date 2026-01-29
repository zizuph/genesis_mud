/* Vladimir 8-09-94 */
inherit "/std/room.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"

void
create_room()
{
   set_short("Fortress hallway");
   set_long(
      "This passageway leads north along a rough walkway. You can barely\n"
      + "make out the ceiling above you. The walls are bereft of everything\n"
      + "except their sickening odor.\n");
   
   add_item(({"walkway", "passageway"}),
      break_string("The floor here is tricky to walk on "+
         "due to the uneveness of the whole room.\n", 70));
   add_item(({"ceiling", "up"}),
      break_string("you can not seem to make out any details of "+
         "the ceiling.\n", 70));
   add_item(({"wall", "walls"}),
      break_string("The walls are bare. They do exude a particularly "+
         "nausiating oder though.\n", 70));
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"hall3", "north");
   add_exit(ORC+"hall1", "south");
}
