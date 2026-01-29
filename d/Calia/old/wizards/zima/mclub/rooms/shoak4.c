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
      "The view of the shrine atop the hill affords a look at the "+
      "structure's bell tower which rises slightly above the shrine's "+
      "roof on its southwestern corner. A few bees buzz through the "+
      "thick growth of honeysuckle which covers the hill, gathering "+
      "nectar for their hive. A large oak grows here in the center "+
      "of the path, which continues around the hill to the north and "+
      "southwest.\n");
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
   add_item(({"bell tower","tower","belltower"}),
      "Made of the same large, irregular stones as the rest of the "+
      "shrine, the bell tower rises slightly higher than the rest "+
      "of the monument, sit into the southeastern corner of the "+
      "structure.\n");
   add_item("bees","They buzz around amongst the flowers of the honeysuckle.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading north and southwest.\n");
 
   add_exit(ROOM_DIR+"shoak3","north",0);
   add_exit(ROOM_DIR+"shoak5","southwest",0);
}
