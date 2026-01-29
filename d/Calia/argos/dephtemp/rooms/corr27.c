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
      "You walk into the end of a narrow corridor in the temple where "+
      "there are entrances to chambers to the north, west and east. "+
      "The corridor leads south into another passage, where you can "+
      "see light falling in from a window.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("window","It is further south.\n");
   add_item("corridor","It is a narrow passage which ends here and "+
                       "leads south.\n");
 
   add_exit(ROOM_DIR+"lounge",  "north", 0);
   add_exit(ROOM_DIR+"quartnpr","west", 0);
   add_exit(ROOM_DIR+"quartnps","east", 0);
   add_exit(ROOM_DIR+"corr24",  "south", 0);
}
