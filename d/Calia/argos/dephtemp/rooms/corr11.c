/*
**  Temple of Dephonia, Ground Level Corridor
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**
**
*/
 
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("Corridor in the Temple of Dephonia");
   set_long(break_string(
      "You are standing in the corner of a corridor which leads " +
      "through the Temple of Dephonia, a dark passage of black marble " +
      "dimly lit by an oil lamp in an alcove on the wall.  The corridor " +
      "leads southwest and southeast through the temple, while an "   +
      "arched doorway inlaid with silver leads north. A small banner " +
      "hangs on the wall next to each of the entrances to two " +
      "chambers to the east and west.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"banner","banners"}), break_string(
      "The banners are made of white silk, the one to the west " +
      "bearing the emblem of a grecian lamp while the one to the " +
      "east is embroidered with a simple red circle.\n",70));
 
   add_item("corridor", break_string(
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the southwest and southeast.\n",70));
 
   add_item("lamp", break_string(
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n",70));
 
   add_item("alcove", break_string(
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n",70));
 
   add_item(({"arch","doorway"}), break_string(
      "An arched doorway, inlaid with silver, leads north " +
      "into the foyer of the temple.\n",70));
 
   add_exit(ROOM_DIR+"foyer",  "north", 0);
   add_exit(ROOM_DIR+"corr12", "southwest", 0);
   add_exit(ROOM_DIR+"corr18", "southeast", 0);
   add_exit(ROOM_DIR+"classrm","west", 0);
   add_exit(ROOM_DIR+"recept", "east", 0);
}
