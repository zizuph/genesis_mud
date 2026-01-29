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
      "The old stones of the shrine atop the hill soak up the sunlight "+
      "as you make your way down a path around the base of the hill. "+
      "A shaded forest walls the path to the west and northwest, while "+
      "a solitary great oak grows here in the middle of the path. The "+
      "path continues around the hill to the south and northeast.\n");
 
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
      "It circles the round hill, leading norteast and south.\n");
 
   add_exit(ROOM_DIR+"shoak11","northeast",0);
   add_exit(ROOM_DIR+"shoak9", "south",0);
}
