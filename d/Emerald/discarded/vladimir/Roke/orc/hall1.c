/* Vladimir 8-10-94 */
inherit "/std/room.c";

#include <macros.h>
#include "/sys/stdproperties.h"
#include "local.h"

create_room()
{
   set_short("Fortress hallway");
   set_long("This is the first part of a large arched hallway that\n"
      + "leads north through the fortress. There is an almost\n"
      + "unnoticeable crooked door to the east that has been left\n"
      + "open. You hear laughing coming from somewhere echoing\n"
      + "throughout the halls.\n");
   add_item(({"door", "small door"}),
   "It is a small open door that seems stuck open.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(ORC+"sleeproom", "east");
   add_exit(ORC+"hall2", "north");
   add_exit(ORC+"r1", "south");
}
