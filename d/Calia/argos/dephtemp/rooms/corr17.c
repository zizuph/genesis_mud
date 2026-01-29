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
   set_long(
      "You come to a corner in the corridor, the narrow passageway " +
      "leading northwest and southwest from here, illuminated by " +
      "a silver lamp in an alcove. A rather large ornamented arch " +
      "marks an entrance to the west, while a more modest doorway "+
      "leads east.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("doorway",
      "It is a simple rectangular doorway with three crescent moons "+
      "sculpted above it.\n");
 
   add_item("arch",
      "Butressed by two thick pillars, the grand arch is wide " +
      "enough for three abreast and twice your height, leading " +
      "into some sort of auditorium to the west.\n");
 
   add_item("corridor",
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the northwest and southwest.\n");
 
   add_item("lamp",
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n");
 
   add_item("alcove",
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n");
 
   add_item("pillars",
      "They stand like ancient sentinels on either side of the " +
      "grand archway leading east.\n");
 
   add_exit(ROOM_DIR+"corr18",  "northwest", 0);
   add_exit(ROOM_DIR+"corr16",  "southwest", 0);
   add_exit(ROOM_DIR+"chapel",  "east", 0);
   add_exit(ROOM_DIR+"anterme", "west", 0);
}
