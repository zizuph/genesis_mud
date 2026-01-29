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
      "A slight breeze sways the sturdy branches of a solitary oak "+
      "which stands in the middle of this path around the hill, "+
      "growing a good distance from the surrounding forest. You see "+
      "the bell tower of the stone shrine sitting in its southeastern "+
      "corner, rising slightly above the rest of the monument. The "+
      "side of the hill is covered with dark green grass interspersed "+
      "with small purple flowers leading up to the base of the shrine "+
      "to the north. The path continues around the hill to the "+
      "northeast and west.\n");
   add_item("grass","It carpets the steeps sides of the hill.\n");
   add_item("flowers","They are wild violets growing on the sides "+
                      "of the hill.\n");
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "honeysuckle.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. The hill is to steep to reach the shrine from here.\n");
   add_item(({"bell tower","tower","belltower"}),
      "Made of the same large, irregular stones as the rest of the "+
      "shrine, the bell tower rises slightly higher than the rest "+
      "of the monument, sit into the southeastern corner of the "+
      "structure.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading northeast and west.\n");
 
   add_exit(ROOM_DIR+"shoak4","northeast",0);
   add_exit(ROOM_DIR+"shoak6","west",0);
}
