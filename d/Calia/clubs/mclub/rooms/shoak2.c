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
      "The walls of the eastern wing of the shrine tower atop the "+
      "hill, set with windows the fortress is missing on the other "+
      "parts. A sea of honeysuckle covers this northeastern side "+
      "of the hill, perfuming the path around it. Another ancient oak "+
      "grows in the middle of the path, its craggy bark twisting in "+
      "mysterious lines.\n");
   add_item("grass","It carpets the steeps sides of the hill.\n");
   add_item("honeysuckle","They are long yellow flowers growing on a "+
            "dark vine with sharp leaves which cover this side of the "+
            "hill.\n");
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "honeysuckle.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. The hill is to steep to reach the shrine from here.\n");
   add_item("windows","They are stained glass windows on the eastern "+
            "wing of the shrine. You can not make out the pattern of "+
            "their mosaic from here.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item("bark","The bark of the oak seems like shaggy ropes turned "+
            "into wood through the many years.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading northwest and south.\n");
 
   add_exit(ROOM_DIR+"shoak1","northwest",0);
   add_exit(ROOM_DIR+"shoak3","south",0);
}
