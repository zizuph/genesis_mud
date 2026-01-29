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
      "leading northeast and southeast from here, illuminated by " +
      "a silver lamp in an alcove. To the west is an entrance to " +
      "a chamber, a banner hanging beside the doorway. A rather " +
      "large ornamented arch marks an entrance to the east.\n",70));
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item("banner",break_string(
      "Made of gold silk, the banner next to the entrance to the " +
      "west bears a scroll.\n",70));
 
   add_item("arch", break_string(
      "Butressed by two thick pillars, the grand arch is wide " +
      "enough for three abreast and twice your height, leading " +
      "into some sort of auditorium to the east.\n",70));
 
   add_item("corridor", break_string(
      "A dimly lit narrow passageway through the temple, " +
      "it leads to the southeast and northeast.\n",70));
 
   add_item("pillars", break_string(
      "They stand like ancient sentinels on either side of the " +
      "arched entrance to the east.\n",70));

   add_item("lamp", break_string(
      "The lamp is crafted of silver in the form of a raven, " +
      "its wings spread above its head. " +
      "A small flame flickers from the upraised " +
      "beak of the bird, giving a dim light to the corridor.\n",70));
 
   add_item("alcove", break_string(
      "Smoothly carved into the wall of the corridor, this alcove " +
      "has an arched top and serves as a small shelf, upon which " +
      "rests a silver lamp.\n",70));
 
 
   add_exit(ROOM_DIR+"corr12",  "northeast", 0);
   add_exit(ROOM_DIR+"corr14",  "southeast", 0);
   add_exit(ROOM_DIR+"antermw",  "east", 0);
   add_exit(ROOM_DIR+"library1", "west", 0);
}
