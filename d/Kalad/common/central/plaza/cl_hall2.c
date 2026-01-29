/*
ROOM: Council of Lords hallway end
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_short("The hallway of the Council of Lords building");
   set_long(
      "This is the end of the Council of Lords building hallway. There are "+
      "nice decorations everywhere, and the inside walls are not as charred "+
      "as the outside walls. Somebody must have cleaned them. To the northeast "+
      "is the Council of Lords debate chamber. "
   );
   set_time_desc(
      "Many people are walking up and down the corridor.\n",
      "You hear some whispering going on to the northeast.\n");

   add_exit(CENTRAL(plaza/cl_hall1), "south", 0, -1, -1);
   add_exit(CENTRAL(plaza/cl_off2), "east" ,0,-1,-1);
   add_exit(CENTRAL(plaza/cl_deb), "northeast",0,-1,-1);
   add_exit(CENTRAL(plaza/cl_up), "up", 0, -1, -1);
  add_item(({"chamber", "debate chamber"}),
    "That's where the Council of Lords plans all its political schemes.\n"
  );
}
