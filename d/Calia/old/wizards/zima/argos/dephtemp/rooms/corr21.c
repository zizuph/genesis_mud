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
      "You are standing in a narrow corridor on the second level of "+
      "the Temple of Dephonia. There are entrances to " +
      "two chambers to the east and west, while the corridor continues " +
      "to the north and south. There is a pleasant aroma wafting from "+
      "somewhere near that makes your stomach growl.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("corridor",
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the north and south.\n");
 
   add_exit(ROOM_DIR+"corr22", "north", 0);
   add_exit(ROOM_DIR+"stair2", "south", 0);
   add_exit(ROOM_DIR+"dine2",  "east", 0);
   add_exit(ROOM_DIR+"kitchen","west", 0);
}
