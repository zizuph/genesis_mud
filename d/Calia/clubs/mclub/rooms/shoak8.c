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
      "Sunlight casts dark shadows in the corners of the stone shrine "+
      "which sits atop the steep hill to the northeast. An ancient oak "+
      "tree grows in the middle of the path around the hill, between "+
      "the surrounding forest to the southwest and the grass and flower "+
      "covered side of the hill. The path continues in a circle around "+
      "the hill to the north and southeast.\n");
 
   add_item("hill",
      "It is a steep round hill, its sides covered with lush grass and "+
      "small purple flowers.\n");
   add_item("shrine",
      "It is a small shrine of some sort which has been built on top of "+
      "the hill. The hill is to steep to reach the shrine from here.\n");
   add_item(({"woods","forest","trees"}),
      "The hill is surrounded by a thick forest of tall trees, some of "+
      "which have been cleared to make a path around the base of the hill.\n");
   add_item("oak",
      "Separated from the rest of the forest, this sturdy oak grows alone "+
      "in the center of the cleared path around the hill. Its canopy reaches "+
      "high above you providing a cooling shade. Its height and girdth tell "+
      "you it has been here since ancient times.\n");
   add_item(({"path","paths"}),
      "It circles the round hill, leading north and southeast.\n");
 
   add_exit(ROOM_DIR+"shoak9","north",0);
   add_exit(ROOM_DIR+"shoak7", "southeast",0);
}
