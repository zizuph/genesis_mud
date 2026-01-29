/*
**  MCLUB - Memorial Shrine, Circle of oaks around the base of the hill
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       7/29/95   Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_room() {
   set_short("On a circular path");
   set_long(
      "A gentle breeze livens the canopy of the thick forest which "+
      "encircles the path to the north and northwest on this side "+
      "of the hill, giving you a feeling of tranquility. A towering oak "+
      "grows in the center of the path, separated from the rest of "+
      "the forest. Dark grass peppered with purple flowers carpets "+
      "the side of the steep hill as it climbs up to the shrine to "+
      "the southeast.\n");
   add_item("grass","It carpets the steep sides of the hill.\n");
   add_item("flowers","They are wild violets growing on the sides "+
                      "of the hill.\n");
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "small purple flowers.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. The hill is too steep to reach the shrine from here.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading southwest and east.\n");
 
   add_exit(ROOM_DIR+"shoak12","east",0);
   add_exit(ROOM_DIR+"shoak10","southwest",0);
}
