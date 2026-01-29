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
      "You come to a corner in the corridor, the narrow passageway " +
      "leading northwest and northeast from here, illuminated by " +
      "a silver lamp in an alcove. A banner hangs beside the " +
      "entrance to a chamber to the east, while a large doorway " +
      "opens up the southern corner of the passage.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
 
   add_item("corridor", break_string(
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the northeast and northwest.\n",70));
 
   add_item("lamp", break_string(
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n",70));
 
   add_item("alcove", break_string(
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n",70));
 
   add_item("banner", break_string(
      "Made of shimmering black silk, the banner is embroidered with " +
      "what looks like a medallion bearing a coiled serpent " +
      "encircled with a wreath of hemlock leaves.\n",70));
 
   add_exit(ROOM_DIR+"corr14",  "northwest", 0);
   add_exit(ROOM_DIR+"corr16",  "northeast", 0);
   add_exit(ROOM_DIR+"talis",   "east", 0);
   add_exit(ROOM_DIR+"stair1",  "south", 0);
}
