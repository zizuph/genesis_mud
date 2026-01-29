/*
**  Temple of Dephonia, Second Level Corridor
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/10/95    Created
**
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(
      "You walk around to the northern side of a circular corridor "+
      "on the second floor of the temple, a bit of light "+
      "from a window on the inner wall to the south reflecting off the " +
      "floor. The corridor circles around to the southwest and southeast "+
      "while a narrow passage leads north. There are entrances to two "+
      "chambers cut into the outer circle to the east and west.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("corridor",
      "It is a circular passageway around the center of the temple "+
      "on the second level.\n");
 
   add_item(({"walls","wall"}), "They are glassy-smooth black marble "+
      "walls set in concentric circles to construct this corridor.\n");
 
   add_item("window","It is a small arched window on the southern "+
            "inner wall of the passageway. A bit of light shines "+
            "through it.\n");
 
   add_item(({"through window","out window"}), "What?\n");
   add_cmd_item(({"through window","out window"}), "look",
                "You look through the window "+
                "into the central tower of the temple's sanctuary. "+
                "Far below you see the consecrated altar of the "+
                "temple, and above you see the tower's crystal dome, "+
                "sunlight spilling through.\n");
 
   add_item("floor","It is made of the same black marble as "+
            "the walls. Light from the window shatters into sparkling "+
            "colors on its glassy surface.\n");
 
   add_exit(ROOM_DIR+"corr25",  "southwest", 0);
   add_exit(ROOM_DIR+"corr23",  "southeast", 0);
   add_exit(ROOM_DIR+"corr27",  "north", 0);
   add_exit(ROOM_DIR+"quartch", "west", 0);
   add_exit(ROOM_DIR+"quartslv","east", 0);
}
