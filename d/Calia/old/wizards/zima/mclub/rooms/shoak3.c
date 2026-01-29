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
      "The sweet smell of the honeysuckle which covers the steep "+
      "side of the hill to the west fills your mind with pleasant "+
      "thoughts. A solitary oak towers from the center of the path "+
      "here, its bark unusually black. A large stained glass window "+
      "is set on the wall of the shrine atop the hill, its sides "+
      "much too steep to scale.\n");
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
   add_item("window","It is a large stained glass window on the outer "+
            "wall of the eastern wing of the shrine. Its mosaic seems "+
            "to portray a robed figure, but you can't make out much "+
            "more than that from this distance.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item("bark","The bark of the oak is very black, much darker than "+
            "that of the other solitary oaks you have seen on this path.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading north and south.\n");
 
   add_exit(ROOM_DIR+"shoak2","north",0);
   add_exit(ROOM_DIR+"shoak4","south",0);
}
