inherit "/d/Gondor/common/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
   set_short("east guardroom");
   set_long(BSN("This is the eastern guardroom. Here the troops, which are "
     + "not on duty, eat and relax. On the east side of the room there is "
     + "a table filled with empty kitchen attributes and such things. But "
     + "you do not want to mess with their things so you look around and "
     + "spot some beds along the south wall, but again those are none of "
     + "your business. In the northeast corner there is a staircase leading "
     + "upwards, and the gates are to the west."));

   add_exit(EDORAS_DIR + "gat_stairs", "up",   0, 2);
   add_exit(EDORAS_DIR + "gate",       "west", 0, 1);
   add_prop(ROOM_I_INSIDE,1);
   add_item(({"bed","beds"}), 
      "These are regular beds, not so different from your own.\n");
   add_item("table", "This is an oaktable filled with jugs and cups and plates.\n");
}

